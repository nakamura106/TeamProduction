#ifndef END_H_
#define END_H_
#include "ProductionBase.h"
#include "../Engine/Graphics.h"
#include "../Utility/Gravity.h"

class EndProduction :public ProductionBase
{
private:
	struct EndProductionInfo {
		Gravity m_grav;

		D3DXVECTOR2 m_finish_pos;
		D3DXVECTOR2 m_fly_pos;
		D3DXVECTOR2 m_oil_filter_pos;

		TEXTURE_DATA m_finish;
		TEXTURE_DATA m_fly;
		TEXTURE_DATA m_oil_filter;

		bool finishflag;
		bool clear_seflag;

		bool flyflag;
		bool fly_seflag;

		float m;   //質量
		float fa;  //摩擦係数
		float f;   //摩擦力
		float e;  //自然対数(ネイピアの数)

		float speed;

		int timer;
	}m_EndProductionInfo;


public:
	EndProduction() {}
	~EndProduction() {}

	virtual void Init();
	virtual void LoadTex();
	virtual void Draw();
	virtual void UpDate();
	virtual void ReleaseTex();

	void ReleaseUITexture(TEXTURE_DATA* texture);

	const EndProductionInfo* GetEndProductionInfo()const { return &m_EndProductionInfo; }


};

#endif