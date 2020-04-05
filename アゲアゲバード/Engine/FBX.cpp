#include "FBX.h"
#include "DrawBuffer.h"

#pragma region �ǂݍ���
// �}�e���A�����̏�����
void InitMaterial(MaterialData* pMaterial, int materialNum)
{
	ZeroMemory(pMaterial, sizeof(MaterialData) * materialNum);

	D3DMATERIAL9 material;
	//	�ގ��ݒ�
	//	�A���r�G���g(��)�J���[
	material.Ambient.r = 1.0f;
	material.Ambient.g = 1.0f;
	material.Ambient.b = 1.0f;
	material.Ambient.a = 1.0f;
	//	�f�B�t���[�Y(�f�ނ�)�J���[
	material.Diffuse.r = 1.0f;
	material.Diffuse.g = 1.0f;
	material.Diffuse.b = 1.0f;
	material.Diffuse.a = 1.0f;
	//	�X�y�L�����[�i�e�J��j�J���[
	material.Specular.r = 1.0f;
	material.Specular.g = 1.0f;
	material.Specular.b = 1.0f;
	material.Specular.a = 1.0f;
	material.Power = 15.0f;
	//	�G�~�b�V�u�i�����j
	material.Emissive.r = 0.0f;
	material.Emissive.g = 0.0f;
	material.Emissive.b = 0.0f;
	material.Emissive.a = 0.0f;

	for (int i = 0; i < materialNum; i++)
	{
		pMaterial[i].material = material;
	}
}

//FBX�̃}�l�[�W���[�쐬
FBXMeshData Fbx::LoadFbx(const char* file_name)
{
	FBXMeshData fbxMeshData;
	ZeroMemory(&fbxMeshData, sizeof(fbxMeshData));

	strcpy_s(m_RootPath, file_name);
	UINT i;
	for (i = strlen(m_RootPath); 0 < i; i--)
	{
		if (m_RootPath[i] == '/') break;
	}
	m_RootPath[i] = '\0';

	//FBX�̃}�l�[�W���[�쐬
	FbxManager* m_manager = FbxManager::Create();
	//�C���|�[�^�[�쐬
	FbxImporter* importer = FbxImporter::Create(m_manager, "");
	//�V�[���쐬
	FbxScene* m_scene = FbxScene::Create(m_manager, "");
	//FBX�ɑ΂�����o��
	FbxIOSettings* ios = FbxIOSettings::Create(m_manager, IOSROOT);

	//filePath�Ɏw�肵���t�@�C����ǂݍ���
	importer->Initialize(file_name);
	//�V�[���ɃC���|�[�g�����t�@�C����n��
	bool result = importer->Import(m_scene);
	//�C���|�[�^�[�̖�ڂ͏I���Ȃ̂ŉ������
	SAFE_DESTROY(importer);


	//�V�[���̃|���S�����O�p�ɂ���
	fbxsdk::FbxGeometryConverter geometryConverter(m_manager);
	// �}�e���A����1���b�V�����ɕ�����
	geometryConverter.SplitMeshesPerMaterial(m_scene, true);
	geometryConverter.Triangulate(m_scene, true);

	//���b�V���擾
	int meshcount = m_scene->GetSrcObjectCount<FbxMesh>();
	MeshData* pMeshData = (MeshData*)malloc(meshcount * sizeof(MeshData));
	ZeroMemory(pMeshData, meshcount * sizeof(MeshData));

	// �}�e���A�����̃o�b�t�@���m��
	int materialcount = meshcount;
	MaterialData* pMaterialData = (MaterialData*)malloc(materialcount * sizeof(MaterialData));
	ZeroMemory(pMaterialData, materialcount * sizeof(MaterialData));


	D3DXMatrixIdentity(&fbxMeshData.fbxinfo.world);
	fbxMeshData.fbxinfo.meshcount = meshcount;
	fbxMeshData.fbxinfo.pMesh = pMeshData;
	fbxMeshData.fbxinfo.materialcount = materialcount;
	fbxMeshData.fbxinfo.pMaterial = pMaterialData;
	fbxMeshData.fbxinfo.bonecount = 0;
	ZeroMemory(fbxMeshData.fbxinfo.bone, sizeof(fbxMeshData.fbxinfo.bone));

	//	���[�V�������擾
	FbxArray<FbxString*> names;
	m_scene->FillAnimStackNameArray(names);

	int StartFrame = 0;
	if (names != NULL) {
		//	���[�V���������݂���Ƃ�
		FbxTakeInfo* take = m_scene->GetTakeInfo(names[0]->Buffer());
		FbxLongLong start = take->mLocalTimeSpan.GetStart().Get();
		FbxLongLong stop = take->mLocalTimeSpan.GetStop().Get();
		FbxLongLong fps60 = FbxTime::GetOneFrameValue(FbxTime::eFrames60);
		StartFrame = (int)(start / fps60);

		fbxMeshData.fbxinfo.pMotion = new std::map<std::string, Motion>();
		(*fbxMeshData.fbxinfo.pMotion)["default"].numFrame = (int)((stop - start) / fps60);
	}
	fbxMeshData.fbxinfo.startFrame = StartFrame;

	// ���b�V���P�ʂœW�J���Ă���
	for (int i = 0; i < meshcount; i++)
	{
		FbxMesh* pMesh = m_scene->GetSrcObject<FbxMesh>(i);

		LoadMesh(&pMeshData[i], pMesh);
		GetTextureInfo(&pMaterialData[i], pMesh);
		GetBone(&fbxMeshData.fbxinfo, &pMeshData[i], pMesh);
		pMeshData[i].materialIndex = i;
	}


	SAFE_DESTROY(m_scene);
	SAFE_DESTROY(m_manager);

	Play(&fbxMeshData, "default");

	return fbxMeshData;

}

void Fbx::Play(FBXMeshData * pData_, std::string name_)
{
	if (pData_ == nullptr) return;
	strcpy_s(pData_->motion, name_.c_str());
	pData_->frame = 0.0f;
}

void Fbx::ReleaseFbxMesh(FBXMeshData * pData_)
{
	if (pData_ == nullptr) return;

	ReleaseModel(&pData_->fbxinfo);
}

//�e���擾
bool Fbx::LoadMesh(MeshData * pMeshData_, FbxMesh * pMesh_)
{
	GetIndeces(pMeshData_, pMesh_);

	GetVertex(pMeshData_, pMesh_);
	GetUV(pMeshData_, pMesh_);
	GetColor(pMeshData_, pMesh_);
	GetNormal(pMeshData_, pMesh_);

	int vertexNum = pMesh_->GetPolygonVertexCount();
	UINT size = (UINT)(vertexNum * sizeof(VERTEX_3D));
	VERTEX_3D* vertex;
	// �o�b�t�@�����b�N���ăf�[�^����������
	pMeshData_->pVB->Lock(0, size, (void**)& vertex, 0);

	pMeshData_->vertex = (VERTEX_3D*)malloc(size);
	memcpy(pMeshData_->vertex, vertex, size);

	pMeshData_->pVB->Unlock();

	return true;
}

//�|���S�����
void Fbx::GetIndeces(MeshData * pMeshData_, FbxMesh * pMesh_)
{
	int polyCount = pMesh_->GetPolygonCount();
	UINT size = (UINT)((polyCount * 3) * sizeof(UINT16));

	pMeshData_->polygonCount = (UINT)polyCount;
	pMeshData_->indexCount = (UINT)(polyCount * 3);
	pMeshData_->pIB = CreateIndexBuffer(NULL, size);

	UINT16* pIndeces;
	// �o�b�t�@�����b�N���ăf�[�^����������
	pMeshData_->pIB->Lock(0, size, (void**)& pIndeces, 0);

	for (int polyIdx = 0; polyIdx < polyCount; polyIdx++)
	{
		pIndeces[polyIdx * 3 + 0] = polyIdx * 3 + 2;
		pIndeces[polyIdx * 3 + 1] = polyIdx * 3 + 1;
		pIndeces[polyIdx * 3 + 2] = polyIdx * 3 + 0;
	}
	pMeshData_->pIB->Unlock();
}
//���_���
void Fbx::GetVertex(MeshData * pMeshData_, FbxMesh * pMesh_) {

	int vertexCount = pMesh_->GetPolygonVertexCount();
	UINT size = (UINT)(vertexCount * sizeof(VERTEX_3D));

	//���b�V���Ɋ܂܂�钸�_���WpMesh_���擾
	FbxVector4* vtx = pMesh_->GetControlPoints();
	// ���b�V���̃g�����X�t�H�[��
	FbxVector4 T = pMesh_->GetNode()->GetGeometricTranslation(FbxNode::eSourcePivot);
	FbxVector4 R = pMesh_->GetNode()->GetGeometricRotation(FbxNode::eSourcePivot);
	FbxVector4 S = pMesh_->GetNode()->GetGeometricScaling(FbxNode::eSourcePivot);
	FbxAMatrix TRS = FbxAMatrix(T, R, S);
	//	�S���_�ϊ�
	for (int v = 0; v < pMesh_->GetControlPointsCount(); v++)
	{
		vtx[v] = TRS.MultT(vtx[v]);
	}

	pMeshData_->vertexCount = (UINT)vertexCount;
	pMeshData_->vertexStride = sizeof(VERTEX_3D);
	pMeshData_->pVB = CreateVertexBuffer(NULL, size);

	VERTEX_3D* pVertex;
	// �o�b�t�@�����b�N���ăf�[�^����������
	pMeshData_->pVB->Lock(0, size, (void**)& pVertex, 0);
	int* pIndex = pMesh_->GetPolygonVertices();
	for (int vIdx = 0; vIdx < vertexCount; vIdx++)
	{
		pVertex[vIdx].pos.x = -vtx[pIndex[vIdx]][0];
		pVertex[vIdx].pos.y = vtx[pIndex[vIdx]][1];
		pVertex[vIdx].pos.z = vtx[pIndex[vIdx]][2];
		pVertex[vIdx].nor.x = 0.0f;
		pVertex[vIdx].nor.y = 1.0f;
		pVertex[vIdx].nor.z = 0.0f;
		pVertex[vIdx].u = 0.0f;
		pVertex[vIdx].v = 0.0f;
		pVertex[vIdx].col = 0xffffff;
		ZeroMemory(pVertex[vIdx].index, sizeof(pVertex[vIdx].index));
		ZeroMemory(pVertex[vIdx].weight, sizeof(pVertex[vIdx].weight));
	}

	pMeshData_->pVB->Unlock();

}
//�@�����擾
void Fbx::GetNormal(MeshData * pMeshData_, FbxMesh * pMesh_) {
	FbxArray<FbxVector4> normals;

	//�@�����擾
	pMesh_->GetPolygonVertexNormals(normals);

	UINT size = pMeshData_->vertexCount * sizeof(VERTEX_3D);
	VERTEX_3D* pVertex;
	// �o�b�t�@�����b�N���ăf�[�^����������
	pMeshData_->pVB->Lock(0, size, (void**)& pVertex, 0);

	//�@���̐����擾
	//int normalCount = normals.Size();
	for (int vtxIdx = 0; vtxIdx < normals.Size(); vtxIdx++)
	{
		FbxVector4& normal = normals[vtxIdx];
		//���_�C���f�b�N�X�ɑΉ��������_�ɒl����
		pVertex[vtxIdx].nor.x = (float)normal[0];
		pVertex[vtxIdx].nor.y = (float)normal[1];
		pVertex[vtxIdx].nor.z = (float)normal[2];
	}
	pMeshData_->pVB->Unlock();

}
//UV���擾
void Fbx::GetUV(MeshData * pMeshData_, FbxMesh * pMesh_) {

	FbxStringList uvsetName;
	//���b�V���Ɋ܂܂��UVSet�������ׂĎ擾
	pMesh_->GetUVSetNames(uvsetName);

	FbxArray<FbxVector2> uvSets;
	pMesh_->GetPolygonVertexUVs(uvsetName.GetStringAt(0), uvSets);

	UINT size = pMeshData_->vertexCount * sizeof(VERTEX_3D);

	VERTEX_3D* pVertex;
	// �o�b�t�@�����b�N���ăf�[�^����������
	pMeshData_->pVB->Lock(0, size, (void**)& pVertex, 0);
	for (int vtxIdx = 0; vtxIdx < uvSets.Size(); vtxIdx++)
	{
		FbxVector2& uvSet = uvSets[vtxIdx];

		pVertex[vtxIdx].u = (float)uvSet[0];
		pVertex[vtxIdx].v = (float)(1.0 - uvSet[1]);
	}
	pMeshData_->pVB->Unlock();
}
//�J���[���擾
void Fbx::GetColor(MeshData * pMeshData_, FbxMesh * pMesh_)
{
	int colorElementCount = pMesh_->GetElementVertexColorCount();
	if (colorElementCount == 0) return;

	FbxLayerElementVertexColor * pColor = pMesh_->GetElementVertexColor(0);

	FbxLayerElement::EMappingMode mapMode = pColor->GetMappingMode();
	FbxLayerElement::EReferenceMode refMode = pColor->GetReferenceMode();

	if (mapMode == FbxLayerElement::eByPolygonVertex)
	{
		if (refMode == FbxLayerElement::eIndexToDirect)
		{
			UINT size = pMeshData_->vertexCount * sizeof(VERTEX_3D);
			VERTEX_3D* pVertex;
			// �o�b�t�@�����b�N���ăf�[�^����������
			pMeshData_->pVB->Lock(0, size, (void**)& pVertex, 0);

			FbxLayerElementArrayTemplate<FbxColor>& colors = pColor->GetDirectArray();
			FbxLayerElementArrayTemplate<int>& indeces = pColor->GetIndexArray();
			for (int i = 0; i < indeces.GetCount(); i++)
			{
				const FbxColor& color = colors.GetAt(indeces.GetAt(i));
				DWORD a = (DWORD)(color.mAlpha * 255.0);
				DWORD r = (DWORD)(color.mRed * 255.0);
				DWORD g = (DWORD)(color.mGreen * 255.0);
				DWORD b = (DWORD)(color.mBlue * 255.0);

				pVertex[i].col = (a << 24) + (r << 16) + (g << 8) + (b);
			}
			pMeshData_->pVB->Unlock();
		}
	}
}
//����񌟍�
int Fbx::FindBone(FbxInfo * pModel_, const char* pName_)
{
	for (UINT boneIdx = 0; boneIdx < pModel_->bonecount; boneIdx++)
	{
		if (strcmp(pModel_->bone[boneIdx].name, pName_) == 0)
		{
			return (int)boneIdx;
		}
	}
	return -1;
}
//�����擾
void Fbx::GetBone(FbxInfo * pModel_, MeshData * pMeshData_, FbxMesh * pMesh_)
{
	// �X�L�����̗L��
	int skinCount = pMesh_->GetDeformerCount(FbxDeformer::eSkin);
	if (skinCount <= 0)
	{
		return;
	}
	int vertexcount = pMeshData_->vertexCount;
	UINT size = (UINT)(vertexcount * sizeof(VERTEX_3D));

	VERTEX_3D* pVertex;
	// �o�b�t�@�����b�N���ăf�[�^����������
	pMeshData_->pVB->Lock(0, size, (void**)& pVertex, 0);

	FbxSkin* pSkin = (FbxSkin*)pMesh_->GetDeformer(0, FbxDeformer::eSkin);
	// �{�[����
	int nBone = pSkin->GetClusterCount();
	//	�S�{�[�����擾
	for (int bone = 0; bone < nBone; bone++)
	{
		//	�{�[�����擾
		FbxCluster* pCluster = pSkin->GetCluster(bone);
		FbxAMatrix trans;
		pCluster->GetTransformMatrix(trans);
		trans.mData[0][1] *= -1;
		trans.mData[0][2] *= -1;
		trans.mData[1][0] *= -1;
		trans.mData[2][0] *= -1;
		trans.mData[3][0] *= -1;

		//	�{�[�����擾
		const char* pName = pCluster->GetLink()->GetName();

		Bone* pBone;
		//	�{�[������
		int bone_no = FindBone(pModel_, pName);
		if (bone_no != -1)
		{
			pBone = &pModel_->bone[bone_no];
		}
		else
		{
			bone_no = pModel_->bonecount;
			pBone = &pModel_->bone[bone_no];
			pModel_->bonecount++;

			strcpy_s(pBone->name, pName);
			//	�I�t�Z�b�g�s��쐬
			FbxAMatrix LinkMatrix;
			pCluster->GetTransformLinkMatrix(LinkMatrix);
			LinkMatrix.mData[0][1] *= -1;
			LinkMatrix.mData[0][2] *= -1;
			LinkMatrix.mData[1][0] *= -1;
			LinkMatrix.mData[2][0] *= -1;
			LinkMatrix.mData[3][0] *= -1;

			FbxAMatrix Offset = LinkMatrix.Inverse() * trans;
			FbxDouble* OffsetM = (FbxDouble*)Offset;

			//	�I�t�Z�b�g�s��ۑ�
			for (int i = 0; i < 16; i++)
			{
				pBone->offset.m[i / 4][i % 4] = (float)OffsetM[i];
			}
			//	�L�[�t���[���ǂݍ���
			GetKeyFrames(pModel_, "default", bone_no, pCluster->GetLink());
		}

		//	�E�F�C�g�ǂݍ���
		int weightCount = pCluster->GetControlPointIndicesCount();
		int* pWeightIndex = pCluster->GetControlPointIndices();
		double* wgt = pCluster->GetControlPointWeights();

		int* index = pMesh_->GetPolygonVertices();


		for (int i = 0; i < weightCount; i++)
		{
			int wgtIdx2 = pWeightIndex[i];
			//	�S�|���S������wgtIdx2�Ԗڂ̒��_����
			for (int vtxIdx = 0; vtxIdx < vertexcount; vtxIdx++)
			{
				if (index[vtxIdx] != wgtIdx2) continue;
				//	���_�ɃE�F�C�g�ۑ�
				int weightCount;
				for (weightCount = 0; weightCount < 4; weightCount++)
				{
					if (pVertex[vtxIdx].weight[weightCount] <= 0.0f)
					{
						break;
					}
				}
				if (4 <= weightCount) continue;

				pVertex[vtxIdx].index[weightCount] = bone_no;
				pVertex[vtxIdx].weight[weightCount] = (float)wgt[i];
			}
		}
	}
	//	�E�F�C�g���K��
	// �T�{�ȏ�ɂ܂������Ă�ꍇ�̂���
	for (int vtxIdx = 0; vtxIdx < vertexcount; vtxIdx++)
	{
		float n = 0;
		int weightCount;
		//	���_�̃E�F�C�g�̍��v�l
		for (weightCount = 0; weightCount < 4; weightCount++)
		{
			if (pVertex[vtxIdx].weight[weightCount] <= 0.0f)
			{
				break;
			}
			n += pVertex[vtxIdx].weight[weightCount];
		}
		//	���K��
		for (weightCount = 0; weightCount < 4; weightCount++)
		{
			pVertex[vtxIdx].weight[weightCount] /= n;
		}
	}
	pMeshData_->pVB->Unlock();
}

void Fbx::GetKeyFrames(FbxInfo * pModel_, std::string name_, int bone_, FbxNode * pBoneNode_)
{
	//	�������m��
	Motion* pMotion = &(*pModel_->pMotion)[name_];
	pMotion->pKey[bone_] = (D3DXMATRIX*)malloc(sizeof(D3DXMATRIX) * (pMotion->numFrame + 1));

	double time = (double)pModel_->startFrame * (1.0 / 60);
	FbxTime T;
	for (UINT f = 0; f < pMotion->numFrame; f++)
	{
		T.SetSecondDouble(time);
		//	T�b�̎p���s���Get
		FbxMatrix m = pBoneNode_->EvaluateGlobalTransform(T);
		m.mData[0][1] *= -1;// _12
		m.mData[0][2] *= -1;// _13
		m.mData[1][0] *= -1;// _21
		m.mData[2][0] *= -1;// _31
		m.mData[3][0] *= -1;// _41

		FbxDouble* mat = (FbxDouble*)m;
		for (int i = 0; i < 16; i++)
		{
			pMotion->pKey[bone_][f].m[i / 4][i % 4] = (float)mat[i];
		}

		time += 1.0 / 60.0;
	}
}

//�e�N�X�`�����擾
void Fbx::GetTextureInfo(MaterialData * pMaterialData_, FbxMesh * pMesh_) {

	InitMaterial(pMaterialData_, 1);
	FbxLayerElementMaterial* pElementMaterial = pMesh_->GetElementMaterial();
	if (pElementMaterial)
	{
		// �}�e���A�����
		int index = pElementMaterial->GetIndexArray().GetAt(0);
		FbxSurfaceMaterial* pMaterial = pMesh_->GetNode()->GetSrcObject<FbxSurfaceMaterial>(index);

		if (pMaterial)
		{
			//diffuse�̏����擾
			FbxProperty prop = pMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);

			//	�e�N�X�`���ǂݍ���
			const char* filename = NULL;

			//�e�N�X�`���̐����擾����
			int fileTextureCount = prop.GetSrcObjectCount<FbxFileTexture>();
			if (fileTextureCount > 0)
			{
				//�e�N�X�`�����擾����
				FbxFileTexture* FileTex = prop.GetSrcObject<FbxFileTexture>(0);
				filename = FileTex->GetFileName();
			}
			else
			{
				//���C���e�N�X�`���̐����擾����
				int numLayer = prop.GetSrcObjectCount<FbxLayeredTexture>();
				if (numLayer > 0)
				{
					//���C���e�N�X�`�����擾����
					FbxLayeredTexture* LayerTex = prop.GetSrcObject<FbxLayeredTexture>(0);
					//�e�N�X�`�����擾����
					FbxFileTexture* FileTex = LayerTex->GetSrcObject<FbxFileTexture>(0);
					filename = FileTex->GetFileName();
				}
			}
			if (filename == NULL) return;

			//	�e�N�X�`���[�̎擾
			char* pFileName;
			size_t size = 0;
			FbxUTF8ToAnsi(filename, pFileName, &size);

			// PSD���g�p����Ă���ꍇ�͓ǂ߂Ȃ��̂�TGA�Ŏ���
			char* ext = (char*)strstr(pFileName, ".psd");
			if (ext)
			{
				strcpy_s(ext, 5, ".tga");
			}

			char path[MAX_PATH];
			if (strstr(pFileName, "\\"))
			{
				strcpy_s(path, pFileName);
			}
			else
			{
				strcpy_s(path, m_RootPath);
				strcat_s(path, "/texture/");
				strcat_s(path, pFileName);
			}
			LoadTexture(path, &pMaterialData_->textureData);

			FbxFree(pFileName);
		}
	}
}
#pragma endregion

void Fbx::RenderFbxMesh(FBXMeshData * pData_)
{
	if (pData_ == nullptr) return;

	Skinning(pData_);

	DrawModel(&pData_->fbxinfo);
}

void Fbx::DrawModel(FbxInfo * pModel)
{
	if (pModel == NULL) return;
	if (pModel->materialcount == 0) return;

	IDirect3DDevice9 * pDevice = GetD3DDevice();
	pDevice->SetTransform(D3DTS_WORLD, &pModel->world);

	for (UINT matIdx = 0; matIdx < pModel->materialcount; matIdx++)
	{
		MaterialData* pMaterial = &pModel->pMaterial[matIdx];
		// �e�N�X�`���[�̐ݒ�
		pDevice->SetTexture(0, pMaterial->textureData.Texture);

		pDevice->SetMaterial(&pMaterial->material);
		for (UINT meshIdx = 0; meshIdx < pModel->materialcount; meshIdx++)
		{
			MeshData* pMesh = &pModel->pMesh[meshIdx];
			if (matIdx != pMesh->materialIndex)
			{
				continue;
			}

			// ���_�o�b�t�@�̐ݒ�
			pDevice->SetStreamSource(0, pMesh->pVB, 0, pMesh->vertexStride);

			// ���_�t�H�[�}�b�g�̎w��
			pDevice->SetFVF(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 | D3DFVF_DIFFUSE);

			if (pMesh->pIB)
			{
				// �C���f�b�N�X�o�b�t�@�̐ݒ�
				pDevice->SetIndices(pMesh->pIB);
				// �`��
				pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, pMesh->vertexCount, 0, pMesh->polygonCount);
			}
			else
			{
				// �`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, pMesh->polygonCount);
			}
		}
	}
}

void Fbx::Skinning(FBXMeshData * pData_)
{
	if (!pData_->fbxinfo.pMotion) return;

	Motion* pMotion = &(*pData_->fbxinfo.pMotion)[pData_->motion];
	if (pMotion == nullptr) return;
	if (pMotion->numFrame < 0) return;

	float Frame = pData_->frame;
	//	�z��p�ϐ�
	int f = (int)Frame;
	//	�s�񏀔�
	D3DXMATRIX KeyMatrix[256];
	for (UINT b = 0; b < pData_->fbxinfo.bonecount; b++)
	{
		if (!pMotion->pKey[b]) continue;
		//	�s����
		D3DXMATRIX m;
		MatrixInterporate(m, pMotion->pKey[b][f], pMotion->pKey[b][f + 1], Frame - (int)Frame);
		pData_->fbxinfo.bone[b].transform = m;
		//	�L�[�t���[��
		KeyMatrix[b] = pData_->fbxinfo.bone[b].offset * m;
	}

	//	���_�ό`
	for (UINT meshIdx = 0; meshIdx < pData_->fbxinfo.meshcount; meshIdx++)
	{
		MeshData* pMeshData = &pData_->fbxinfo.pMesh[meshIdx];
		VERTEX_3D* pSrcVertex = pMeshData->vertex;

		UINT size = (UINT)(pMeshData->vertexCount * sizeof(VERTEX_3D));
		VERTEX_3D* pVertex;
		// �o�b�t�@�����b�N���ăf�[�^����������
		pMeshData->pVB->Lock(0, size, (void**)& pVertex, 0);
		for (UINT v = 0; v < pMeshData->vertexCount; v++)
		{
			//	���_ * �{�[���s��
			// b = v�Ԗڂ̒��_�̉e���{�[��[n]
			if (pVertex[v].weight[0] <= 0) continue;

			pVertex[v].pos.x = 0;
			pVertex[v].pos.y = 0;
			pVertex[v].pos.z = 0;

			//	�e���������[�v
			for (int n = 0; n < 4; n++)
			{
				if (pVertex[v].weight[n] <= 0) break;

				int b = (int)pVertex[v].index[n];

				float x = pSrcVertex[v].pos.x;
				float y = pSrcVertex[v].pos.y;
				float z = pSrcVertex[v].pos.z;
				//	���W���e���͕��ړ�
				pVertex[v].pos.x += (x * KeyMatrix[b]._11 + y * KeyMatrix[b]._21 + z * KeyMatrix[b]._31 + 1 * KeyMatrix[b]._41) * pVertex[v].weight[n];
				pVertex[v].pos.y += (x * KeyMatrix[b]._12 + y * KeyMatrix[b]._22 + z * KeyMatrix[b]._32 + 1 * KeyMatrix[b]._42) * pVertex[v].weight[n];
				pVertex[v].pos.z += (x * KeyMatrix[b]._13 + y * KeyMatrix[b]._23 + z * KeyMatrix[b]._33 + 1 * KeyMatrix[b]._43) * pVertex[v].weight[n];

				float nx = pSrcVertex[v].nor.x;
				float ny = pSrcVertex[v].nor.y;
				float nz = pSrcVertex[v].nor.z;
				//	�@�����e���͕��ϊ�
				pVertex[v].nor.x += (nx * KeyMatrix[b]._11 + ny * KeyMatrix[b]._21 + nz * KeyMatrix[b]._31) * pVertex[v].weight[n];
				pVertex[v].nor.y += (nx * KeyMatrix[b]._12 + ny * KeyMatrix[b]._22 + nz * KeyMatrix[b]._32) * pVertex[v].weight[n];
				pVertex[v].nor.z += (nx * KeyMatrix[b]._13 + ny * KeyMatrix[b]._23 + nz * KeyMatrix[b]._33) * pVertex[v].weight[n];
			}
		}
		pMeshData->pVB->Unlock();
	}
}

void Fbx::MatrixInterporate(D3DXMATRIX & out_, D3DXMATRIX & A_, D3DXMATRIX B_, float rate_)
{
	out_ = A_ * (1.0f - rate_) + B_ * rate_;
}

void Fbx::ReleaseModel(FbxInfo * pModel)
{
	if (pModel == nullptr) return;

	for (UINT i = 0; i < pModel->meshcount; i++)
	{
		SAFE_RELEASE(pModel->pMesh[i].pVB);
		SAFE_RELEASE(pModel->pMesh[i].pIB);
		free(pModel->pMesh[i].vertex);
	}
	for (UINT i = 0; i < pModel->materialcount; i++)
	{
		ReleaseTexture(&pModel->pMaterial[i].textureData);
	}
	if (pModel->pMotion)
	{
		std::map<std::string, Motion>::iterator it;
		for (it = pModel->pMotion->begin(); it != pModel->pMotion->end(); it++)
		{
			for (int i = 0; i < 256; i++)
			{
				if (it->second.pKey[i])
				{
					free(it->second.pKey[i]);
				}
			}
		}
		delete pModel->pMotion;
	}
	free(pModel->pMesh);
	free(pModel->pMaterial);

	ZeroMemory(pModel, sizeof(FbxInfo));
}

void Fbx::Animate(FBXMeshData * pData_, float sec_)
{
	if (pData_ == nullptr) return;
	if (pData_->fbxinfo.pMotion == nullptr) return;
	//	���[�V�������Ԃ̍X�V
	pData_->frame += sec_ * 120.0f;

	//	���[�v�`�F�b�N
	if (pData_->frame >= (*pData_->fbxinfo.pMotion)[pData_->motion].numFrame - 1)
	{
		// ���[�v
		pData_->frame = 0;
	}
}

void Fbx::ResetAnimate(FBXMeshData * pData_)
{
	if (pData_ == nullptr) return;
	pData_->frame = 0;
}