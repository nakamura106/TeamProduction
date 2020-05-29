#ifndef UIMANAGER_H_
#define UIMANAGER_H_

#include"../Object/ObjectBase.h"
#include<vector>
#include "../UI/UIBase.h"

class UIManager
{
public:
	static UIManager* Instance();

	void Init(int scene_);
	void CreateUI();
	void LoadTex(int scene_);
	void LoadFile(int scene_);
	void Draw(int scene_);
	void UpDate(int scene_);
	void Release(int scene_);

	std::vector<UIBase*>* GetUI() { return &m_UI; }

	enum class Scene :int
	{
		title,
		game,
		end,
		help,
		option,
	};

protected:
	UIManager();
	~UIManager();

	

private:
	static UIManager* p_instance;
	std::vector<UIBase*> m_UI;
};

#endif