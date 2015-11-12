#include "precompiled.h"
#include "Shop.h"
#include "RecommenderSystem.h"
void output(std::ofstream& os, std::vector<float> ratings)
{
	auto itr = ratings.begin();
	auto itrEnd = ratings.end();
	while (itr != itrEnd)
	{
		os << *itr << "\t";
		++itr;
	}
	os << std::endl;
}
int main()
{
	Shop shop;
	shop.initialize("config.csv");
	shop.fetchDatabase("data.csv");
	shop.testData("test.csv");

	auto Rs1 = RecommenderSystem::instance().getRecommendation("U1");
	auto Rs2 = RecommenderSystem::instance().getRecommendation("U2");
	auto Rs3 = RecommenderSystem::instance().getRecommendation("U3");
	std::ofstream file;
	file.open("Output.txt");
	file << "Recommendation for new users U1 , U2, U3 are as follows: " << std::endl;
	file << std::endl;
	file << std::endl;
	file << "Recommendation for U1:  " << Rs1.first << std::endl;
	
	file << "Recommendation for U2:  " << Rs2.first << std::endl;
	
	file << "Recommendation for U3:  " << Rs3.first << std::endl;

	file << "final Table: " << std::endl<< "U1" << "\t";
	output(file, Rs1.second);
	file << "U2" << "\t";
	output(file, Rs2.second);
	file << "U3" << "\t";
	output(file, Rs3.second);
	file.close();
	return 0;
}


/*
Dataset for data bases;
user database
movie database


*/