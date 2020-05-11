#include "UIBase.h"


void UIBase::ReleaseUITexture(TEXTURE_DATA* texture)
{
	if (texture->Texture != nullptr)
	{
		texture->Texture->Release();
		texture->Texture = nullptr;
	}
}
