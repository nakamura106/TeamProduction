#include"ObjectBase.h"

ObjectBase::ObjectBase()
{
	
}

ObjectBase::~ObjectBase()
{
	MyFbxManager::FbxManager::Instance()->AllReleaseMesh(&m_object);
}

void ObjectBase::Draw()
{
	MyFbxManager::FbxManager::Instance()->DrawFbx(m_key,m_mat_world);
}

void ObjectBase::Update()
{
	MyFbxManager::FbxManager::Instance()->Animation(m_key, 1.0f / 60.0f);
}