#ifndef PRODUCTIONMANAGER_H_
#define PRODUCTIONMANAGER_H_

#include "../Production/ProductionBase.h"
#include "../Production/StartProduction.h"
#include "../Production/EndProduction.h"

#include <vector>

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
protected:
	ProductionManager(){}
	~ProductionManager(){}

private:
	static ProductionManager* p_instance;
	std::vector<ProductionBase*> m_Production;
};

#endif