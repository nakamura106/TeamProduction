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
#include "PlayerManager.h"

//仮include
#include"Manager/SoundManager.h"


int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmpLine,
	INT nCmdShow)
{
	// エンジンの初期化
	if (InitEngine(1920, 1080, "アゲアゲバード") == false)
	{
		return 0;
	}

	//CAMERA camera(0, 0, 0);


	
	ObjectManager::Instance()->CreateObject();
	

	SoundManager::Instance()->RegisterTitleSound();
	SoundManager::Instance()->SoundBGM();
	

	PlayerManager pmanager;
	pmanager.Init();

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
			UpdateInput();
			KeyStateUpdate();


			pmanager.Update();

			/*camera->Update();
			camera->Move();
			camera->MouseRotate();*/

		
			ObjectManager::Instance()->Update();

			if (GetKeyDown(SPACE_KEY))
			{
				ObjectManager::Instance()->CreateBlock();
			}


			DrawStart();

			SetRenderMode(ERenderMode::Normal, false);

			GetD3DDevice()->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			GetD3DDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);	

			SetLight();
		
			ObjectManager::Instance()->Draw();

			pmanager.Draw();

			DrawEnd();

		}
	}

	
	SoundManager::Instance()->ReleaseTitleSound();

	

	// エンジン終了
	EndEngine();
}