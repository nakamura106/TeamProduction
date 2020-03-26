#ifndef FBXMANAGER_H_
#define FBXMANAGER_H_
#include "../Engine/FBX.h"
#include<map>
#include<string>

namespace MyFbxManager
{



	class FbxManager
	{
	public:
		static FbxManager* Instance();

	

		FBXMeshData LoadFbxMesh(std::string key_,const char* pFilename);

		void ReleaseFbxMesh(std::string key_);

		void AllReleaseMesh(FBXMeshData* meshdata_);

		void DrawFbx(std::string key_,D3DXMATRIX& mat_world_);

		void Animation(std::string key_,float sec_);

		void ResetAnimation(FBXMeshData* meshdata_);

		FBXMeshData GetMeshData(std::string key_) { return m_MeshData[key_]; }
		
	protected:
		FbxManager();

		~FbxManager();

	private:

		static FbxManager* p_instance;

		Fbx* m_Fbx;

		std::map<std::string, FBXMeshData> m_MeshData;

		bool HasKey(std::string key_);

	};
}
#endif
