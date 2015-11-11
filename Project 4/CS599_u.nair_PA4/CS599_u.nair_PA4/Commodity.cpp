#include "precompiled.h"
#include "Commodity.h"
#include "User.h"

Commodity::Commodity(std::string name)
{
	commodityName = name;
}

Commodity::~Commodity()
{
	userlist.clear();
}

void Commodity::adduser(User* user) 
{
	userlist.push_back(user);
}

