#pragma once
#include "positionVector.h"

/*Represents the cluster*/
class cluster
{
public:
	positionVector position;
	int clusterID;
	cluster();
	~cluster();
};

