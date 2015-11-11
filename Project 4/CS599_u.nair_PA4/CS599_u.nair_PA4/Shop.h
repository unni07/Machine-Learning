#pragma once
class Shop
{
public:
	Shop();
	~Shop();
	/**this function is responsible for inisitializing the user and commodity factory*/
	void initialize(std::string configFileName);
	/**this will accept the filename of the database and setup the dataset to be used by recommender system*/
	void fetchDatabase(std::string databaseName);
private:
	/**stores the name of the movies*/
	std::vector<std::string> movienames;
	/**stores the name of the user*/
	std::vector<std::string> usernames;


};

