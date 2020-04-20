#ifndef CSV_H_
#define CSV_H_

struct PlayerData {
	char name[32];		// 名前
	float pos_x;		// 座標x
	float pos_y;		// 座標y
	float pos_z;		// 座標z
};

//void LoadFile();	// C用
int LoadFile();		// C++用

void OutPutFile();

#endif