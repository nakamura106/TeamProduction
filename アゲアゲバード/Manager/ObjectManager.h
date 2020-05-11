#ifndef OBJECTMANAGER_H_
#define OBJECTMANAGER_H_

#include"../Object/ObjectBase.h"
#include"../Utility/Collision.h"
#include"../DataBank/Definition.h"
#include"../Player/Player.h"
#include<vector>
#include<map>

//�O���錾
class Block;
class Item;
class GetItemBox;
class Player;
class Pot;

class ObjectManager
{
public:
	static ObjectManager* Instance();

	//�}�l�[�W���[�̏��������R���X�g���N�^���̂�
	void Init() {};

	//�I�u�W�F�N�g����
	void CreateObject();//�}�b�v�A�v���C���[(2�܂�)�B�A�C�e���A�u���b�N�͕ʔz��
	bool CreateBlock();
	void CreateItem();
	void CreatePlayer();	// K�V�����ǉ�����

	void Update();
	void Draw();
	void AllDeleteObject();
	
	D3DXVECTOR3 BlockInstallation(D3DXVECTOR3 eyepos_, D3DXVECTOR3 forward_);
	
	Pot* GetMap() { return m_pot; }
	std::vector<Item*>* GetItem() { return &m_Item; }
	std::vector<Block*>* GetBlock() { return &m_Block; }
	Character::Player* GetPlayer(std::string key_) { return m_player[key_]; }
	ObjectBase* GetOil(std::string key_) { return m_Object[key_]; }
	CAMERA* GetCamera() { return m_camera; }
	
protected:
	ObjectManager();
	~ObjectManager();

private:
	static ObjectManager* p_instance;

	void CreateItemBox();

	Collision* m_collision;
	CAMERA* m_camera;
	Pot* m_pot;
	std::map<std::string,ObjectBase*> m_Object;
	std::map<std::string,Character::Player*> m_player;
	std::vector<Block*> m_Block;
	std::vector<Item*> m_Item;
	std::vector<GetItemBox*> m_ItemBox;
};

#endif