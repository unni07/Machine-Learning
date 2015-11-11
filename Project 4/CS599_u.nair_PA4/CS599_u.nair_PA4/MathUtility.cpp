#include "precompiled.h"
#include "MathUtility.h"


MathUtility& MathUtility::instance()
{
	static MathUtility mu;
	return mu;
}

float MathUtility::minkowskiDistance(float val1, float val2, int r)
{
	return abs(val1 - val2);
}

MathUtility::MathUtility()
{
}


MathUtility::~MathUtility()
{
}
