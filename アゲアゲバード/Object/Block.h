#ifndef BLOCK_H_
#define BLOCK_H_

#include"../Object/ObjectBase.h"


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
	
};

#endif