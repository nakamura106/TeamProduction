#ifndef UIBASE_H_
#define UIBASE_H_

#include<string>
#include "../Engine/Graphics.h"
class UIBase
{
public:
	UIBase() {}
	~UIBase() {}

	virtual void Init() = 0;
	virtual void LoadTex() = 0;
	virtual void LoadFile() = 0;
	virtual void Draw() = 0;
	virtual void UpDate() = 0;
	virtual void ReleaseTex() = 0;

protected:
	virtual void ReleaseUITexture(TEXTURE_DATA* texture);
	std::string m_key;
};

#endif