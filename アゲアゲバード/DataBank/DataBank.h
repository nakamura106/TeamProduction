#ifndef DATABANK_H_
#define DATABANK_H_

#include <d3dx9.h>
#include<vector>
#include"../Object/ObjectBase.h"
#include"../Scene/BaseScene.h"
#include"Definition.h"

//î•ñ•Û‘¶ƒNƒ‰ƒX
class DataBank
{
public:
	static DataBank* Instance();

	
#pragma region Set

	
#pragma endregion

#pragma region Get


#pragma endregion

protected:
	DataBank();
	~DataBank();

private:
	static DataBank* p_instance;

};

#endif // !DATABANK_H_
