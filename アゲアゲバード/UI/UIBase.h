#ifndef UIBASE_H_
#define UIBASE_H_
#include <d3dx9.h>
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
	
};

#endif