#include <fbxsdk.h>
#include <Windows.h>
#include "Window.h"
#include "Graphics.h"
#include <thread>
#include "Engine.h"
#include "FBX.h"
#include "FbxManager.h"
#include "Input.h"
#include "Camera.h"

//��include
#include"Sound/SoundManager.h"


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

	CAMERA camera(0, 0, -50);

	/*Fbx tori(D3DXVECTOR3(3.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.05f, 0.05f, 0.05f));*/

	FbxManagera manager;
	FBXMeshData player;

	SoundManager::Instance()->RegisterTitleSound();
	SoundManager::Instance()->SoundBGM();
	player = manager.LoadFbxMesh("Res/tori.fbx");
	
	//���ǉ�
	
	//�����܂�

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
	
			


			camera.Update();
			camera.Move();
			camera.MouseRotate();

			D3DXMATRIX mat_world;
			D3DXMatrixIdentity(&mat_world);
			D3DXMatrixTranslation(&mat_world, 0.0f, 0.0f, 0.0f);

			// ���[���h���W���쐬����
			player.fbxinfo.world = mat_world;
			
			manager.Animation(&player, 1.0f / 60.0f);

			DrawStart();

			//SetRenderMode(ERenderMode::Normal, false);

			GetD3DDevice()->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

			SetLight();
			manager.DrawFbx(&player);

			
			DrawEnd();

		}
	}

	manager.ReleaseFbxMesh(&player);
	SoundManager::Instance()->ReleaseTitleSound();

	//ReleaseTexture(NULL);

	// �G���W���I��
	EndEngine();
}