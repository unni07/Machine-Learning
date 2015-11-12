#pragma once
class MathUtility
{
public:
	static MathUtility& instance();
	void pushDetailsForCalculation(float user1, float user2);
	double calculateCosine();
	void clear();
	float operator()(const float Left, const float Right) const;
private:
	MathUtility();
	~MathUtility();
	std::vector<float> user1;
	std::vector<float> user2;
	float minkowskiDistance(float val1, float val2, int r);
	float sumOfSquares(float x, float y);
};

struct square
{
	double operator()(const double x, const double y) const
	{
		return x + y*y;
	}
};