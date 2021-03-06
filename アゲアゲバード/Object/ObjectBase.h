#ifndef OBJBASE_H_
#define OBJBASE_H_

//#include "../Object/ObjectBase.h"
#include"../Engine/FBX.h"
#include"../Manager/FbxManager.h"

class ObjectBase
{
protected:
	struct ObjectData {

		FBXMeshData m_object;

		D3DXVECTOR3 m_pos;
		D3DXMATRIX m_mat_world;		// ワールド
		D3DXMATRIX m_mat_scale;		// 拡縮		誤字 scall→scale？
		D3DXMATRIX m_mat_move;		// 移動
		D3DXMATRIX m_mat_rot;		// 回転
		D3DXMATRIX m_mat_rot_x;		// 回転x軸
		D3DXMATRIX m_mat_rot_y;		// 回転y軸
		D3DXMATRIX m_mat_rot_z;		// 回転z軸

		float radius;					// 半径(プレイヤーの当たり判定をとるための)

		D3DXVECTOR3 angle_;
		D3DXVECTOR3 scale_;

		std::string m_key;
	};


	MyFbxManager::FbxManager* m_fbxmanager = MyFbxManager::FbxManager::Instance();

public:
	ObjectBase();
	virtual ~ObjectBase();

	virtual void Update()=0;
	virtual void Draw()=0;
	
	
private:

};

#endif
