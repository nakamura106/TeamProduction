#include "ProductionManager.h"
#include "../Production/StartProduction.h"
#include "../Production/EndProduction.h"

ProductionManager* ProductionManager::p_instance = 0;

ProductionManager* ProductionManager::Instance()
{
	if (p_instance == 0)
	{
		p_instance = new ProductionManager;
	}
	return p_instance;
}

void ProductionManager::Init()
{
	m_StartProduction->Init();
	m_EndProduction->Init();
}

void ProductionManager::CreateProduction()
{
	m_StartProduction = (new StartProduction);
	m_EndProduction = (new EndProduction);
}

void ProductionManager::LoadTex()
{
	m_StartProduction->LoadTex();
	m_EndProduction->LoadTex();
}

void ProductionManager::Draw()
{
	m_StartProduction->Draw();
	m_EndProduction->Draw();
}

void ProductionManager::UpDate()
{
	m_StartProduction->UpDate();
	m_EndProduction->UpDate();
}

void ProductionManager::ReleaseTex()
{
	m_StartProduction->ReleaseTex();
	m_EndProduction->ReleaseTex();
}
