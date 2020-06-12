#ifndef GAME_H_
#define GAME_H_

#include <d3dx9.h>
#include "UIBase.h"
#include "../Engine/Graphics.h"
#include"../Manager/ObjectManager.h"
#include"../Manager/ProductionManager.h"
#include"../Manager/SceneManager.h"

//前方宣言
class StartProduction;

class GameUI:public UIBase
{
public:
	GameUI() {}
	~GameUI() {}

public:
	enum GameUINum
	{
		NowPosBg,
		NowPosBg2,
		NowPosBg3,
		Player,
		TimerBg,
		One_S_Timer,
		Ten_S_Timer,
		One_M_Timer,
		Ten_M_Timer,
		Timer,
		BlockCont,
		One_Block,
		Ten_Block,
		GameUIMaxNum,
	};
private:
	struct GameUIInfo
	{
		int timercounter;
		int timercounter2;

		int time;

		float m_ones_tu;
		float m_ones_tv;

		float m_tens_tu;
		float m_tens_tv;

		float m_onem_tu;
		float m_onem_tv;

		float m_tenm_tu;
		float m_tenm_tv;


		char m_timefont[20];      //文字

		float m_oneblock_tu;
		float m_oneblock_tv;

		float m_tenblock_tu;
		float m_tenblock_tv;

		char m_stockfont[50];
		int timecounter;		//1秒数える
		int m_ones;	//1の単位
		int m_tens;	//10の単位
		int m_onem;	//1分の単位
		int m_tenm;	//10分の単位


		TEXTURE_DATA	 m_Ui[(int)GameUINum::GameUIMaxNum];
		D3DXVECTOR2		 m_Ui_pos[(int)GameUINum::GameUIMaxNum];
		

	}m_gameuiinfo;;

public:
	virtual void LoadTex()override;
	virtual void Init()override;
	virtual void Draw()override;
	virtual void UpDate()override;
	virtual void ReleaseTex()override;

	GameUIInfo* GetUIInfo() { return &m_gameuiinfo; }

private:
	void UpDateTimer();
	void UpDateTimer2();
	void UpDatePlayerPos();
	void ConversionBlockStock();

private:
	ObjectManager* m_objectmanager = ObjectManager::Instance();
	ProductionManager* m_productionmanager = ProductionManager::Instance();
	SceneManager* m_scene_manager = SceneManager::Instance();

};

#endif