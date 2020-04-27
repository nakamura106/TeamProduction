#ifndef PRODUCTION_H_
#define PRODUCTION_H_

class ProductionBase
{
public:
	ProductionBase(){}
	~ProductionBase(){}

	virtual void Init() = 0;
	virtual void LoadTex() = 0;
	virtual void Draw() = 0;
	virtual void UpDate() = 0;
	virtual void ReleaseTex() = 0;


};

#endif