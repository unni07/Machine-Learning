#include "precompiled.h"
#include "MathUtility.h"


MathUtility& MathUtility::instance()
{
	static MathUtility mu;
	return mu;
}

MathUtility::MathUtility()
{
}


MathUtility::~MathUtility()
{
}
