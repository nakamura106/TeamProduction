#ifndef CSV_H_
#define CSV_H_

struct PlayerData {
	char name[32];		// ���O
	float pos_x;		// ���Wx
	float pos_y;		// ���Wy
	float pos_z;		// ���Wz
};

//void LoadFile();	// C�p
int LoadFile();		// C++�p

void OutPutFile();

#endif