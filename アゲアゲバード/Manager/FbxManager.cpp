#include "FbxManager.h"


MyFbxManager::FbxManager* MyFbxManager::FbxManager::p_instance = 0;

MyFbxManager::FbxManager* MyFbxManager::FbxManager::Instance()
{
	if (p_instance == 0)
	{
		p_instance = new FbxManager();
	}

	return p_instance;
}

MyFbxManager::FbxManager::FbxManager()
{
	if (m_Fbx == nullptr)
	{
		m_Fbx = new Fbx();
	}
	LoadFbxMesh("pot", "Res/FBX/KanAndOilMaya_A.fbx");
	LoadFbxMesh("block", "Res/FBX/tenkasuMaya.fbx");
	LoadFbxMesh("oil", "Res/FBX/FloorOil.fbx");
	LoadFbxMesh("filloil", "Res/FBX/FillOil.fbx");
	LoadFbxMesh("item", "Res/FBX/BallMayaColor.fbx");
	LoadFbxMesh("ItemBox", "Res/FBX/BlockItemMAYA_B.fbx");
	LoadFbxMesh("WorldBox", "Res/FBX/WorldBoxA.fbx");
	//LoadFbxMesh("player", "Res/FBX/PopBird_Export.fbx");
	/*LoadFbxMesh("player_wait", "Res/FBX/PopBirdAnim_Taiki.fbx");
	LoadFbxMesh("player_walk", "Res/FBX/PopBirdAnim_Run.fbx");
	LoadFbxMesh("player_jamp", "Res/FBX/PopBirdAnim_Jump.fbx");	*/

	//LoadFbxMesh("player", "Res/FBX/PopBird_Export.fbx");
	//LoadFbxMesh("player_wait", "Res/FBX/PopBirdAnim_Taiki.fbx");	// <モーション>待機
	//LoadFbxMesh("player_walk", "Res/FBX/PopBirdAnim_Run.fbx");		// <モーション>走る
	//LoadFbxMesh("player_jamp", "Res/FBX/PopBirdAnim_Jump.fbx");	
}

MyFbxManager::FbxManager::~FbxManager()
{
	if (m_Fbx != nullptr)
	{
		delete m_Fbx;
		m_Fbx = nullptr;
	}
}



FBXMeshData MyFbxManager::FbxManager::LoadFbxMesh(std::string key_, const char* pFilename_)
{
	if (HasKey(key_))
	{
		return m_MeshData[key_];
	}
	m_MeshData[key_] = m_Fbx->LoadFbx(pFilename_);
	return m_MeshData[key_];
}

void MyFbxManager::FbxManager::ReleaseFbxMesh(std::string key_)
{
	m_Fbx->ReleaseFbxMesh(&m_MeshData[key_]);
}

void MyFbxManager::FbxManager::AllReleaseMesh(FBXMeshData* meshdata_)
{
	if (meshdata_ == nullptr) { return; }
	m_Fbx->ReleaseFbxMesh(meshdata_);
}

void MyFbxManager::FbxManager::DrawFbx(std::string key_, D3DXMATRIX& mat_world_)
{
	m_MeshData[key_].fbxinfo.world = mat_world_;
	m_Fbx->RenderFbxMesh(&m_MeshData[key_]);
}

void MyFbxManager::FbxManager::Animation(std::string key_,float sec_)
{
	
	m_Fbx->Animate(&m_MeshData[key_], sec_); 
	
}

void MyFbxManager::FbxManager::ResetAnimation(FBXMeshData* meshdata_)
{
	if (meshdata_ == nullptr) { return; }
	m_Fbx->ResetAnimate(meshdata_);
}

bool MyFbxManager::FbxManager::HasKey(std::string key_)
{
	auto itr=m_MeshData.find(key_);
	if (itr != m_MeshData.end())
	{
		return true;
	}
	return false;
}
