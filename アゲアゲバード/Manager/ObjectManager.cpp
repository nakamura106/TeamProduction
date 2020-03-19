#include"ObjectManager.h"
#include"../Object/Pot.h"

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
	for (int i = 0; Object.size(); i++)
	{
		delete Object[i];
	}
}

void ObjectManager::AllDeleteObject()
{
	for (int i = 0; Object.size(); i++)
	{
		delete Object[i];
	}
}

void ObjectManager::CreateObject()
{
	Object.push_back(new Pot);

}

void ObjectManager::Update()
{
	for (int i = 0;i< Object.size(); i++)
	{
		Object[i]->Update();
	}
}

void ObjectManager::Draw()
{
	for (int i = 0; i<Object.size(); i++)
	{
		Object[i]->Draw();
	}
}
