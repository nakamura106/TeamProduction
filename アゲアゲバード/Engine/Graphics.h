#ifndef GRAHPICS
#define GRAHPICS

#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <vector>
#include <fbxsdk.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

#include <Windows.h>

// ���
#define	SAFE_DESTROY(x)	{ if(x) { (x)->Destroy(); (x) = NULL; } }

// ��������p�̃}�N�����`
#define SAFE_RELEASE(x) { if(x) { (x)->Release(); (x) = NULL; } }

struct TEXTURE_DATA
{
	LPDIRECT3DTEXTURE9 Texture;
	float Width;
	float Height;
};




struct Size
{
	Size()
	{
		Width = 0.0f;
		Height = 0.0f;
	}

	Size(float width, float height)
	{
		Width = width;
		Height = height;
	}

	Size(const Size& size)
	{
		this->Width = size.Width;
		this->Height = size.Height;
	}

	float Width;
	float Height;
};


struct CUSTOM_VERTEX
{
	float x;
	float y;
	float z;
	float rhw;
	float tu;
	float tv;
};

enum ERenderMode
{
	Normal,		// ��������
	Add,		// ���Z
	Subtract,	// ���Z
	Multiple,	// ��Z
};

void SetRenderMode(ERenderMode mode_, bool enableAlpa_);

bool InitGraphics();

void ReleaseGraphics();

bool CreateGraphicsInterface();

bool CreateGraphicsDevice(D3DPRESENT_PARAMETERS* present_param);

bool SetUpViewPort(D3DPRESENT_PARAMETERS* present_param);

void DrawStart();

void DrawEnd();

void DrawUITexture(TEXTURE_DATA* texture, D3DXVECTOR2 pos);

void DrawUVTexture(TEXTURE_DATA* texture, D3DXVECTOR2 pos, float sprite_width, float sprite_height, float tu, float tv);

//bool LoadTexture(const char*, TEXTURE_DATA*);

bool LoadTexture(const char* file_name, TEXTURE_DATA* texture);

void DrawUITexture(TEXTURE_DATA* texture, D3DXVECTOR2 pos);

void ReleaseTexture(TEXTURE_DATA*);

const LPDIRECT3DDEVICE9 GetD3DDevice(void);

void SetLight();


#endif
