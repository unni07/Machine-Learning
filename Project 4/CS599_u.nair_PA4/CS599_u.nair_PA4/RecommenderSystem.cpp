#include "precompiled.h"
#include "RecommenderSystem.h"


RecommenderSystem& RecommenderSystem::instance()
{
	static RecommenderSystem rs;
	return rs;
}

RecommenderSystem::RecommenderSystem()
{
}


RecommenderSystem::~RecommenderSystem()
{
}
