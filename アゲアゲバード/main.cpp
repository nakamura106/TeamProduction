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
#include "PlayerManager.h"

//��include
#include"Manager/SoundManager.h"


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

	//CAMERA camera(0, 0, 0);

	/*Fbx tori(D3DXVECTOR3(3.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.05f, 0.05f, 0.05f));*/

	//FbxManagera manager;
	//FBXMeshData player;
	//FBXMeshData bg_box;
	//FBXMeshData nabe;
	//FBXMeshData block;
	Pot pot;


	SoundManager::Instance()->RegisterTitleSound();
	SoundManager::Instance()->SoundBGM();
	//player = manager.LoadFbxMesh("Res/PopBird_Export.fbx");
	////bg_box = manager.LoadFbxMesh("Res/worldBox.fbx");
	//nabe = manager.LoadFbxMesh("Res/nabemaya.fbx");
	////block = manager.LoadFbxMesh("Res/tenkasu.fbx");

	PlayerManager pmanager;

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

			/*D3DXMATRIX mat_world;
			D3DXMATRIX mat_nabe;

			D3DXMatrixIdentity(&mat_world);
			D3DXMatrixIdentity(&mat_nabe);
			D3DXMatrixTranslation(&mat_world, 0.0f, 10.0f, 0.0f);
			D3DXMatrixTranslation(&mat_nabe, 0.0f, 0.0f, 0.0f);
*/
			//D3DXMatrixRotationX(&mat_nabe, D3DXToRadian(-90));



//			// ���[���h���W���쐬����
//			player.fbxinfo.world = mat_world;
//
//			//bg_box.fbxinfo.world = mat_world;
//
//			nabe.fbxinfo.world = mat_nabe;
//
//			/*block.fbxinfo.world = mat_world;
//*/
			pot.Update();



			DrawStart();

			SetRenderMode(ERenderMode::Normal, false);

			GetD3DDevice()->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			GetD3DDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);	

			SetLight();
		/*	manager.DrawFbx(&player);
			manager.DrawFbx(&bg_box);
			manager.DrawFbx(&nabe);
			manager.DrawFbx(&block);*/
			pot.Draw();

			pmanager.Draw();

			DrawEnd();

		}
	}

	//manager.ReleaseFbxMesh(&player);
	////manager.ReleaseFbxMesh(&bg_box);
	//manager.ReleaseFbxMesh(&nabe);
	////manager.ReleaseFbxMesh(&block);
	SoundManager::Instance()->ReleaseTitleSound();

	//ReleaseTexture(NULL);

	// �G���W���I��
	EndEngine();
}