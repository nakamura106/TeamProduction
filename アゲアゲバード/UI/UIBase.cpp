#include "UIBase.h"
//#include "UIBase.h"
//
//void UIBase::LoadTex()
//{
//	LoadTexture((char*)filename, &m_texturedata);
//}
//
//void UIBase::Draw()
//{
//	DrawUITexture(&m_texturedata, m_pos);
//}

void UIBase::ReleaseUITexture(TEXTURE_DATA* texture)
{
	if (texture->Texture != nullptr)
	{
		texture->Texture->Release();
		texture->Texture = nullptr;
	}
}
