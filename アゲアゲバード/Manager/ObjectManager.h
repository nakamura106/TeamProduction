#ifndef OBJECTMANAGER_H_
#define OBJECTMANAGER_H_

#include"../Object/ObjectBase.h"
#include"../Utility/Collision.h"
#include<vector>

class ObjectManager
{
public:
	static ObjectManager* Instance();

	//�}�l�[�W���[�̏��������R���X�g���N�^���̂�
	void Init() {};
	//�I�u�W�F�N�g����
	void CreateObject();//�}�b�v�A�v���C���[(2�܂�)�A�A�C�e���B�u���b�N�͕ʔz��
	bool CreateBlock();
	void CreateItem();
	void CreateItemBox();
	void CreatePlayer();	// K�V�����ǉ�����
	void Update();
	void Draw();
	void AllDeleteObject();
	


	//ObjectBase* GetPlayerObject() {};

	//ObjectBase* GetCharaObject() {};

protected:
	ObjectManager();
	~ObjectManager();

private:
	static ObjectManager* p_instance;
	Collision* m_collision;
	std::vector<ObjectBase*> m_Object;
	std::vector<ObjectBase*> m_Block;
	std::vector<ObjectBase*> m_Item;
	std::vector<ObjectBase*> m_ItemBox;
	std::vector<ObjectBase*> m_player;

};

#endif