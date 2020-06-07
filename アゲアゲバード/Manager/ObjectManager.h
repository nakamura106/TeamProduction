#ifndef OBJECTMANAGER_H_
#define OBJECTMANAGER_H_

#include"../Object/ObjectBase.h"
#include"../Utility/Collision.h"
#include<string>
#include<vector>
#include<map>

//前方宣言
namespace Character {
	class Player;
}
class Block;
class Item;
class ItemBox;
class Pot;
class Oil;
class FillOil;
class WorldBox;

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
	 Character::Player* GetPlayer(std::string key_) { return m_player[key_]; }
	 Oil* GetOil() { return m_oil; }
	 FillOil* GetFillOil() { return m_filloil; }
	 std::vector<Item*>* GetItem() { return &m_Item; }
	 std::vector<Block*>* GetBlock() { return &m_Block; }
	
	
protected:
	ObjectManager();
	~ObjectManager();

private:
	static ObjectManager* p_instance;

	void CreateItemBox();

	Collision* m_collision;
	Pot* m_pot;
	Oil* m_oil;
	FillOil* m_filloil;
	WorldBox* m_world_box;
	
	std::map<std::string,Character::Player*> m_player;
	std::vector<Block*> m_Block;
	std::vector<Item*> m_Item;
	std::vector<ItemBox*> m_ItemBox;
};

#endif