#pragma once

#include <map>
#include <vector>
#include "FileReader.h"
#include <unordered_map>
#include "FrequencyTable.h"
#include <fstream>
typedef std::unordered_map<std::string, std::vector<std::string>> mapVectors;
typedef std::map<std::string, std::string> oneRule;
//typedef std::unordered_map<std::string, int> frequencyTable;
typedef std::unordered_map<std::string, FrequencyTable*> mapFrequency;
typedef std::unordered_map<std::string, std::unordered_map<std::string, std::string>> result;

class OneR
{
public:
	OneR();
	~OneR();
	void readMetaData(std::string);
	void readFile(std::string);
	void process(std::string, std::vector<std::string>);
	void process(std::string);
	void test(std::string);
	void setUpTestData();
	void writeResultToFile(std::ofstream& output);
private:
	void setMetadata();
	void setDatabase();
	void setVerdict(std::string);
	void getOneRRule(std::string);
	mapVectors metaData;
	mapVectors database;
	mapVectors testDatabase;
	FileReader reader;
	result rule;
	result oneRule;
	mapFrequency frequencyTable;
};

