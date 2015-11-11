#pragma once
class RecommenderSystem
{
public:
	static RecommenderSystem& instance();
private:
	RecommenderSystem();
	~RecommenderSystem();
};

