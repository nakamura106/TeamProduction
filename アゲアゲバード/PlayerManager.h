#ifndef PLAYER_MANAGER_H_
#define PLAYER_MANAGER_H_

#include "Player.h"

class PlayerManager {
public:
	PlayerManager();
	~PlayerManager();

public:
	void Init();
	void Update();
	void Draw();

private:
	Character::Player* m_p_player;

};

#endif