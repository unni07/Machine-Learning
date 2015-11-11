#pragma once
class Commodity;
class User
{
public:
	 User(std::string name);
	~User();
	/**this funtion will add the movie name watched by the user and rating given by the user*/
	void addRating(std::string movieName, float rating);
	
private:
	/**this map of string and float will hold the movie names
	 *and the rating the user gave.
	 */
	std::map<std::string, float> myWatchList;
	//std::map<Commodity *, float> myWatchList;
	/**stores the name of the user*/
	std::string username;

};

