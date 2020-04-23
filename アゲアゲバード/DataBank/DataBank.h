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

	void DeleteBlockPos(int num);
	
#pragma region Set

	// �J�����̒����_��ۑ�����
	void SetEyePos(D3DXVECTOR3 eyepos_);
	// �J�����̈ʒu��ۑ�����
	void SetCameraPos(D3DXVECTOR3 camerapos_);

	void SetMapCenterPos(D3DXVECTOR3 map_centerpos_);

	void SetMapRadius(float map_radius_);

	// �}�b�v(�|�b�g)�̒���̒��S���W��ۑ�����
	void SetMapTop(D3DXVECTOR3 map_top_);
	// �}�b�v(�|�b�g)�̒�ӂ̒��S���W��ۑ�����
	void SetMapBottom(D3DXVECTOR3 map_bottom_);

	void SetOilPos(float oilelevation_);

	void SetBlockPos(D3DXVECTOR3 blockpos_);

	// �A�C�e���̈ʒu��ۑ�����
	void SetItemPos(D3DXVECTOR3 item_pos_);
	// �A�C�e���̔��a��ۑ�����
	void SetItemRadius(float item_radius_);

	// �ړ��O�̃v���C���[�̈ʒu��ۑ�����
	void SetBeforePlayerPos(D3DXVECTOR3 player_pos_);
	// �ړ���̃v���C���[�̈ʒu��ۑ�����
	void SetAfterPlayerPos(D3DXVECTOR3 player_pos_);
	// �v���C���[�̔��a��ۑ�����
	void SetPlayerRadius(float player_radius_);

	void SetSceneStep(BaseScene::SceneStep scenestep_);

	void SetSceneId(BaseScene::SceneId sceneid_);

	void SetForward(D3DXVECTOR3 forward_);

	D3DXVECTOR3 BlockInstallation(D3DXVECTOR3 pos_);

	void SetClearflag(bool clearflag_);

#pragma endregion

#pragma region Get

	// �J�����̒����_���擾����
	D3DXVECTOR3 GetEyePos() {
		return m_eye_pos; 
	}
	// �J�����̈ʒu���擾����
	D3DXVECTOR3 GetCameraPos() {
		return m_Camera_Pos;
	}

	// �}�b�v�̒��S�̍��W���擾����
	D3DXVECTOR3 GetMapCenterPos() {
		return m_map_centerpos;
	}
	// �}�b�v�̔��a
	float GetMapRadius() {
		return m_map_radius;
	}

	auto GetBlockPos() { return m_blockpos; }

	float GetOilPos() { return m_oilelevation; }

	// �A�C�e���̈ʒu���擾����
	D3DXVECTOR3 GetItemPos() {
		return m_item_pos;
	}
	// �A�C�e���̔��a���擾����
	float GetItemRadius() {
		return m_item_radius;
	}

	// �ړ��O�̃v���C���[�̈ʒu���擾����
	D3DXVECTOR3 GetBeforePlayerPos() {
		return m_before_player_pos;
	}
	// �ړ���̃v���C���[�̈ʒu���擾����
	D3DXVECTOR3 GetAfterPlayerPos() {
		return m_after_player_pos;
	}
	// �v���C���[�̔��a���擾����
	float GetPlayerRadius(float player_radius_) {
		return m_player_radius;
	}
	
	D3DXVECTOR3 GetMapTop() { return m_map_top; }
	D3DXVECTOR3 GetMapBottom() {
		return m_map_bottom;
	}

	D3DXVECTOR3 GetForward() { return m_Forward; }

	BaseScene::SceneStep GetSceneStep() { return m_scene_step; }

	BaseScene::SceneId GetSceneId() { return m_scene_id; }

	bool GetClearflag() { return m_clearflag; }

#pragma endregion

protected:
	DataBank();
	~DataBank();

private:
	static DataBank* p_instance;

	bool m_clearflag;

	float m_oilelevation;

	D3DXVECTOR3 m_eye_pos;
	D3DXVECTOR3 m_Camera_Pos;
	
	D3DXVECTOR3 m_map_centerpos;

	D3DXVECTOR3 m_Forward;

	float m_map_radius;

	D3DXVECTOR3 m_map_top;
	D3DXVECTOR3 m_map_bottom;

	D3DXVECTOR3 m_item_pos;
	float m_item_radius;

	D3DXVECTOR3 m_before_player_pos;
	D3DXVECTOR3 m_after_player_pos;
	float m_player_radius;

	std::vector<D3DXVECTOR3> m_blockpos;

	BaseScene::SceneStep m_scene_step;

	BaseScene::SceneId m_scene_id;

};

#endif // !DATABANK_H_
