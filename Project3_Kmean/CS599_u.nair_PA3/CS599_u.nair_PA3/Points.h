#pragma once
#include "positionVector.h"
/*a class to hold the data in X-Y style*/
class Points
{
public:
	positionVector position;
	int clusterGroupNum;
	Points();
	~Points();
};

