#ifndef PRODUCTIONMANAGER_H_
#define PRODUCTIONMANAGER_H_

#include "../Production/ProductionBase.h"


#include <vector>

//�O���錾
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

	StartProduction* GetStartProduction()const { return m_StartProduction; }
	EndProduction* GetEndProduction()const { return m_EndProduction; }

protected:
	ProductionManager() {
		CreateProduction();
		Init();
	}
	~ProductionManager(){}

private:
	static ProductionManager* p_instance;
	StartProduction* m_StartProduction;
	EndProduction* m_EndProduction;
};

#endif