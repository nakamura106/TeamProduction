#include "Pot.h"

Pot::Pot()
{
	m_object=m_manager.LoadFbxMesh("Res/FBX/nabeMaya100m.fbx");
	D3DXMatrixIdentity(&m_mat_world);
	D3DXMatrixScaling(&m_mat_scall, 50.0f, 100.0f, 50.0f);
	D3DXMatrixTranslation(&m_mat_move,0.0f,-1.0f,0.0f);
	D3DXMatrixMultiply(&m_mat_world, &m_mat_move, &m_mat_scall);
	m_object.fbxinfo.world = m_mat_world;
	
}
