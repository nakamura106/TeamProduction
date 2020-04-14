#ifndef DATABANK_H_
#define DATABANK_H_

#include <d3dx9.h>
#include<vector>
#include"../Object/ObjectBase.h"
#include"../Scene/BaseScene.h"

//���ۑ��N���X
class DataBank
{
public:
	static DataBank* Instance();

	void ResetData() {}

	// �J�����̒����_��ۑ�����
	void SetEyePos(D3DXVECTOR3 eyepos_);
	// �J�����̈ʒu��ۑ�����
	void SetCameraPos(D3DXVECTOR3 camerapos_);
	// �ړ��O�̃J�����̈ʒu��ۑ�����
	void SetBeforeCameraPos(D3DXVECTOR3 camera_pos_);
	// �ړ���̃J�����̈ʒu��ۑ�����
	void SetAfterCameraPos(D3DXVECTOR3 camera_pos_);

	void SetMapCenterPos(D3DXVECTOR3 map_centerpos_);

	void SetMapRadius(float map_radius_);

	void SetMapTop(float map_top_);

	void SetOilPos(float oilelevation_);

	void SetBlockPos(D3DXVECTOR3 blockpos_);

	// �v���C���[�̈ʒu��ۑ�����
	void SetPlayerPos(D3DXVECTOR3 player_pos_);
	// �v���C���[�̔��a��ۑ�����
	void SetPlayerRadius(float player_radius_);

	void SetSceneStep(BaseScene::SceneStep scenestep_);

	void SetSceneId(BaseScene::SceneId sceneid_);

	void SetForward(D3DXVECTOR3 forward_);

	// �J�����̈ʒu���擾����
	D3DXVECTOR3 GetCameraPos() {
		return m_Camera_Pos;
	}
	// �ړ��O�̃J�����̈ʒu���擾����
	D3DXVECTOR3 GetBeforeCameraPos() {
		return m_before_camera_pos;
	}
	// �ړ���̃J�����̈ʒu���擾����
	D3DXVECTOR3 GetAfterCameraPos() {
		return m_after_camera_pos;
	}

	D3DXVECTOR3 GetEyePos() { return m_eye_pos; }

	auto GetBlockPos() { return m_blockpos; }

	float GetOilPos() { return m_oilelevation; }

	// �v���C���[�̈ʒu���擾����
	D3DXVECTOR3 GetPlayerPos(D3DXVECTOR3 player_pos_) {
		return m_player_pos;
	}
	// �v���C���[�̔��a���擾����
	float GetPlayerRadius(float player_radius_) {
		return m_player_radius;
	}

	float GetMapRadius() { return m_map_radius; }

	float GetMapTop() { return m_map_top; }

	D3DXVECTOR3 GetMapCenterPos() { return m_map_centerpos; }

	D3DXVECTOR3 GetForward() { return m_Forward; }

	BaseScene::SceneStep GetSceneStep() { return m_scene_step; }

	BaseScene::SceneId GetSceneId() { return m_scene_id; }
	


protected:
	DataBank();
	~DataBank();

private:
	static DataBank* p_instance;

	float m_oilelevation;

	D3DXVECTOR3 m_Camera_Pos;
	D3DXVECTOR3 m_before_camera_pos;
	D3DXVECTOR3 m_after_camera_pos;
	
	D3DXVECTOR3 m_player_pos;
	float m_player_radius;

	D3DXVECTOR3 m_eye_pos;

	D3DXVECTOR3 m_map_centerpos;

	D3DXVECTOR3 m_Forward;

	float m_map_radius;

	float m_map_top;

	std::vector<D3DXVECTOR3> m_blockpos;

	BaseScene::SceneStep m_scene_step;

	BaseScene::SceneId m_scene_id;

};

#endif // !DATABANK_H_
