#include"ObjectManager.h"
#include"../Object/Pot.h"
#include"../Object/Block.h"
#include"../Object/Oil.h"
#include"../Object/Item.h"
#include "../Player/Player.h"
#include"../DataBank/DataBank.h"



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
		if (m_Object[i] != nullptr)
		{
			delete m_Object[i];
			m_Object[i] = nullptr;
		}
	}
	for (int i = 0; m_Block.size(); i++)
	{
		if (m_Block[i] != nullptr)
		{
			delete m_Block[i];
			m_Block[i] = nullptr;
		}
	}
}

void ObjectManager::AllDeleteObject()
{
	std::vector<ObjectBase*>().swap(m_Object);
	std::vector<ObjectBase*>().swap(m_Block);
}

void ObjectManager::CreateObject()
{
	m_Object.push_back(new Pot);
	m_Object.push_back(new Oil);
	m_Object.push_back(new FillOil);
	m_Object.push_back(new Character::Player(0.0f, 0.0f, 0.0f));
	m_Object.push_back(new Item);

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
		if (DataBank::Instance()->GetOilPos()>=m_Block[i]->GetPos().y)
		{
			m_Block.erase(m_Block.begin()+i);
		}
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
