#ifndef UIBASE_H_
#define UIBASE_H_
#include <d3dx9.h>
#include "../Engine/Graphics.h"
#include "../CSV/CSV.h"

class UIBase
{
public:
	UIBase() {}
	~UIBase() {}

public:
	virtual void LoadFile() = 0;		// ���g���ĂȂ�

	virtual void LoadTex() = 0;
	virtual void Init() = 0;
	virtual void Draw() = 0;
	virtual void UpDate() = 0;
	virtual void ReleaseTex() = 0;

protected:
	
};

#endif