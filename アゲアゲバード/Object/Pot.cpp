#include "Pot.h"

Pot::Pot()
{
	m_object=m_manager.LoadFbxMesh("Res/FBX/KanMaya2.fbx");
	D3DXMatrixIdentity(&m_mat_world);
	D3DXMatrixScaling(&m_mat_scall, 30.0f, 30.0f, 30.0f);
	D3DXMatrixTranslation(&m_mat_move,0.0f,0.0f,0.0f);
	D3DXMatrixMultiply(&m_mat_world, &m_mat_move, &m_mat_scall);
	m_object.fbxinfo.world = m_mat_world;
}
