#ifndef PRODUCTIONMANAGER_H_
#define PRODUCTIONMANAGER_H_

#include "../Production/ProductionBase.h"


#include <vector>

//ëOï˚êÈåæ
class StartProduction;
class EndProduction;

class ProductionManager
{
public:
	static ProductionManager* Instance();

	void Init();
	void CreateProduction();
	void LoadTex();
	void Draw();
	void UpDate();
	void ReleaseTex();

	const StartProduction* GetStartProduction()const { return m_StartProduction; }
	const EndProduction* GetEndProduction()const { return m_EndProduction; }

protected:
	ProductionManager(){}
	~ProductionManager(){}

private:
	static ProductionManager* p_instance;
	StartProduction* m_StartProduction;
	EndProduction* m_EndProduction;
};

#endif