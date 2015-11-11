#pragma once
class MathUtility
{
public:
	static MathUtility& instance();
	float minkowskiDistance(float val1 , float val2, int r);
private:
	MathUtility();
	~MathUtility();
};

