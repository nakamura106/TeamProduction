#ifndef UIMANAGER_H_
#define UIMANAGER_H_

#include"../Object/ObjectBase.h"
#include<vector>
#include "../UI/UIBase.h"

class UIManager
{
public:
	static UIManager* Instance();

	void Init();
	void CreateUI();
	void LoadTex();
	void LoadFile();
	void Draw();
	void UpDate();
	void Release();

protected:
	UIManager();
	~UIManager();

private:
	static UIManager* p_instance;
	std::vector<UIBase*> m_UI;
};

#endif