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
		char m_stockfont[50];
		int timecounter;		//1秒数える
		int m_ones;	//1の単位
		int m_tens;	//10の単位
		int m_onem;	//1分の単位
		int m_tenm;	//10分の単位


		D3DXVECTOR2 tex_pos;
		D3DXVECTOR2 player_pos;

		D3DXVECTOR2 timerbg_pos;
		D3DXVECTOR2 one_s_timer_pos;
		D3DXVECTOR2 ten_s_timer_pos;

		D3DXVECTOR2 one_m_timer_pos;
		D3DXVECTOR2 ten_m_timer_pos;

		D3DXVECTOR2 timer_pos;


		TEXTURE_DATA m_position;
		TEXTURE_DATA m_player_pos;
		TEXTURE_DATA m_timer;
		TEXTURE_DATA m_timerbg;

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