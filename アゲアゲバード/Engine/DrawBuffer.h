#ifndef DRAWBUFFER_H_
#define DRAWBUFFER_H_

#include "Graphics.h"

// ���_�o�b�t�@�̐���
IDirect3DVertexBuffer9* CreateVertexBuffer(const void* pVertices, UINT size);
// �C���f�b�N�X�o�b�t�@�̐���
IDirect3DIndexBuffer9* CreateIndexBuffer(const UINT16* pIndeces, UINT size);



#endif