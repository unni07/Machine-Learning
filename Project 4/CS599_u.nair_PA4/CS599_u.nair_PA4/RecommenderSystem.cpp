#include "precompiled.h"
#include "RecommenderSystem.h"
#include "UserFactory.h"
#include "User.h"
#include "MathUtility.h"

RecommenderSystem& RecommenderSystem::instance()
{
	static RecommenderSystem rs;
	return rs;
}

std::pair<std::string, std::vector<float>> RecommenderSystem::getRecommendation(std::string username)
{
	std::string reqdUserName = getClosestUser(username);
	std::string output;
	float maxRating = 11.0f;
	std::vector<float> ratings;
	auto movieList = UserFactory::instance().getUser(reqdUserName)->getWatchList();
	auto reqdUsersMovieList = UserFactory::instance().getUser(username)->getWatchList();
	auto itr = movieList.begin();
	auto itrEnd = movieList.end();
	bool found = false;
	bool fillUptheList = true;
	while (maxRating > 0)
	{
		itr = movieList.begin();
		while (itr != itrEnd && found == false)
		{
			if (itr->second == maxRating)
			{
				float rating = reqdUsersMovieList.find(itr->first)->second;
				if (rating == 0)
				{
					output = itr->first;
					found = true;
				}
			}
			++itr;
		}
		
		maxRating = maxRating -1.0f;
	}
	itr = movieList.begin();
	itrEnd = movieList.end();
	while (itr != itrEnd)
	{
		float rating = reqdUsersMovieList.find(itr->first)->second;
		if (rating == 0)
		{
			ratings.push_back(itr->second);
		}
		else
		{
			ratings.push_back(rating);
		}
		++itr;
	}
	return std::make_pair(output,ratings);
}

RecommenderSystem::RecommenderSystem()
{
}


RecommenderSystem::~RecommenderSystem()
{
}

std::string RecommenderSystem::getClosestUser(std::string username)
{
	/*
	get me movie list of this username
	movies that I have watched

	*/

	auto movielistforusername = UserFactory::instance().getUser(username)->getWatchList();
	auto itrReqduser = movielistforusername.begin();
	auto itrReqduserEnd = movielistforusername.end();
	double minDistance = 0.0f;
	double maxValue = FLT_MIN;
	std::string closestUser;

	auto allusers = UserFactory::instance().getDatabase();
	auto itrAllUsers = allusers.begin();
	auto itrAllUsersEnd = allusers.end();
	--itrAllUsersEnd;
	--itrAllUsersEnd;
	--itrAllUsersEnd;
	while (itrAllUsers != itrAllUsersEnd)
	{
		itrReqduser = movielistforusername.begin();
		while (itrReqduser != itrReqduserEnd)
		{
			if (itrReqduser->second != 0)
			{
				auto movieListperUser = UserFactory::instance().getUser(itrAllUsers->first)->getWatchList();
				//auto itrMovieList = movieListperUser.begin();
				//auto itrMovieListEnd = movieListperUser.end();

				float rating = movieListperUser.find(itrReqduser->first)->second;
				//minDistance = minDistance + MathUtility::instance().minkowskiDistance(rating, itrReqduser->second, 1);
				MathUtility::instance().pushDetailsForCalculation(rating, itrReqduser->second);
			}
			++itrReqduser;
			
		}
		minDistance = MathUtility::instance().calculateCosine();
		MathUtility::instance().clear();
		if (minDistance > maxValue)
		{
			maxValue = minDistance;
			closestUser = itrAllUsers->first;
			minDistance = 0.0f;
			
		}
		++itrAllUsers;
	}
	return closestUser;
	
	
	
	
	
	
	
	/*
		if (itrReqduser->second != -1)
		{
			
			while (itrAllUsers != itrAllUsersEnd)
			{
				float rating = itrAllUsers->second->getWatchList().find(itrReqduser->first)->second;
				minDistance = minDistance + MathUtility::instance().minkowskiDistance(rating, itrReqduser->second, 1);
			}
			if (minDistance < maxValue)
			{
				maxValue = minDistance;
				closestUser = itrReqduser->first;
			}
		}
	}







































	auto movieListUser1 = UserFactory::instance().getUser(username)->getWatchList();
	auto itr = movieListUser1.begin();
	auto itrEnd = movieListUser1.end();
	float maxVal = FLT_MAX;
	std::string closestUser;
	
	while (itr != itrEnd)
	{
		float summation = 0.0;
		float ratingUnkwonUser = itr->second;
		if (itr->second != -1)
		{
			auto userList = CommodityFactory::instance().getUser(itr->first)->getUsers();
			auto itr2 = userList.begin();
			auto itrEnd2 = userList.end();
			while (itr2 != itrEnd2)
			{
				auto movieListUser2 = UserFactory::instance().getUser((*itr2)->getUserName())->getWatchList();
				float ratingKnownUser = movieListUser2.find(itr->first)->second;
				summation =  MathUtility::instance().minkowskiDistance(ratingUnkwonUser, ratingKnownUser, 1);
				if (summation < maxVal)
				{
					maxVal = summation;
					closestUser = (*itr2)->getUserName();
				}
				++itr2;
			}
			
		}
		
		++itr;
	}

	return closestUser;*/
}