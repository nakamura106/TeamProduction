#include"ObjectBase.h"

ObjectBase::ObjectBase()
{
	D3DXMatrixIdentity(&m_mat_world);
	m_object.fbxinfo.world = m_mat_world;
}

ObjectBase::~ObjectBase()
{
	m_manager.ReleaseFbxMesh(&m_object);
}

void ObjectBase::Draw()
{
	m_manager.DrawFbx(&m_object);
}

void ObjectBase::Update()
{
	m_manager.Animation(&m_object, 1.0f / 60.0f);

}