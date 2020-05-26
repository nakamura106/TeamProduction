#ifndef BLOCK_H_
#define BLOCK_H_

#include"../Manager/ObjectManager.h"

//‘O•ûéŒ¾
class ObjectBase;


class Block :public ObjectBase
{
public:
	Block();
	~Block();

	void Update()override;
	void Draw()override;

	ObjectData* GetBlockData() { return &m_BlockData;}

private:
	ObjectData m_BlockData;
	ObjectManager* m_objectmanager= ObjectManager::Instance();
	CAMERA* m_camera = m_objectmanager->GetPlayer("player1")->GetPlayerData()->m_p_camera;
};

#endif