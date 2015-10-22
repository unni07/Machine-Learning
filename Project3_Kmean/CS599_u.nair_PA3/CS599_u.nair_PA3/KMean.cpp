#include "KMean.h"
#include <cmath>
#include <algorithm>
#include <numeric>

#define MAX_ITERATOR 8
#include <ctime>

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
	std::ofstream file;
	file.open("Output.txt");
	file << "Kmean Clustering: " << std::endl << std::endl << std::endl;
	
	auto itr = clustersData.begin();
	auto itrBegin = clustersData.begin();
	auto itrEnd = clustersData.end();

	auto itrFilter = filter.begin();
	auto itrBeginFilter = filter.begin();
	auto itrEndFilter = filter.end();
	bool attributeStatus = true;
	file << "Cluster Centroid " << std::endl << std::endl;
	++itrFilter;
	for (; itrFilter != itrEndFilter; ++itrFilter)
	{
		file << (*itrFilter) << "\t";
		if (attributeStatus)
		{
			for (; itr != itrEnd; ++itr)
			{
				file << (*itr)->position.xposition << "\t";
			}
			attributeStatus = false;
			itr = itrBegin;
		}
		else
		{
			for (; itr != itrEnd; ++itr)
			{
				file << (*itr)->position.yposition << "\t";
			
			}
		}
		file << std::endl;
	}

	file << std::endl;
	file << "Cluster Instances" << std::endl;
	auto itrCluster = clustersX.begin();
	auto itrClusterBegin = clustersX.begin();
	auto itrClusterEnd = clustersX.end();
	int index = 0;
	for (; itrCluster != itrClusterEnd; ++itrCluster)
	{
		
		file << index << "\t" << (*itrCluster).second.size() << std::endl;
		index++;
	}
	file.close();
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
		pts->position.xposition = std::stof(dataX);
		if (pts->position.xposition > maxValueX)
		{
			maxValueX = pts->position.xposition;
		}
		if (pts->position.xposition < minValueX)
		{
			minValueX = pts->position.xposition;;
		}
		pts->position.yposition = std::stof(dataY);
		if (pts->position.yposition > maxValueY)
		{
			maxValueY = pts->position.yposition;
		}
		if (pts->position.yposition < minValueY)
		{
			minValueY = pts->position.yposition;;
		}
		points.push_back(pts);
	
	}
}

void KMean::initRandomClusters()
{
	srand(k);
	for (int i = 0; i < k; i++)
	{
		
		cluster* cls = new cluster();
		cls->clusterID = i;
		cls->position.xposition = rand() % (int)(maxValueX - minValueX) + minValueX;
		cls->position.yposition = rand() % (int)(maxValueY - minValueY) + minValueY;
		
		clustersData.push_back(cls);
	}
}

void KMean::processData()
{
	convertTheFileintoKMeanFormat(); // need to change the invoker loaction
	initRandomClusters();
	clustering();
}

void KMean::clustering()
{
	auto itrPoints        = points.begin();
	auto itrBeginPoints   = points.begin();
	auto itrEndPoints     = points.end();
	auto itrClusters      = clustersData.begin();
	auto itrBeginClusters = clustersData.begin();
	auto itrEndClusters   = clustersData.end();
	bool anythingChanged = true;
	
	int iterator = 0;
	while (anythingChanged && iterator<MAX_ITERATOR)
	{
		itrPoints = itrBeginPoints;
		for (; itrPoints != itrEndPoints; ++itrPoints)
		{
			float max = INT_MIN;
			int clusterID = -1;
			double minElement = static_cast<double>(INT_MAX);
			itrClusters = itrBeginClusters;
			for (; itrClusters != itrEndClusters; ++itrClusters)
			{
				auto tempDistance = distance((*itrClusters)->position, (*itrPoints)->position);
				if (minElement > tempDistance)
				{
					minElement = tempDistance;
					clusterID = (*itrClusters)->clusterID;
				}
			}

			(*itrPoints)->clusterGroupNum = clusterID;
			clustersX[clusterID].push_back((*itrPoints)->position.xposition);
			clustersY[clusterID].push_back((*itrPoints)->position.yposition);
		}
		recompileClusterPositions();
		if (!clusterPositionChanged())
		{
			anythingChanged = false;
		}
		else
		{
			clearClusters();
		}
		iterator++;
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
		auto vY = clustersY[i];
		/*clustersX[i].clear();
		clustersY[i].clear();*/
		auto sumX = std::accumulate(vX.begin(), vX.end(), 0.0);
		auto meanX = sumX / vX.size();

		
		auto sumY = std::accumulate(vY.begin(), vY.end(), 0.0);
		auto meanY = sumY / vY.size();
		if (vX.size() != 0)
		{
			clustersData[i]->prevPosition.xposition = clustersData[i]->position.xposition;
			clustersData[i]->position.xposition = static_cast<float>(meanX);
		}
		if (vY.size() != 0)
		{
			clustersData[i]->prevPosition.yposition = clustersData[i]->position.yposition;
			clustersData[i]->position.yposition = static_cast<float>(meanY);
		}
	}
}

bool KMean::clusterPositionChanged()
{
	auto itrBegin = clustersData.begin();
	auto itrEnd =clustersData.end();
	auto itr = itrBegin;
	bool valueChanged = true;
	for (; itr != itrEnd;++itr)
	{
		if ((*itr)->position.xposition == (*itr)->prevPosition.xposition && 
			(*itr)->position.yposition == (*itr)->prevPosition.yposition) //weirdest thing its working with float. I was prepared to optimized it but as its working out I didnt mess with it
		{
			valueChanged = false;
		}
	}
	return valueChanged;
}

void KMean::clearClusters()
{
	for (int i = 0; i < k; i++)
	{
		clustersX[i].clear();
		clustersY[i].clear();
	}
}

KMean::KMean()
{										  
	maxValueX = static_cast<float>(INT_MIN);
	maxValueY = static_cast<float>(INT_MIN);
	minValueX = static_cast<float>(INT_MAX);
	minValueY = static_cast<float>(INT_MAX);
}										  

KMean::~KMean()
{
}