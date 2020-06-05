#ifndef END_H_
#define END_H_

#include "ProductionBase.h"
#include "../Engine/Graphics.h"
#include "../Utility/Gravity.h"
#include "../Manager/ObjectManager.h"
#include "../Manager/SoundManager.h"

class EndProduction :public ProductionBase
{
private:
	struct EndProductionInfo {
		Gravity m_grav;

		D3DXVECTOR2 m_finish_pos;
		D3DXVECTOR2 m_fly_pos;
		D3DXVECTOR2 m_oil_filter_pos;

		TEXTURE_DATA m_finish;
		TEXTURE_DATA m_fly;
		TEXTURE_DATA m_oil_filter;

		bool finishflag;
		bool clear_seflag;

		bool flyflag;
		bool fly_seflag;

		float m;   //����
		float fa;  //���C�W��
		float f;   //���C��
		float e;  //���R�ΐ�(�l�C�s�A�̐�)

		float speed;

		int timer;
	}m_EndProductionInfo;

	ObjectManager* m_objectmanager = ObjectManager::Instance();
	SoundManager* m_soundmanager = SoundManager::Instance();

public:
	EndProduction() {}
	~EndProduction() {}

	virtual void Init();
	virtual void LoadTex();
	virtual void Draw();
	virtual void UpDate();
	virtual void ReleaseTex();

	void ReleaseUITexture(TEXTURE_DATA* texture);

	const EndProductionInfo* GetEndProductionInfo()const { return &m_EndProductionInfo; }


};

#endif