#include "EndProduction.h"
#include "../DataBank/DataBank.h"

void EndProduction::Init()
{
	m_finish_pos.x = 0.0f;
	m_finish_pos.y = 0.0f;

	m_fly_pos.x = 0.0f;
	m_fly_pos.y = 0.0f;

}

void EndProduction::LoadTex()
{
	LoadTexture("Res/Tex/UI フィニッシュ.png", &m_finish);
	LoadTexture("Res/Tex/UI フライ.png", &m_fly);
}

void EndProduction::Draw()
{
	if (DataBank::Instance()->GetClearflag() == true)
	{
		DrawUITexture(&m_finish, m_finish_pos);
	}
	else if(DataBank::Instance()->GetAfterPlayerPos().y <= DataBank::Instance()->GetOilPos())
	{
		DrawUITexture(&m_fly, m_fly_pos);
	}
}

void EndProduction::UpDate()
{

}

void EndProduction::ReleaseTex()
{
	ReleaseUITexture(&m_finish);
	ReleaseUITexture(&m_fly);

}

void EndProduction::ReleaseUITexture(TEXTURE_DATA* texture)
{
	if (texture->Texture != NULL)
	{
		texture->Texture->Release();
		texture->Texture = NULL;
	}
}
