#ifndef DATABANK_H_
#define DATABANK_H_

#include <d3dx9.h>

//èÓïÒï€ë∂ÉNÉâÉX
class DataBank
{
public:
	static DataBank* Instance();

	void ResetData() {}

	void SetCameraPos(D3DXVECTOR3 eyepos_);

	void SetOilPos(float oilelevation_);
	
	D3DXVECTOR3 GetCameraPos() { return m_Camera_Pos; }

	float GetOilPos() { return m_oilelevation; }
	
protected:
	DataBank();
	~DataBank();

private:
	static DataBank* p_instance;

	float m_oilelevation;

	D3DXVECTOR3 m_Camera_Pos;

};

#endif // !DATABANK_H_
