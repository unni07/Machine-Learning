#pragma once

class Commodity;
class CommodityFactory
{
public:
	static CommodityFactory& instance();
	/**this will fetch the commodity if it exists
	*or creates the user if its not there in the database and
	*returns the pointer to the user*/
	Commodity* getUser(std::string name);
	
private:
	CommodityFactory();
	~CommodityFactory();

	/**container will hold all the commodity names in the shop
	*this ensuring uniquness*/
	std::map<std::string, Commodity*>  commodityDatabase;
};

