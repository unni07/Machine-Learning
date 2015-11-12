#include "precompiled.h"
#include "Shop.h"
#include "FileReader.h"
#include "CommodityFactory.h"
#include "UserFactory.h"
#include "User.h"
#include "Commodity.h"


Shop::Shop()
{
}


Shop::~Shop()
{
}

void Shop::initialize(std::string configFileName)
{
	auto& reader = FileReader::instance();
	reader.readFile(configFileName, 0);
	auto rawFile = reader.returnRawDatabse();
	auto itrBegin = rawFile.begin();
	auto itrEnd = rawFile.end();
	auto itr = itrBegin;
	size_t i = 0;
	std::string value;
	while (itr != itrEnd)
	{
		std::string line = *itr;
		auto pos = line.find(',');
		std::string title = line.substr(0, pos);
		bool doneReading = false;
		while (!doneReading)
		{
			if (pos == std::string::npos)
			{
				doneReading = true;
			}
			std::string val = line.substr(0, pos);
			if (title == "Movies" && val.size() != 0 && val != "Movies")
			{
				CommodityFactory::instance().getUser(val);
				movienames.push_back(val);
			}
			if (title == "Reviewer" && val.size() != 0 && val != "Reviewer")
			{
				UserFactory::instance().getUser(val);
				usernames.push_back(val);
			}
			line = line.substr(pos + 1);
			pos = line.find(',');
		}
		++itr;
	}
	reader.clear();
}

void Shop::fetchDatabase(std::string databaseName)
{
	auto& reader = FileReader::instance();
	reader.readFile(databaseName, 1);
	auto rawFile = reader.returnRawDatabse();
	auto itrBegin = rawFile.begin();
	auto itrEnd = rawFile.end();
	auto itr = itrBegin;
	std::string value;
	unsigned int index = 0;
	while (itr != itrEnd)
	{
		std::string line = *itr;
		auto pos = line.find(',');
		std::string title = line.substr(0, pos);
		line = line.substr(pos + 1);
		bool doneReading = false;
		while (!doneReading)
		{
			if (pos == std::string::npos)
			{
				doneReading = true;
			}
			std::string val = line.substr(0, pos);
			std::stringstream ss;
			ss.str(val);
			float rating;
			ss >> rating;

			auto reviewer = UserFactory::instance().getUser(title);
			reviewer->addRating(movienames[index],rating);

			auto movieEntity = CommodityFactory::instance().getUser(movienames[index]);
			movieEntity->adduser(reviewer, rating);

			line = line.substr(pos + 1);
			pos = line.find(',');
			index++;	
		}
		++itr;
		index = 0;
	}
	reader.clear();
}

void Shop::testData(std::string fileName)
{
	auto& reader = FileReader::instance();
	reader.readFile(fileName, 1);
	auto rawFile = reader.returnRawDatabse();
	auto itrBegin = rawFile.begin();
	auto itrEnd = rawFile.end();
	auto itr = itrBegin;
	size_t i = 0;
	std::string value;
	unsigned int index = 0;
	while (itr != itrEnd)
	{
		std::string line = *itr;
		auto pos = line.find(',');
		std::string title = line.substr(0, pos);
		line = line.substr(++pos);
		bool doneReading = false;
		while (!doneReading)
		{
			if (pos == std::string::npos)
			{
				doneReading = true;
			}
			std::string val = line.substr(0, pos);
			if (val.compare("?") != -1)
			{
				val = "0";
			}
			std::stringstream ss;
			ss.str(val);
			float rating;
			ss >> rating;

			auto reviewer = UserFactory::instance().getUser(title);
			reviewer->addRating(movienames[index], rating);

			auto movieEntity = CommodityFactory::instance().getUser(movienames[index]);
			movieEntity->adduser(reviewer, rating);

			line = line.substr(pos + 1);
			pos = line.find(',');
			index++;
		}
		++itr;
		index = 0;
	}
	reader.clear();
	
}