#include <fbxsdk.h>
#include <Windows.h>
#include "Engine/Window.h"
#include "Engine/Graphics.h"
#include <thread>
#include "Engine/Engine.h"
#include "Engine/FBX.h"
#include "Manager/FbxManager.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include"Object/Pot.h"
#include"Manager/ObjectManager.h"
#include"Manager/SoundManager.h"
#include"Manager/UIManager.h"
#include"DataBank/DataBank.h"
#include"Manager/SceneManager.h"
#include"Utility/Collision.h"


int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmpLine,
	INT nCmdShow)
{
	// �G���W���̏�����
	if (InitEngine(1920, 1080, "�A�Q�A�Q�o�[�h") == false)
	{
		return 0;
	}

	SceneManager::Instance()->Init();

	while (true)
	{
		bool message_ret = false;
		MSG msg;

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else if (msg.message == WM_CLOSE)
			{
				break;
			}
			else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			
			SceneManager::Instance()->Update();
			
			SceneManager::Instance()->Draw();
			
		}
	}
	
	// �G���W���I��
	EndEngine();
}