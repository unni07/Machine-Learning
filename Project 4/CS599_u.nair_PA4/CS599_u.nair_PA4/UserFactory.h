#pragma once
class User;
class UserFactory
{
public:
	static UserFactory& instance();
	/**this will fetch the user if exists
	 *or creates the user if its not there in the database and
	 *returns the pointer to the user*/
	User* getUser(std::string name);
private:
	UserFactory();
	~UserFactory();
	/**container will hold all the users in the system
	 *this ensuring that only one user exists*/
	std::map<std::string, User*>  userDatabase;
};

