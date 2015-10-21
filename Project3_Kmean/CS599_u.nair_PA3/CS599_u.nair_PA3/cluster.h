#pragma once
#include "positionVector.h"

/*Represents the cluster*/
class cluster
{
public:
	positionVector position;
	positionVector prevPosition;
	int clusterID;
	cluster();
	~cluster();
};

