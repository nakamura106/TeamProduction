#include "PlayerManager.h"

PlayerManager::PlayerManager()
{
	m_p_player = nullptr;
	Init();
}

PlayerManager::~PlayerManager()
{
	if (m_p_player != nullptr)
	{
		delete m_p_player;
		m_p_player = nullptr;
	}
}

void PlayerManager::Init()
{
	if (m_p_player == nullptr)
	{
		m_p_player = new Character::Player(0.0f, 0.0f, 0.0f);
	}
}

void PlayerManager::Update()
{
	if (m_p_player != nullptr)
	{
		m_p_player->Update();
	}
}

void PlayerManager::Draw()
{
	if (m_p_player != nullptr)
	{
		m_p_player->Draw();
	}
}