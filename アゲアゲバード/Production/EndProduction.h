#ifndef END_H_
#define END_H_
#include "ProductionBase.h"
#include "../Engine/Graphics.h"

class EndProduction :public ProductionBase
{
public:
	EndProduction() {}
	~EndProduction() {}

	virtual void Init();
	virtual void LoadTex();
	virtual void Draw();
	virtual void UpDate();
	virtual void ReleaseTex();

	void ReleaseUITexture(TEXTURE_DATA* texture);


private:
	D3DXVECTOR2 m_finish_pos;
	D3DXVECTOR2 m_fly_pos;


	TEXTURE_DATA m_finish;
	TEXTURE_DATA m_fly;

};

#endif