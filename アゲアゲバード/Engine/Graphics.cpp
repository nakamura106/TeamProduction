#include "Graphics.h"
#include "Window.h"
#include "FBX.h"

#define	TEXTURE_MAX	1000

static LPDIRECT3D9 g_Interface;
static LPDIRECT3DDEVICE9 g_Device;




bool InitGraphics()
{
	D3DPRESENT_PARAMETERS present_param;
	ZeroMemory(&present_param, sizeof(D3DPRESENT_PARAMETERS));

	if (CreateGraphicsInterface() == false)
	{
		return false;
	}

	if (CreateGraphicsDevice(&present_param) == false)
	{
		return false;
	}

	if (SetUpViewPort(&present_param) == false)
	{
		return false;
	}

	return true;
}

bool CreateGraphicsInterface()
{
	// インターフェース作成
	g_Interface = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_Interface == NULL)
	{
		return false;
	}

	return true;
}

bool CreateGraphicsDevice(D3DPRESENT_PARAMETERS* present_param)
{
	present_param->BackBufferCount = 1;
	present_param->BackBufferFormat = D3DFMT_A8R8G8B8;
	present_param->Windowed = true;
	present_param->SwapEffect = D3DSWAPEFFECT_DISCARD;
	present_param->EnableAutoDepthStencil = true;
	present_param->MultiSampleType = D3DMULTISAMPLE_NONE;
	present_param->MultiSampleQuality = 0;

	// デプスとステンシルバッファのフォーマット設定
	present_param->AutoDepthStencilFormat = D3DFMT_D24S8;

	// もしフルスクリーンなら
	if (present_param->Windowed == false)
	{
		present_param->BackBufferWidth = 1920.0f;
		present_param->BackBufferHeight = 1080.0f;

		present_param->FullScreen_RefreshRateInHz = 60.0f;
	}

	if (FAILED(g_Interface->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		FindWindowA(WINDOW_CLASS_NAME, nullptr),
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
		present_param,
		&g_Device)))
	{
		return false;
	}

	return true;
}

bool SetUpViewPort(D3DPRESENT_PARAMETERS* present_param)
{
	// ビューポートパラメータ
	D3DVIEWPORT9 view_port;

	view_port.X = 0;
	view_port.Y = 0;
	view_port.Width = present_param->BackBufferWidth;
	view_port.Height = present_param->BackBufferHeight;
	view_port.MinZ = 0.0f;
	view_port.MaxZ = 1.0f;

	if (FAILED(g_Device->SetViewport(&view_port)))
	{
		return false;
	}

	return true;
}

void ReleaseGraphics()
{
	g_Device->Release();
	g_Interface->Release();
}

// 描画ステートの設定
void SetRenderMode(ERenderMode mode_, bool enableAlpa_)
{
	IDirect3DDevice9* pDevice = GetD3DDevice();
	// αが無向な場合入力されたカラーをそのまま使う
	DWORD srcColorblend = D3DBLEND_ONE;
	DWORD dstColorblend = D3DBLEND_ZERO;
	if (enableAlpa_)
	{
		// αが有効な場合はα値をカラーに影響させる
		srcColorblend = D3DBLEND_SRCALPHA;
		dstColorblend = D3DBLEND_INVSRCALPHA;
		// αテストでα値が0の場合は描画をしないように設定
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_NOTEQUAL);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	}
	// αブレンドとαテストの有無を設定
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, enableAlpa_);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, enableAlpa_);


	switch (mode_)
	{
	case Normal:
		// αが有効 : (SrcColor * 1)  + (DestColor * 0)
		// αが無効 : (SrcColor * α) + (DestColor * (1 - α))
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, srcColorblend);
		pDevice->SetRenderState(D3DRS_DESTBLEND, dstColorblend);
		break;
	case Add:
		// αが有効：(SrcColor * 1) + (DestColor * 1)
		// αが無効：(SrcColor * α) + (DestColor * 1)
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, srcColorblend);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;
	case Subtract:
		// αが有効：(DestColor * 1) - (SrcColor * 1)
		// αが無効：(DestColor * 1) - (SrcColor * α)
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
		pDevice->SetRenderState(D3DRS_SRCBLEND, srcColorblend);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;
	case Multiple:
		// 共通 : (SrcColor * 0) + (DestColor * SrcColor
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);
		break;
	default:
		break;
	}
}

void DrawStart()
{
	g_Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 255, 255), 1.0f, 0);

	g_Device->BeginScene();
}

void DrawEnd()
{
	g_Device->EndScene();
	g_Device->Present(NULL, NULL, NULL, NULL);
}


const LPDIRECT3DDEVICE9 GetD3DDevice(void)
{
	return g_Device;
}

void SetLight()
{
	D3DLIGHT9 light;
	D3DXVECTOR3 vec_direction(0, 0, 1);
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Direction.x = 0.0f;
	light.Direction.y = -0.5f;
	light.Direction.z = 0.2f;
	light.Diffuse.a = 1.0f;
	light.Diffuse.r = 0.8f;
	light.Diffuse.g = 0.8f;
	light.Diffuse.b = 0.8f;
	light.Ambient.a = 1.0f;
	light.Ambient.r = 0.5f;
	light.Ambient.g = 0.5f;
	light.Ambient.b = 0.5f;
	D3DXVec3Normalize((D3DXVECTOR3*)& light.Direction, &vec_direction);
	light.Range = 200.0f;
	g_Device->SetLight(0, &light);
	g_Device->LightEnable(0, true);
	g_Device->SetRenderState(D3DRS_LIGHTING, true);
}

bool CreateTexture(const char* file_name, Texture* texture_data)
{
	Size size;
	D3DXIMAGE_INFO info;

	// 2の累乗じゃないケースを想定して元のサイズを取得してD3DXCreateTextureFromFileExで使う
	D3DXGetImageInfoFromFileA(file_name, &info);

	if (FAILED(D3DXCreateTextureFromFileExA(g_Device,
		file_name,
		info.Width,
		info.Height,
		1,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0x0000ff00,
		nullptr,
		nullptr,
		&texture_data->TextureData)))
	{
		return false;
	}
	else
	{
		// テクスチャサイズの取得
		D3DSURFACE_DESC desc;

		if (FAILED(texture_data->TextureData->GetLevelDesc(0, &desc)))
		{
			texture_data->TextureData->Release();
			return false;
		}
		texture_data->Width = desc.Width;
		texture_data->Height = desc.Height;
	}

	return true;
}

void DrawTexture(float x, float y, Texture* texture_data)
{
	CUSTOM_VERTEX v[4] =
	{
		{ x, y, 0.0f, 1.0f, 0.0f, 0.0f },
		{ x + texture_data->Width, y, 0.0f, 1.0f, 1.0f, 0.0f },
		{ x + texture_data->Width, y + texture_data->Height, 0.0f, 1.0f, 1.0f, 1.0f },
		{ x, y + texture_data->Height, 0.0f, 1.0f, 0.0f, 1.0f },
	};

	// 頂点構造の指定
	g_Device->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

	g_Device->SetTexture(0, texture_data->TextureData);

	g_Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(CUSTOM_VERTEX));
}