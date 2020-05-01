#ifndef END_H_
#define END_H_
#include "ProductionBase.h"
#include "../Engine/Graphics.h"
#include "../Utility/Gravity.h"

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

	Gravity m_grav;

	D3DXVECTOR2 m_finish_pos;
	D3DXVECTOR2 m_fly_pos;

	TEXTURE_DATA m_finish;
	TEXTURE_DATA m_fly;

	bool clearflg;
	bool flyflg;

	float m;   //����
	float fa;  //���C�W��
	float f;   //���C��
	float e;  //���R�ΐ�(�l�C�s�A�̐�)

	float speed;

	int timer;
};

#endif