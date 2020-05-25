#ifndef WORLDBOX_H_
#define WORLDBOX_H_

#include"../Object/ObjectBase.h"


class WorldBox :public ObjectBase
{
public:
	WorldBox();
	~WorldBox();

	void Update()override;
	void Draw()override;

	ObjectData* GetWorldBoxData() { return &m_world_box_data; }


private:
	ObjectData m_world_box_data;

};

#endif // !WORLDBOX_H_


