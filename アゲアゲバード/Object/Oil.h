#ifndef OIL_H_
#define OIL_H_

#include"ObjectBase.h"

class Oil :public ObjectBase
{
public:
	Oil();
	~Oil() {};

	void Update()override;
	void Draw()override;

	const ObjectData* GetOilData()const { return &m_oildata; }
private:
	ObjectData m_oildata;
};

class FillOil :public ObjectBase
{
public:
	FillOil();
	~FillOil() {};

	void Update()override;
	void Draw()override;

	const ObjectData* GetFillOilData()const { return &m_filloildata; }

private:
	ObjectData m_filloildata;
};


#endif
