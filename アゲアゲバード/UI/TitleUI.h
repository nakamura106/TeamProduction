#ifndef TITLE_UI_H_
#define TITLE_UI_H_

#include"UIBase.h"
#include<vector>

class TitleUi :public UIBase
{
public:
	TitleUi();
	~TitleUi();

	virtual void Init()override;
	virtual void LoadTex()override;
	virtual void LoadFile()override;
	virtual void Draw()override;
	virtual void UpDate()override;
	virtual void ReleaseTex()override;


	enum class Select :int
	{
		Solo,
		Help,
		Option,
		Freemode,
		Timeattack,
		Back,
		Title,
		SelectMax,
	}m_title_select;

	enum class page :int
	{
		page1,
		page2,
	};

private:

	void DrawTitleUi(int page_);

	void UpdateSelect();


	TEXTURE_DATA	 m_Ui[(int)Select::SelectMax];
	TEXTURE_DATA	 m_select;
	D3DXVECTOR2		 m_Ui_pos[(int)Select::SelectMax];
	D3DXVECTOR2		 m_select_pos;
};



#endif