#ifndef PRODUCTIONMANAGER_H_
#define PRODUCTIONMANAGER_H_

#include "../Production/ProductionBase.h"
#include <vector>

class ProductionManager
{
public:


private:
	static ProductionManager* p_instance;
	std::vector<ProductionBase> m_Production;
};

#endif