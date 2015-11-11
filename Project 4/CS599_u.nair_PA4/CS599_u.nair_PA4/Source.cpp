#include "precompiled.h"
#include "Shop.h"
#include "RecommenderSystem.h"

int main()
{
	Shop shop;
	shop.initialize("config.csv");
	shop.fetchDatabase("data.csv");
	shop.testData("test.csv");

	auto Rs = RecommenderSystem::instance().getRecommendation("U1");
	std::ofstream file;
	file.open("Output.txt");
	file << "Recommendation for new users U1 , U2, U3 are as follows: " << std::endl;
	file << std::endl;
	file << std::endl;
	file << "Recommendation for U1:  " << Rs << std::endl;
	Rs = RecommenderSystem::instance().getRecommendation("U2");
	file << "Recommendation for U2:  " << Rs << std::endl;
	Rs = RecommenderSystem::instance().getRecommendation("U3");
	file << "Recommendation for U3:  " << Rs << std::endl;

	return 0;
}

/*
Dataset for data bases;
user database
movie database


*/