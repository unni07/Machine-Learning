#pragma once
class User;
class Commodity
{
public:
	Commodity(std::string name);
	~Commodity();
	void adduser(User *user,float);
	/** this fetches the user databse*/
	std::unordered_map<User*, float> getUsers()const;
private:
	/**user list will hold all the people who used this commodity*/
	//std::vector<User*> userlist;
	std::unordered_map<User*,float> userlist;
	/**stores the name of the commodity*/
	std::string commodityName;
};

