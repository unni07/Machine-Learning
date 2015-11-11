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

void Commodity::adduser(User* user, float rating)
{
	userlist[user] = rating;
}

//void Commodity::adduser(User* user) 
//{
//	userlist.push_back(user);
//}

std::unordered_map<User*, float> Commodity::getUsers() const
{
	return userlist;
}
