#ifndef OBJECTMANAGER_H_
#define OBJECTMANAGER_H_

#include"../Object/ObjectBase.h"
#include"../Utility/Collision.h"
#include"../DataBank/Definition.h"
#include"../Player/Player.h"
#include<vector>
#include<map>

//前方宣言
class Block;
class Item;
class GetItemBox;
class Player;
class Pot;

class ObjectManager
{
public:
	static ObjectManager* Instance();

	//マネージャーの初期化※コンストラクタ時のみ
	void Init() {};

	//オブジェクト生成
	void CreateObject();//マップ、プレイヤー(2まで)。アイテム、ブロックは別配列
	bool CreateBlock();
	void CreateItem();
	void CreatePlayer();	// K新しく追加した

	void Update();
	void Draw();
	void AllDeleteObject();
	
	D3DXVECTOR3 BlockInstallation(D3DXVECTOR3 eyepos_, D3DXVECTOR3 forward_);
	
	Pot* GetMap() { return m_pot; }
	std::vector<Item*>* GetItem() { return &m_Item; }
	std::vector<Block*>* GetBlock() { return &m_Block; }
	Character::Player* GetPlayer(std::string key_) { return m_player[key_]; }
	ObjectBase* GetOil(std::string key_) { return m_Object[key_]; }
	CAMERA* GetCamera() { return m_camera; }
	
protected:
	ObjectManager();
	~ObjectManager();

private:
	static ObjectManager* p_instance;

	void CreateItemBox();

	Collision* m_collision;
	CAMERA* m_camera;
	Pot* m_pot;
	std::map<std::string,ObjectBase*> m_Object;
	std::map<std::string,Character::Player*> m_player;
	std::vector<Block*> m_Block;
	std::vector<Item*> m_Item;
	std::vector<GetItemBox*> m_ItemBox;
};

#endif