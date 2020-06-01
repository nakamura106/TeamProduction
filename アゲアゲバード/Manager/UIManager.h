#ifndef UIMANAGER_H_
#define UIMANAGER_H_

#include"../Object/ObjectBase.h"
#include<vector>
#include "../UI/UIBase.h"
#include "../UI/TitleUI.h"
#include "../UI/GameUI.h"
#include "../UI/ResultUI.h"



class UIManager
{
public:
	static UIManager* Instance();

	enum class Scene :int
	{
		title,
		game,
		end,
		help,
		option,
	};

	void Init(Scene scene_);
	void CreateUI();
	void LoadTex(Scene scene_);
	void Draw(Scene scene_);
	void UpDate(Scene scene_);
	void Release(Scene scene_);

	std::vector<UIBase*>* GetUI() { return &m_UI; }

	TitleUI* GetTitleUI() {return m_titleui;}
	GameUI* GetGameUI() { return m_gameui; }
	ResultUI* GetResultUI() { return m_resultui; }


protected:
	UIManager();
	~UIManager();

private:
	static UIManager* p_instance;
	std::vector<UIBase*> m_UI;
	TitleUI* m_titleui;
	GameUI* m_gameui;
	ResultUI* m_resultui;

};

#endif