#ifndef START_H_
#define START_H_
#include "ProductionBase.h"
#include "../Engine/Graphics.h"

class StartProduction:public ProductionBase
{
private:
	struct StartProductionInfo {
		D3DXVECTOR2 m_t_one_pos;
		D3DXVECTOR2 m_t_two_pos;
		D3DXVECTOR2 m_t_three_pos;

		D3DXVECTOR2 m_start_pos;


		TEXTURE_DATA m_t_one;
		TEXTURE_DATA m_t_two;
		TEXTURE_DATA m_t_three;

		TEXTURE_DATA m_start;

		int m_counttimer;

		bool m_one_draw;
		bool m_two_draw;
		bool m_three_draw;

		bool m_uistartflag;
	}m_ProductionInfo;

public:
	StartProduction(){}
	~StartProduction(){}

	virtual void Init();
	virtual void LoadTex();
	virtual void Draw();
	virtual void UpDate();
	virtual void ReleaseTex();

	const StartProductionInfo* GetStartProductionInfo()const { return &m_ProductionInfo; }

	void ReleaseUITexture(TEXTURE_DATA* texture);



	
};

#endif