#include "EndProduction.h"
#include "../DataBank/DataBank.h"
#include "../Manager/SoundManager.h"

void EndProduction::Init()
{
	m_finish_pos.x = 400.0f;
	m_finish_pos.y = -100.0f;

	m_fly_pos.x = 600.0f;
	m_fly_pos.y = 500.0f;


	speed = 5.0f;

	timer = 0;
	m = 30.0f;
	fa = 0.3f;
	e = 2.71828182845904523536f;

	finishflag = false;
	flyflag = false;
	clear_seflag = false;
	fly_seflag = false;
}

void EndProduction::LoadTex()
{
	LoadTexture("Res/Tex/UI フィニッシュ.png", &m_finish);
	LoadTexture("Res/Tex/UI フライ.png", &m_fly);
}

void EndProduction::Draw()
{
	if (DataBank::Instance()->GetAfterPlayerPos().y >= DataBank::Instance()->GetMapTop().y && DataBank::Instance()->GetStartflag() == true)
	{
		DrawUITexture(&m_finish, m_finish_pos);
	}
	else if(DataBank::Instance()->GetAfterPlayerPos().y <= DataBank::Instance()->GetOilPos() && DataBank::Instance()->GetStartflag() == true)
	{
		DrawUITexture(&m_fly, m_fly_pos);
	}
}

void EndProduction::UpDate()
{
	if (DataBank::Instance()->GetAfterPlayerPos().y <= DataBank::Instance()->GetOilPos())
	{
		fly_seflag = true;

		if (m_fly_pos.y >= -300.0f)
		{
			m_grav.ThrowingUp(m_fly_pos.y, 8.0f);
			m_fly_pos.y = m_grav.GetPosY();
		}
		else
		{
			flyflag = true;
		}
	}
	if (DataBank::Instance()->GetAfterPlayerPos().y >= DataBank::Instance()->GetMapTop().y && DataBank::Instance()->GetStartflag() == true)
	{	

		clear_seflag = true;

		if (m_finish_pos.y <= 400.0f)
		{
			timer++;

			if (timer == 30)
			{
				speed *= powf(e, -(fa / m) * timer);
				timer = 0;
			}

			m_finish_pos.y += speed;
		}
		else
		{
			finishflag = true;
		}
		
	}

	if (clear_seflag == true)
	{
		SoundManager::Instance()->SoundClearSE();
	}
	else if (fly_seflag == true)
	{
		SoundManager::Instance()->SoundFlySE();
	}

	DataBank::Instance()->SetFinishflag(finishflag);
	DataBank::Instance()->SetFlyflag(flyflag);

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
