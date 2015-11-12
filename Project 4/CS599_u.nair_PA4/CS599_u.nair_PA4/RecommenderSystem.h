#pragma once
class RecommenderSystem
{
public:
	static RecommenderSystem& instance();
	/**this will fetch a recommendation for the user based on the username*/
	std::pair<std::string,std::vector<float>> getRecommendation(std::string username);
private:
	RecommenderSystem();
	~RecommenderSystem();
	/**private processor*/
	std::string getClosestUser(std::string username);
};

