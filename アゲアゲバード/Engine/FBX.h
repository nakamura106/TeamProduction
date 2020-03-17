#ifndef FBX_H
#define FBX_H
#include <d3dx9.h>
#include <string>
#include <vector>
#include <fbxsdk.h>
#include "Graphics.h"
#include <map>
#include <iostream>

//���_�̏��
struct VERTEX_3D {
	D3DXVECTOR3 pos;
	D3DXVECTOR3 nor;
	D3DCOLOR    col;
	float u, v;
	// �X�L�����b�V���p
	BYTE index[4];
	float weight[4];

};

// �{�[�����
struct Bone
{
	char		name[64];
	D3DXMATRIX	offset;
	D3DXMATRIX	transform;
};
//�}�e���A���̏��
struct MaterialData
{
	TEXTURE_DATA textureData;	// �e�N�X�`���\
	D3DMATERIAL9 material;		// �}�e���A��
};

//���b�V���̏��
struct MeshData {
	//�|���S���̐�
	int polygonCount;
	//���_�̐�
	int vertexCount;
	//���_�C���f�b�N�X�̐�
	int indexCount;
	// 1���_�ӂ�̃T�C�Y
	int vertexStride;
	//�}�e���A���ԍ�
	int materialIndex;

	int uvSetCount;
	//���_
	VERTEX_3D* vertex;
	//���_�o�b�t�@
	IDirect3DVertexBuffer9* pVB;
	//�C���f�b�N�X�o�b�t�@
	IDirect3DIndexBuffer9* pIB;
};
static const int BONE_MAX = 256;

//	�A�j���[�V����
struct Motion
{
	Motion()
	{
		ZeroMemory(pKey, sizeof(pKey));
	}

	UINT		numFrame;		// �t���[����	
	D3DXMATRIX* pKey[BONE_MAX];	// �L�[�t���[��
};



//FBX�̏��
struct FbxInfo {
	//���b�V��
	MeshData* pMesh;
	//���b�V���̐�
	int meshcount;
	//�}�e���A��
	MaterialData* pMaterial;
	//�}�e���A���̐�
	int materialcount;

	Bone bone[BONE_MAX];	// �{�[�����
	int bonecount;
	int	startFrame;		// �J�n�t���[��
	std::map<std::string, Motion>* pMotion;		// ���[�V����
	D3DXMATRIX						world;			// ���[���h�}�g���b�N�X
};

struct FBXMeshData
{
	FbxInfo fbxinfo;
	char	motion[64];	// ���[�V������
	float	frame;		// �t���[��
};



enum class Object
{
	PLAYER,
	MaxObject
};

class Fbx
{
public:
	/*Fbx(D3DXVECTOR3 Pos, D3DXVECTOR3 Scale):
		m_Pos(Pos),
		m_Scale(Scale)
	{}*/

	Fbx() {}

	~Fbx() {}



	//FBX����
	FBXMeshData LoadFbx(const char* file_name);

	bool LoadMesh(MeshData* pMeshData_, FbxMesh* pMesh_);

	void ReleaseFbxMesh(FBXMeshData* pData_);

	void GetIndeces(MeshData* pMeshData_, FbxMesh* pMesh_);
	//���_���擾
	void GetVertex(MeshData* pMeshData_, FbxMesh* pMesh_);
	//�@�����擾
	void GetNormal(MeshData* pMeshData_, FbxMesh* pMesh_);
	//UV���W�̎擾
	void GetUV(MeshData* pMeshData_, FbxMesh* pMesh_);
	//�J���[�擾
	void GetColor(MeshData* pMeshData_, FbxMesh* pMesh_);

	int FindBone(FbxInfo* pModel_, const char* pName_);

	void GetBone(FbxInfo* pModel_, MeshData* pMeshData_, FbxMesh* pMesh_);

	void GetKeyFrames(FbxInfo* pModel_, std::string name_, int bone_, FbxNode* pBoneNode_);

	void Play(FBXMeshData* pData_, std::string name_);
	//�e�N�X�`�����擾
	void GetTextureInfo(MaterialData* pMaterialData_, FbxMesh* pMesh_);
	//�A�j���[�V��������
	void RenderFbxMesh(FBXMeshData* pData_);

	void DrawModel(FbxInfo* pModel);

	void Skinning(FBXMeshData* pData_);

	void MatrixInterporate(D3DXMATRIX& out_, D3DXMATRIX& A_, D3DXMATRIX B_, float rate_);

	void ReleaseModel(FbxInfo* pModel);

	void Animate(FBXMeshData* pData_, float sec_);

	void ResetAnimate(FBXMeshData* pData_);
private:




	D3DXVECTOR3 m_Pos;
	D3DXVECTOR3 m_Scale;

	char m_RootPath[MAX_PATH]; // �t�@�C���̃p�X
};

#endif