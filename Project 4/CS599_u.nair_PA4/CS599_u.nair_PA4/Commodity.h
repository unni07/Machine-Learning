#pragma once
class User;
class Commodity
{
public:
	Commodity(std::string name);
	~Commodity();
	void adduser(User *user);
private:
	/**user list will hold all the people who used this commodity*/
	std::vector<User*> userlist;
	/**stores the name of the commodity*/
	std::string commodityName;
};

