#include "precompiled.h"
#include "MathUtility.h"


MathUtility& MathUtility::instance()
{
	static MathUtility mu;
	return mu;
}

void MathUtility::pushDetailsForCalculation(float rating1, float rating2)
{
	user1.push_back(rating1);
	user2.push_back(rating2);
}

double MathUtility::calculateCosine()
{
	double x = std::accumulate(user1.begin(), user1.end(), 0.0,square());
	double y = std::accumulate(user2.begin(), user2.end(), 0.0,square());
	double dot = std::inner_product(user1.begin(), user1.end(), user2.begin(), 0.0);
	double cosine = dot / (x*y);
	return cosine;
}

void MathUtility::clear()
{
	user1.clear();
	user2.clear();
}

float MathUtility::operator()(const float x, const float y) const
{

	return x + y*y;
}

float MathUtility::minkowskiDistance(float val1, float val2, int r)
{
	return abs(val1 - val2);
}

float MathUtility::sumOfSquares(float x, float y)
{

	return x + y*y;
}

MathUtility::MathUtility()
{
}


MathUtility::~MathUtility()
{
	user1.clear();
	user2.clear();
}
