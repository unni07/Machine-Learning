#include "precompiled.h"
#include "User.h"


User::User(std::string name)
{
	username = name;
}

User::~User()
{
	myWatchList.clear();
}

void User::addRating(std::string movieName, float rating)
{
	myWatchList[movieName] = rating;
}