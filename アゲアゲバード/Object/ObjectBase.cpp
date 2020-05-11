#include"ObjectBase.h"

ObjectBase::ObjectBase()
{
	
}

ObjectBase::~ObjectBase()
{
	MyFbxManager::FbxManager::Instance()->AllReleaseMesh(&m_ObjectData.m_object);
}

void ObjectBase::Draw()
{
	MyFbxManager::FbxManager::Instance()->DrawFbx(m_ObjectData.m_key, m_ObjectData.m_mat_world);
}

void ObjectBase::Update()
{
	MyFbxManager::FbxManager::Instance()->Animation(m_ObjectData.m_key, 1.0f / 60.0f);
}