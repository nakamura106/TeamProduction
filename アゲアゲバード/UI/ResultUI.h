#ifndef RESULTUI_H_
#define RESULTUI_H_
#include <d3dx9.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "UIBase.h"
#include "../Engine/Graphics.h"
#include"../Manager/ObjectManager.h"
#include"../Manager/ProductionManager.h"
#include"../Manager/SceneManager.h"

#include "../CSV/CSV.h"

class ResultUI:public UIBase
{
public:
	ResultUI(){}
	~ResultUI(){}

	virtual void LoadTex(){}
	virtual void Init();
	virtual void Draw();
	virtual void UpDate(){}
	virtual void ReleaseTex();

private:
	CSV* m_csv;

	SceneManager* m_scene_manager = SceneManager::Instance();

	char m_timefont[20];
	char m_no1[20];
	char m_no2[20];
	char m_no3[20];

	std::vector<std::string> m_score_table;

	struct  Ranking
	{
		char first[6];
		char second[6];
		char third[6];
	};
	Ranking m_ranking;

};

#endif