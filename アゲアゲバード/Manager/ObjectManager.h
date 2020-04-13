#ifndef OBJECTMANAGER_H_
#define OBJECTMANAGER_H_

#include"../Object/ObjectBase.h"
#include<vector>

class ObjectManager
{
public:
	static ObjectManager* Instance();

	//マネージャーの初期化※コンストラクタ時のみ
	void Init() {};
	//オブジェクト生成
	void CreateObject();//マップ、プレイヤー(2まで)、アイテム。ブロックは別配列
	void CreateBlock();
	void CreateItem();
	void CreatePlayer();	// K新しく追加した
	void Update();
	void Draw();
	void AllDeleteObject();
	


	//ObjectBase* GetPlayerObject() {};

	//ObjectBase* GetCharaObject() {};

protected:
	ObjectManager();
	~ObjectManager();

private:
	static ObjectManager* p_instance;
	std::vector<ObjectBase*> m_Object;
	std::vector<ObjectBase*> m_Block;
	std::vector<ObjectBase*> m_Item;
	std::vector<ObjectBase*> m_player;

};

#endif