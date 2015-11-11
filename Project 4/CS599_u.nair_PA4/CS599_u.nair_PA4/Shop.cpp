#include "precompiled.h"
#include "Shop.h"
#include "FileReader.h"


Shop::Shop()
{
}


Shop::~Shop()
{
}

void Shop::initialize(std::string configFileName)
{
	auto& reader = FileReader::instance();
	reader.readFile(configFileName,0);
	auto rawFile = reader.returnRawDatabse();




	reader.clear();
}

void Shop::fetchDatabase(std::string databaseName)
{
	auto& reader = FileReader::instance();
	reader.readFile(databaseName, 0);
	auto rawFile = reader.returnRawDatabse();
}