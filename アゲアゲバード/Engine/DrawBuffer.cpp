#include "DrawBuffer.h"

// ���_�o�b�t�@�̐���
IDirect3DVertexBuffer9* CreateVertexBuffer(const void* pVertices, UINT size)
{
	IDirect3DVertexBuffer9* pVertexBuffer;
	IDirect3DDevice9* pDevice = GetD3DDevice();
	// �w�肵���T�C�Y�̒��_�o�b�t�@���쐬
	if (FAILED(pDevice->CreateVertexBuffer(size, 0, 0, D3DPOOL_MANAGED, &pVertexBuffer, NULL)))
	{
		return NULL;
	}

	if (pVertices)
	{
		void* pData;
		// �o�b�t�@�����b�N���ăf�[�^����������
		if (SUCCEEDED(pVertexBuffer->Lock(0, size, &pData, 0)))
		{
			memcpy(pData, pVertices, size);
			pVertexBuffer->Unlock();
		}
	}
	return pVertexBuffer;
}

// �C���f�b�N�X�o�b�t�@�̐���
IDirect3DIndexBuffer9* CreateIndexBuffer(const UINT16* pIndeces, UINT size)
{
	IDirect3DIndexBuffer9* pIndexBuffer;
	IDirect3DDevice9* pDevice = GetD3DDevice();
	// 16byte�^�̃C���f�b�N�X�o�b�t�@���쐬
	if (FAILED(pDevice->CreateIndexBuffer(size, 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &pIndexBuffer, NULL)))
	{
		return NULL;
	}
	if (pIndeces)
	{
		void* pData;
		// �o�b�t�@�����b�N���ăf�[�^����������
		if (SUCCEEDED(pIndexBuffer->Lock(0, size, &pData, 0)))
		{
			memcpy(pData, pIndeces, size);
			pIndexBuffer->Unlock();
		}
	}
	return pIndexBuffer;
}