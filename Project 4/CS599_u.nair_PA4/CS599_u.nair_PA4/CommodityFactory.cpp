#include "precompiled.h"
#include "CommodityFactory.h"
#include "Commodity.h"

CommodityFactory& CommodityFactory::instance()
{
	static CommodityFactory cFactory;
	return cFactory;
}

Commodity* CommodityFactory::getUser(std::string name)
{
	auto itr = commodityDatabase.find(name);
	if (itr != commodityDatabase.end())
	{
		return itr->second;
	}
	commodityDatabase[name] = new Commodity(name);
	return commodityDatabase[name];
}

CommodityFactory::CommodityFactory()
{
}


CommodityFactory::~CommodityFactory()
{
	commodityDatabase.clear();
}
