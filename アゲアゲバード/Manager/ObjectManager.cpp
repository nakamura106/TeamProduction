#include"ObjectManager.h"
#include"../Object/Pot.h"
#include"../Object/Block.h"

ObjectManager* ObjectManager::p_instance = 0;

ObjectManager* ObjectManager::Instance()
{
	if (p_instance == 0)
	{
		p_instance = new ObjectManager;
	}

	return p_instance;
}

ObjectManager::ObjectManager()
{

}

ObjectManager::~ObjectManager()
{
	for (int i = 0; m_Object.size(); i++)
	{
		delete m_Object[i];
	}
	for (int i = 0; m_Block.size(); i++)
	{
		delete m_Block[i];
	}
}

void ObjectManager::AllDeleteObject()
{
	for (int i = 0; m_Object.size(); i++)
	{
		delete m_Object[i];
	}
	for (int i = 0; m_Block.size(); i++)
	{
		delete m_Block[i];
	}
}

void ObjectManager::CreateObject()
{
	m_Object.push_back(new Pot);
}

void ObjectManager::CreateBlock()
{
	m_Block.push_back(new Block);
}

void ObjectManager::Update()
{
	for (int i = 0;i< m_Object.size(); i++)
	{
		m_Object[i]->Update();
	}
	for (int i = 0; i < m_Block.size(); i++)
	{
		m_Block[i]->Update();
	}
}

void ObjectManager::Draw()
{
	for (int i = 0; i< m_Object.size(); i++)
	{
		m_Object[i]->Draw();
	}
	for (int i = 0; i < m_Block.size(); i++)
	{
		m_Block[i]->Draw();
	}
}
