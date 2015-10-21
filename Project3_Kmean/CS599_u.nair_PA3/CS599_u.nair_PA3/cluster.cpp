#include "cluster.h"


cluster::cluster()
{
	position.xposition = 0;
	position.yposition = 0;
	prevPosition.xposition = -1.0f;
	prevPosition.yposition = -1.0f;
	clusterID = -1;
}


cluster::~cluster()
{
}
