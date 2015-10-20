#include "KMean.h"
#include <cmath>
#include <algorithm>
#include <numeric>

#define MAX_ITERATOR 5
KMean& KMean::getInstance()
{
	static KMean kmean;
	return kmean;
}

void KMean::readFile(std::string fileName,int numClusters)
{
	getRawFormat(fileName);
	k = numClusters;
	clustersData.reserve(k);
	processData();
}

void KMean::printOutputwithFileName(std::string)
{

}

void KMean::getRawFormat(std::string fileName)
{
	reader.readFile(fileName,0);
	rawFromat = reader.returnRawDatabse();
	points.reserve(rawFromat.size());
	
}

void KMean::convertTheFileintoKMeanFormat()
{
	if (rawFromat.size() == 0)
	{
		std::cout << "No data to Process"<<std::endl;
	}
	lines::iterator itr;
	auto itrBegin = rawFromat.begin();
	auto itrEnd   = rawFromat.end();
	itr = itrBegin;
	size_t i = 0;
	std::string value;
	auto sizeofLine = itr->size();
	while (i<sizeofLine)
	{
		auto index = itr->at(i);
		i++;
		if (index!=',')
		{
			value = value + index;
		}
		if (index == ',' || i==sizeofLine)
		{
			if (value.size()!=0)
			{
				filter.push_back(value);
				value.clear();
			}
		}
		
	}
	++itr;

	for (; itr != itrEnd; ++itr)
	{
		size_t        pos = itr->find(",");
		std::string  data = itr->substr(++pos);
		size_t       posX = data.find(",");
		std::string dataX = data.substr(0,posX++);
		std::string dataY = data.substr(posX);
		Points *      pts = new Points();
		pts->position.xposition = std::stoi(dataX);
		if (pts->position.xposition > maxValueX)
			maxValueX = pts->position.xposition;
		pts->position.yposition = std::stoi(dataY);
		if (pts->position.yposition > maxValueY)
			maxValueY = pts->position.yposition;
		points.push_back(pts);
	
	}
}

void KMean::initRandomClusters()
{
	for (int i = 0; i < k; i++)
	{
		cluster* cls = new cluster();
		cls->clusterID = i;
		cls->position.xposition = /*static_cast<float>*/(rand() % maxValueX);
		cls->position.yposition = /*static_cast<float>*/(rand() % maxValueY);
		clustersData.push_back(cls);
	}
}

void KMean::processData()
{
	convertTheFileintoKMeanFormat(); // need to change the invoker loaction
	initRandomClusters();
}

void KMean::clustering()
{
	auto itrPoints        = points.begin();
	auto itrBeginPoints   = points.begin();
	auto itrEndPoints     = points.end();
	auto itrClusters      = clustersData.begin();
	auto itrBeginClusters = clustersData.begin();
	auto itrEndClusters   = clustersData.end();
	std::map<int,double>distances;
	int iterator = 0;
	while (iterator < MAX_ITERATOR)
	{
		for (; itrPoints != itrEndPoints; ++itrEndPoints)
		{
			float max = INT_MIN;
			for (; itrEndClusters != itrBeginClusters; ++itrClusters)
			{
				auto tempDistance = distance((*itrEndClusters)->position, (*itrPoints)->position);
				distances.insert(std::make_pair((*itrClusters)->clusterID, tempDistance));
			}
			auto mapItrbegin = distances.begin();
			auto mapItrEnd = distances.end();
			auto itr = std::max_element(mapItrbegin, mapItrEnd);
			(*itrPoints)->clusterGroupNum = itr->first;
			clustersX[itr->first].push_back((*itrPoints)->position.xposition);
			clustersY[itr->first].push_back((*itrPoints)->position.yposition);
			distances.clear();
		}
		recompileClusterPositions();
	}
}

double KMean::distance(positionVector pts1, positionVector pts2)
{
	auto diffx = pow((pts1.xposition - pts2.xposition), 2);
	auto diffy = pow((pts1.yposition - pts2.yposition), 2);
	auto distance = sqrt(diffx + diffy);

	return distance;
}

void KMean::recompileClusterPositions()
{
	for (int i = 0; i < k;i++)
	{
		auto vX = clustersX[i];
		auto sumX = std::accumulate(vX.begin(), vX.end(), 0.0);
		auto meanX = sumX / vX.size();

		auto vY = clustersY[i];
		auto sumY = std::accumulate(vY.begin(), vY.end(), 0.0);
		auto meanY = sumY / vY.size();

		clustersData[i]->position.xposition = static_cast<int>(meanX);
		clustersData[i]->position.yposition = static_cast<int>(meanY);
	}
}

KMean::KMean()
{
	maxValueX = INT_MIN;
	maxValueY = INT_MIN;
}

KMean::~KMean()
{
}