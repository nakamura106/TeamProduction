#include "Pot.h"

Pot::Pot()
{
	m_key = "pot";
	D3DXMatrixIdentity(&m_mat_world);
	D3DXMatrixScaling(&m_mat_scall, 30.0f, 30.0f, 30.0f);
	D3DXMatrixTranslation(&m_mat_move,0.0f,0.0f,0.0f);
	D3DXMatrixMultiply(&m_mat_world, &m_mat_scall,  & m_mat_move);
}
