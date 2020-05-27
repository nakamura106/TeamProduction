#ifndef OIL_H_
#define OIL_H_

#include"ObjectBase.h"
#include"../Manager/ProductionManager.h"
#include"../Manager/ObjectManager.h"

class Oil :public ObjectBase
{
private:
	struct OilData :public ObjectData{

		TEXTURE_DATA m_oiltex;

		float tex_tu, tex_tv;

		int m_uv_counter;
	}m_oil_data;

	ObjectManager* m_object_manager = ObjectManager::Instance();
	ProductionManager* m_production_manager = ProductionManager::Instance();

public:
	Oil();
	~Oil() {};

	void Update()override;
	void Draw()override;

	const OilData* GetOilData()const { return &m_oil_data; }

private:
	void UpdateUV();
	void RisingOil();

};

class FillOil :public ObjectBase
{
private:
	struct FillOilData :public ObjectData {

		TEXTURE_DATA m_filloiltex;

		D3DXVECTOR3 angle2_;
		D3DXVECTOR3 angle3_;
		D3DXVECTOR3 angle4_;

		float tex_tu, tex_tv;

		int m_uv_counter;

		bool m_fall_flag;
	}m_filloildata;

	ProductionManager* m_production_manager = ProductionManager::Instance();

public:
	FillOil();
	~FillOil() {};

	void Update()override;
	void Draw()override;

	const FillOilData* GetFillOilData()const { return &m_filloildata; }

private:

	void UpdateUV();
	void FallFillOil();

};


#endif
