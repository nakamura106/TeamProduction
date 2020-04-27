#include "ProductionManager.h"

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
	for (int i = 0; i < m_Production.size(); i++)
	{
		m_Production[i]->Init();
	}
}

void ProductionManager::CreateProduction()
{
	m_Production.push_back(new StartProduction);
	m_Production.push_back(new EndProduction);

}

void ProductionManager::LoadTex()
{
	for (int i = 0; i < m_Production.size(); i++)
	{
		m_Production[i]->LoadTex();
	}
}

void ProductionManager::Draw()
{
	for (int i = 0; i < m_Production.size(); i++)
	{
		m_Production[i]->Draw();
	}
}

void ProductionManager::UpDate()
{
	for (int i = 0; i < m_Production.size(); i++)
	{
		m_Production[i]->UpDate();
	}
}

void ProductionManager::ReleaseTex()
{
	for (int i = 0; i < m_Production.size(); i++)
	{
		m_Production[i]->ReleaseTex();
	}
}
