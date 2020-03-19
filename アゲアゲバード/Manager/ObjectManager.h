#ifndef OBJECTMANAGER_H_
#define OBJECTMANAGER_H_

#include"../Object/ObjectBase.h"
#include<vector>

class ObjectManager
{
public:
	static ObjectManager* Instance();

	//�}�l�[�W���[�̏��������R���X�g���N�^���̂�
	void Init();
	//�I�u�W�F�N�g����
	void CreateObject();//�}�b�v�A�v���C���[(2�܂�)�A�A�C�e���B�u���b�N�͕ʔz��
	void Update();
	void Draw();
	void AllDeleteObject();

	ObjectBase* GetPlayerObject();

	ObjectBase* GetCharaObject();

protected:
	ObjectManager();
	~ObjectManager();

private:
	static ObjectManager* p_instance;
	std::vector<ObjectBase*> Object;

};

#endif