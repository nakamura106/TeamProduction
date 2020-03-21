#ifndef DATABANK_H_
#define DATABANK_H_

#include <d3dx9.h>

//î•ñ•Û‘¶ƒNƒ‰ƒX
class DataBank
{
public:
	static DataBank* Instance();

	void ResetData() {}

	void SetCameraPos(D3DXVECTOR3 eyepos_);

	D3DXVECTOR3 GetCameraPos() { return m_Camera_Pos; }

protected:
	DataBank();
	~DataBank();

private:
	static DataBank* p_instance;


	D3DXVECTOR3 m_Camera_Pos;
};

#endif // !DATABANK_H_
