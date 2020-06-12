#include <fbxsdk.h>
#include <Windows.h>
#include <thread>
#include "Engine/Window.h"
#include "Engine/Graphics.h"
#include "Engine/Engine.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include"Manager/UIManager.h"
#include"Manager/SceneManager.h"

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

	UIManager::Instance()->CreateUI();
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
	
	// エンジン終了
	EndEngine();
}