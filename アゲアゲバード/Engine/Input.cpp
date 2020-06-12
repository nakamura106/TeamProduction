#define DIRECTINPUT_VERSION 0x0800
#include<d3dx9math.h>
#include<math.h>
#include "Input.h"
#include "Window.h"
#include"../Scene/OptionScene.h"
#include"../Manager/SceneManager.h"

//#include "DirectX.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

//�O���[�o���ϐ�
static LPDIRECTINPUT8 g_InputInterface;
static LPDIRECTINPUTDEVICE8 g_KeyDevice;
static LPDIRECTINPUTDEVICE8 g_MouseDevice;		//!< DIRECTINPUTDEVICE8�̃|�C���^

static DIMOUSESTATE g_PrevMouseState;			//!< �}�E�X�̂P�t���[���O�̓��͏��
static DIMOUSESTATE g_CurrentMouseState;		//!< �}�E�X�̌��݂̓��͏��
static Vec2 g_MousePos;
static Vec2 g_MouseMoveVec;
static LPDIRECTINPUTDEVICE8 g_GamePadDevice;
static ButtonState g_ButtonStates[ButtonKind::ButtonKindMax];



//�Q�[���p�b�h�f�o�C�X�̍쐬-�f�o�C�X�񋓂̌��ʂ��󂯎��\����
struct DeviceEnumParameter
{
	LPDIRECTINPUTDEVICE8* GamePadDevice;
	int FindCount;
};

// �}�E�X�̍X�V
void UpdateMouse();

// �Q�[���p�b�h�̍X�V
void UpdateGamePad();

bool CreateGamePadDevice();

#define MOUSE_ON_VALUE (0x80)		// �I����Ԃ̒l

// @brief ���͏�Ԃ̎��
enum INPUT_STATE
{
	NOT_PUSH,		//������Ă��Ȃ�
	PUSH_DOWN,		//�����ꂽ�u��
	PUSH,			//������Ă���
	PUSH_UP,		//�������u��
};

//�L�[�̏�Ԃ�ێ�����O���[�o���ϐ�
static INPUT_STATE g_InputState[KEY_INFO::MAX_KEY_INFO];


BOOL SetUpCooperativeLevel(LPDIRECTINPUTDEVICE8 device)
{
	//�������[�h�̐ݒ�
	if (FAILED(device->SetCooperativeLevel(
		FindWindow(WINDOW_CLASS_NAME, nullptr),
		DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)
	))
	{
		return false;
	}
	return true;
}

//���C�u�������̃L�[���z��
int g_KeyInfo[] = {
	DIK_ESCAPE,
	DIK_SPACE,
	DIK_UP,
	DIK_DOWN,
	DIK_RIGHT,
	DIK_LEFT,
	DIK_A,
	DIK_W,
	DIK_S,
	DIK_D,
	DIK_F,
	DIK_E,
	DIK_Q,
	DIK_T,
	DIK_Y,
	DIK_RETURN,
	DIK_LCONTROL,
	DIK_LSHIFT,
};

BOOL StartGamePadControl()
{
	if (g_GamePadDevice == nullptr)
	{
		return false;
	}

	if (FAILED(g_GamePadDevice->Acquire()))
	{
		return false;
	}

	return true;
}

BOOL SetUpGamePadProperty(LPDIRECTINPUTDEVICE8 device)
{
	// �����[�h���Βl���[�h�Ƃ��Đݒ�
	DIPROPDWORD diprop;
	ZeroMemory(&diprop, sizeof(diprop));
	// ��������DIPROP�̃w�b�_�[�ɃX�e�[�^�X�ݒ�
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.diph.dwObj = 0;
	diprop.dwData = DIPROPAXISMODE_ABS;
	if (FAILED(device->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		return false;
	}

	// X���̒l�͈̔͐ݒ�
	DIPROPRANGE diprg;
	ZeroMemory(&diprg, sizeof(diprg));
	diprg.diph.dwSize = sizeof(diprg);
	diprg.diph.dwHeaderSize = sizeof(diprg.diph);
	diprg.diph.dwHow = DIPH_BYOFFSET;
	diprg.diph.dwObj = DIJOFS_X;
	diprg.lMin = -1000;
	diprg.lMax = 1000;
	if (FAILED(device->SetProperty(DIPROP_RANGE, &diprg.diph)))
	{
		return false;
	}

	// Y���̒l�͈̔͐ݒ�
	diprg.diph.dwObj = DIJOFS_Y;
	if (FAILED(device->SetProperty(DIPROP_RANGE, &diprg.diph)))
	{
		return false;
	}

	return true;
}

BOOL CALLBACK DeviceFindCallBack(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef)
{
	DeviceEnumParameter* parameter = (DeviceEnumParameter*)pvRef;
	LPDIRECTINPUTDEVICE8 device = nullptr;

	if (parameter->FindCount >= 1)
	{
		return DIENUM_STOP;
	}

	HRESULT hr = g_InputInterface->CreateDevice(
		lpddi->guidInstance,
		parameter->GamePadDevice,
		NULL);

	if (FAILED(hr))
	{
		return DIENUM_STOP;
	}

	device = *parameter->GamePadDevice;
	hr = device->SetDataFormat(&c_dfDIJoystick);

	if (FAILED(hr))
	{
		return DIENUM_STOP;
	}

	if (SetUpGamePadProperty(device) == false)
	{
		return DIENUM_STOP;
	}

	if (SetUpCooperativeLevel(device) == false)
	{
		return DIENUM_STOP;
	}

	//if (FAILED(device->Poll()))
	//{
	//	return DIENUM_STOP;
	//}

	parameter->FindCount++;

	return DIENUM_CONTINUE;
}

bool InitInput()
{
	if (CreateInputInterface() == false)
	{
		return false;
	}

	if (CreateMouseDevice() == false)
	{
		EndInput();
		return false;
	}

	if (CreateKeyboardDevice() == false) {
		EndInput();
		return false;
	}

	if (CreateGamePadDevice() == false)
	{
		EndInput();
		return false;
	}

	for (int i = 0; i < ButtonKind::ButtonKindMax; i++)
	{
		g_ButtonStates[i] = ButtonState::ButtonStateNone;
	}

	ZeroMemory(&g_CurrentMouseState, sizeof(DIMOUSESTATE));
	ZeroMemory(&g_PrevMouseState, sizeof(DIMOUSESTATE));

	return true;
}

void EndInput()
{
	if (g_MouseDevice != nullptr)
	{
		g_MouseDevice->Release();
		g_MouseDevice = nullptr;
	}

	if (g_InputInterface != nullptr)
	{
		g_InputInterface->Release();
		g_InputInterface = nullptr;
	}

	if (g_GamePadDevice != nullptr)
	{
		g_GamePadDevice->Release();
		g_GamePadDevice = nullptr;
	}

	if (g_KeyDevice != nullptr)
	{
		g_KeyDevice->Release();
		g_KeyDevice = nullptr;
	}
}

bool CreateInputInterface()
{
	// IDirectInput8�C���^�[�t�F�C�X�̎擾
	HRESULT hr = DirectInput8Create(GetModuleHandle(nullptr),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)& g_InputInterface,
		NULL);
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}

bool CreateGamePadDevice()
{
	DeviceEnumParameter parameter;

	parameter.FindCount = 0;
	parameter.GamePadDevice = &g_GamePadDevice;

	// �w�肵���f�o�C�X��񋓂���i����ł���΃Q�[���p�b�h�j
	if (FAILED(g_InputInterface->EnumDevices(
		DI8DEVTYPE_GAMEPAD,
		DeviceFindCallBack,		// ��2�����F�R�[���o�b�N�֐�
		&parameter,				// ��3�����F�R�[���o�b�N�֐��ɓn�����Ƃ��ł���f�[�^
		DIEDFL_ATTACHEDONLY		// ��4�����F����ł������Ă���f�o�C�X�݂̂��g�p����ݒ�
	)))
	{
		return false;
	}

	/*if (parameter.FindCount == 0)
	{
		return false;
	}*/

	int count = 0;
	while (StartGamePadControl() == false)
	{
		Sleep(1000);
		count++;
		if (count >= 5)
		{
			break;
		}
	}

	return true;
}

bool CreateMouseDevice()
{
	// �}�E�X�p�Ƀf�o�C�X�I�u�W�F�N�g���쐬
	if (FAILED(g_InputInterface->CreateDevice(GUID_SysMouse, &g_MouseDevice, NULL)))
	{
		// �f�o�C�X�̍쐬�Ɏ��s
		return false;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_MouseDevice->SetDataFormat(&c_dfDIMouse)))
	{
		// �f�[�^�t�H�[�}�b�g�Ɏ��s
		return false;
	}

	// ���[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	if (FAILED(g_MouseDevice->SetCooperativeLevel(
		FindWindowA(WINDOW_CLASS_NAME, nullptr),
		DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
	{
		// ���[�h�̐ݒ�Ɏ��s
		return false;
	}

	// �f�o�C�X�̐ݒ�
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;	// ���Βl���[�h�Őݒ�i��Βl��DIPROPAXISMODE_ABS�j

	if (FAILED(g_MouseDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		// �f�o�C�X�̐ݒ�Ɏ��s
		return false;
	}

	// ���͐���J�n
	g_MouseDevice->Acquire();

	return true;
}

bool CreateKeyboardDevice()
{
	// �}�E�X�p�Ƀf�o�C�X�I�u�W�F�N�g���쐬
	if (FAILED(g_InputInterface->CreateDevice(GUID_SysKeyboard, &g_KeyDevice, NULL)))
	{
		// �f�o�C�X�̍쐬�Ɏ��s
		return false;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_KeyDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		// �f�[�^�t�H�[�}�b�g�Ɏ��s
		return false;
	}

	// ���[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	if (FAILED(g_KeyDevice->SetCooperativeLevel(
		FindWindowA(WINDOW_CLASS_NAME, nullptr),
		DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
	{
		// ���[�h�̐ݒ�Ɏ��s
		return false;
	}

	// �f�o�C�X�̐ݒ�
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;	// ���Βl���[�h�Őݒ�i��Βl��DIPROPAXISMODE_ABS�j

	if (FAILED(g_KeyDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		// �f�o�C�X�̐ݒ�Ɏ��s
		return false;
	}

	// ���͐���J�n
	g_KeyDevice->Acquire();

	return true;
}

void KeyStateUpdate()
{
	BYTE Key[256];
	HRESULT hr = g_KeyDevice->GetDeviceState(256, Key);

	if (FAILED(hr))
	{
		return;
	}

	for (int i = 0; i < MAX_KEY_INFO; i++)
	{
		if (Key[g_KeyInfo[i]] & 0x80)
		{
			if (g_InputState[i] == INPUT_STATE::NOT_PUSH || g_InputState[i] == INPUT_STATE::PUSH_UP)
			{
				g_InputState[i] = INPUT_STATE::PUSH_DOWN;
			}
			else
			{
				g_InputState[i] = INPUT_STATE::PUSH;
			}
		}
		else
		{
			if (g_InputState[i] == INPUT_STATE::PUSH || g_InputState[i] == INPUT_STATE::PUSH_DOWN)
			{
				g_InputState[i] = INPUT_STATE::PUSH_UP;
			}
			else
			{
				g_InputState[i] = INPUT_STATE::NOT_PUSH;
			}
		}
	}
}

bool GetKey(KEY_INFO key)
{
	return (g_InputState[key] == INPUT_STATE::PUSH);
}

bool GetKeyDown(KEY_INFO key)
{
	return (g_InputState[key] == INPUT_STATE::PUSH_DOWN);
}

bool GetKeyUp(KEY_INFO key)
{
	return (g_InputState[key] == INPUT_STATE::PUSH_UP);
}

void UpdateInput()
{
	UpdateMouse();
	UpdateGamePad();

	g_PrevMouseState = g_CurrentMouseState;
	// �}�E�X�̏�Ԃ��擾���܂�
	HRESULT	hr = g_MouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &g_CurrentMouseState);
	if (FAILED(hr))
	{
		g_MouseDevice->Acquire();
		hr = g_MouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &g_CurrentMouseState);
	}
}

bool OnMouseDown(MouseButton button_type)
{
	if (!(g_PrevMouseState.rgbButtons[button_type] & MOUSE_ON_VALUE) &&
		g_CurrentMouseState.rgbButtons[button_type] & MOUSE_ON_VALUE)
	{
		return true;
	}

	return false;
}

bool OnMousePush(MouseButton button_type)
{
	if (g_PrevMouseState.rgbButtons[button_type] & MOUSE_ON_VALUE &&
		g_CurrentMouseState.rgbButtons[button_type] & MOUSE_ON_VALUE)
	{
		return true;
	}

	return false;
}

bool OnMouseUp(MouseButton button_type)
{
	if (g_PrevMouseState.rgbButtons[button_type] & MOUSE_ON_VALUE &&
		!(g_CurrentMouseState.rgbButtons[button_type] & MOUSE_ON_VALUE))
	{
		return true;
	}

	return false;
}

void UpdateMouse()
{
	Vec2 prev = g_MousePos;
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(FindWindowA(TEXT("XFileDraw"), nullptr), &p);

	g_MousePos.X = (float)p.x;
	g_MousePos.Y = (float)p.y;

	g_MouseMoveVec.X = g_MousePos.X - prev.X;
	g_MouseMoveVec.Y = g_MousePos.Y - prev.Y;
}

Vec2 GetMousePos()
{
	return g_MousePos;
}

void UpdateGamePad()
{

	if (g_GamePadDevice == nullptr)
	{
		return;
	}

	DIJOYSTATE pad_data;
	HRESULT hr = g_GamePadDevice->GetDeviceState(sizeof(DIJOYSTATE), &pad_data);
	if (FAILED(hr))
	{
		if (FAILED(g_GamePadDevice->Acquire()))
		{
			for (int i = 0; i < ButtonKind::ButtonKindMax; i++)
			{
				g_ButtonStates[i] = ButtonState::ButtonStateNone;
			}
		}
	}

	bool is_push[ButtonKind::ButtonKindMax] = { false };

	//���A�i���O�X�e�B�b�N��500�̂Ƃ��Ńf�b�h�]�[������
	if (pad_data.lX < -500)
	{
		is_push[ButtonKind::L_LeftStick] = true;
	}
	else if (pad_data.lX > 500)
	{
		is_push[ButtonKind::L_RightStick] = true;
	}

	if (pad_data.lY < -500)
	{
		is_push[ButtonKind::L_UpStick] = true;
	}
	else if (pad_data.lY > 500)
	{
		is_push[ButtonKind::L_DownStick] = true;
	}
	if (pad_data.lZ > 50000)
	{
		is_push[ButtonKind::LeftTButton] = true;
	}
	else if (pad_data.lZ < 500)
	{
		is_push[ButtonKind::RightTButton] = true;
	}

	if (pad_data.lRx < 10000)
	{
		is_push[ButtonKind::R_LeftStick] = true;
	}
	else if (pad_data.lRx > 40000)
	{
		is_push[ButtonKind::R_RightStick] = true;
	}

	if (pad_data.lRy < 10000)
	{
		is_push[ButtonKind::R_UpStick] = true;
	}
	else if (pad_data.lRy > 40000)
	{
		is_push[ButtonKind::R_DownStick] = true;
	}
	// �\���L�[
	if (pad_data.rgdwPOV[0] != 0xFFFFFFFF)
	{
		float rad = D3DXToRadian((pad_data.rgdwPOV[0] / 100.0f));
		// �{����x��cos�Ay��sin�����ǁArgdwPOV��0���ォ��n�܂�̂ŁA
		// cos��sin���t�ɂ��������s��������
		float x = sinf(rad);
		float y = cosf(rad);

		if (x < -0.01f)
		{
			is_push[ButtonKind::LeftButton] = true;
		}
		else if (x > 0.01f)
		{
			is_push[ButtonKind::RightButton] = true;
		}

		if (y > 0.01f)
		{
			is_push[ButtonKind::UpButton] = true;
		}
		else if (y < -0.01f)
		{
			is_push[ButtonKind::DownButton] = true;
		}
	}

	for (int i = 0; i < 6; ++i)
	{
		if (pad_data.rgbButtons[i] == 0x80)
		{
			is_push[i] = true;
		}
		else {
			is_push[i] = false;
		}
	}


	for (int i = 0; i < ButtonKind::ButtonKindMax; i++)
	{
		if (is_push[i] == true)
		{
			if (g_ButtonStates[i] == ButtonState::ButtonStateNone)
			{
				g_ButtonStates[i] = ButtonState::ButtonStateDown;
			}
			else
			{
				g_ButtonStates[i] = ButtonState::ButtonStatePush;
			}
		}
		else
		{
			if (g_ButtonStates[i] == ButtonState::ButtonStatePush)
			{
				g_ButtonStates[i] = ButtonState::ButtonStateUp;
			}
			else
			{
				g_ButtonStates[i] = ButtonState::ButtonStateNone;
			}
		}
	}
}

bool IsButtonPush(ButtonKind button)
{
	if (g_ButtonStates[button] == ButtonState::ButtonStatePush)
	{
		return true;
	}

	return false;
}

bool IsButtonUp(ButtonKind button)
{
	if (g_ButtonStates[button] == ButtonState::ButtonStateUp)
	{
		return true;
	}

	return false;
}

bool IsButtonDown(ButtonKind button)
{
	if (g_ButtonStates[button] == ButtonState::ButtonStateDown)
	{
		return true;
	}

	return false;
}