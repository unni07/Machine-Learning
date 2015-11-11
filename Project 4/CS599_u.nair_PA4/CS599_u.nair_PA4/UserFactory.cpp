#include "precompiled.h"
#include "UserFactory.h"
#include "User.h"

UserFactory& UserFactory::instance()
{
	static UserFactory uFactory;
	return uFactory;
}

User* UserFactory::getUser(std::string name)
{
	auto itr = userDatabase.find(name);
	if (itr!=userDatabase.end())
	{
		return itr->second;
	}
	userDatabase[name] = new User(name);
	return userDatabase[name];
}

std::map<std::string, User*> UserFactory::getDatabase() const
{
	return userDatabase;
}

UserFactory::UserFactory()
{
}


UserFactory::~UserFactory()
{
	userDatabase.clear();
}
