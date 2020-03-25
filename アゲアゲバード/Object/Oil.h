#ifndef OIL_H_
#define OIL_H_

#include"ObjectBase.h"

class Oil :public ObjectBase
{
public:
	Oil();
	~Oil() {};

	void Update()override;

private:
	float m_oil_elevation;
};

class FillOil :public ObjectBase
{
public:
	FillOil();
	~FillOil() {};

	void Update();

};


#endif
