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
	if (m_Object["oil"] != nullptr)
	{
		delete m_Object["oil"];
		m_Object["oil"] = nullptr;
	}
	if (m_Object["filloil"] != nullptr)
	{
		delete m_Object["filloil"];
		m_Object["filloil"] = nullptr;
	}
	if (m_player["player1"] != nullptr)
	{
		delete m_player["player1"];
		m_player["player1"] = nullptr;
	}
	for (int i = 0; m_Block.size(); i++)
	{
		if (m_Block[i] != nullptr)
		{
			delete m_Block[i];
			m_Block[i] = nullptr;
		}
	}
	for (int i = 0; m_Item.size(); i++)
	{
		if (m_Item[i] != nullptr)
		{
			delete m_Item[i];
			m_Item[i] = nullptr;
		}
	}
	for (int i = 0; m_ItemBox.size(); i++)
	{
		if (m_ItemBox[i] != nullptr)
		{
			delete m_ItemBox[i];
			m_ItemBox[i] = nullptr;
		}
	}
	
}

void ObjectManager::AllDeleteObject()
{
	std::map<std::string,ObjectBase*>().swap(m_Object);
	std::vector<Block*>().swap(m_Block);
	std::vector<Item*>().swap(m_Item);
	std::vector<GetItemBox*>().swap(m_ItemBox);
	std::map<std::string,Character::Player*>().swap(m_player);
}

D3DXVECTOR3 ObjectManager::BlockInstallation(D3DXVECTOR3 eyepos_, D3DXVECTOR3 forward_)
{
	D3DXVECTOR3 blockpos;
	blockpos = eyepos_+(forward_*4.0f);
	blockpos /= 2.0f;
	blockpos.x = roundf(blockpos.x);
	blockpos.y = roundf(blockpos.y);
	blockpos.z = roundf(blockpos.z);
	blockpos *= 2.0f;
	return blockpos;
}



void ObjectManager::CreateObject()
{
	m_pot = (new Pot);
	m_Object["oil"]=(new Oil);
	m_Object["filloil"]=(new FillOil);
	CreateItemBox();
}
 
bool ObjectManager::CreateBlock()
{

	D3DXVECTOR3 eyepos;
	eyepos = BlockInstallation(m_camera->GetCameraData()->m_CameraPos , m_camera->GetCameraData()->m_Forward);

	for (const auto& itr : m_Block)
	{
		if (itr->GetBlockData()->m_pos == eyepos)
		{
			return false;
		}
	}
	m_Block.push_back(new Block);
	return true;
}

void ObjectManager::CreateItem()
{
	m_Item.push_back(new Item);
}

void ObjectManager::CreateItemBox()
{
	srand((unsigned)time(NULL));
	for (int i = 0; i <= 20; i++)
	{
		m_ItemBox.push_back(new GetItemBox);
	}
}

void ObjectManager::CreatePlayer()
{
	m_player["player1"]=(new Character::Player(0.0f, 5.0f, 0.0f));
	
}

void ObjectManager::Update()
{
	
	m_Object["pot"]->Update();
	m_Object["oil"]->Update();
	m_Object["filloil"]->Update();
	
	for (int i = 0; i < m_Block.size(); i++)
	{
		m_Block[i]->Update();
		if (m_Object["oil"]->GetObjectData()->m_pos.y>=m_Block[i]->GetBlockData()->m_pos.y)
		{
			m_Block.erase(m_Block.begin()+i);
		}
	}
	for (int i = 0; i < m_Item.size(); i++)
	{
		m_Item[i]->Update();

		if (m_Object["oil"]->GetObjectData()->m_pos.y >= m_Item[i]->GetItemData()->m_pos.y)
		{
			m_Item.erase(m_Item.begin() + i);
		}
		
	}
	for (int i = 0; i < m_ItemBox.size(); i++)
	{
		m_ItemBox[i]->Update();
		if (m_collision->HitBox(m_ItemBox[i]->GetBoxData()->m_pos, m_player["player1"]->GetPlayerData()->m_pos, 2.0f, 2.0f))
		{
			m_player["player1"]->PlusBlockStock(5);
			m_ItemBox.erase(m_ItemBox.begin() + i);
		}
		
	}
	
	m_player["player1"]->Update();
	
}

void ObjectManager::Draw()
{
	m_Object["pot"]->Draw();
	m_Object["oil"]->Draw();
	m_Object["filloil"]->Draw();
	
	for (int i = 0; i < m_Block.size(); i++)
	{	
		m_Block[i]->Draw();
	}

	for (int i = 0; i < m_Item.size(); i++)
	{
		m_Item[i]->Draw();
	}
	for (int i = 0; i < m_ItemBox.size(); i++)
	{
		m_ItemBox[i]->Draw();
	}
	
	m_player["player1"]->Draw();
	
}
