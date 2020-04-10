#ifndef DATABANK_H_
#define DATABANK_H_

#include <d3dx9.h>
#include<vector>
#include"../Object/ObjectBase.h"
#include"../Scene/BaseScene.h"

//情報保存クラス
class DataBank
{
public:
	static DataBank* Instance();

	void ResetData() {}

	void SetCameraPos(D3DXVECTOR3 camerapos_);

	void SetEyePos(D3DXVECTOR3 eyepos_);

	void SetOilPos(float oilelevation_);

	void SetBlockPos(D3DXVECTOR3 blockpos_);


	
	D3DXVECTOR3 GetCameraPos() { return m_Camera_Pos; }

	D3DXVECTOR3 GetEyePos() { return m_Eye_Pos; }

	auto GetBlockPos() { return m_blockpos; }

	float GetOilPos() { return m_oilelevation; }


	
protected:
	DataBank();
	~DataBank();

private:
	static DataBank* p_instance;

	float m_oilelevation;

	D3DXVECTOR3 m_Camera_Pos;
	
	D3DXVECTOR3 m_player_pos;

	D3DXVECTOR3 m_Eye_Pos;

	std::vector<D3DXVECTOR3> m_blockpos;

	BaseScene::SceneStep m_scene_step;

	BaseScene::SceneId m_scene_id;

};

#endif // !DATABANK_H_
