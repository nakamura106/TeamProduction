#include "Pot.h"

Pot::Pot()
{
	m_object=m_manager.LoadFbxMesh("Res/nabemaya.fbx");
	D3DXMatrixIdentity(&m_mat_world);
	D3DXMatrixScaling(&m_mat_world, 10000.0f, 10000.0f, 10000.0f);
	D3DXMatrixTranslation(&m_mat_world,0.0f,-1.0f,0.0f);
	m_object.fbxinfo.world = m_mat_world;
}
