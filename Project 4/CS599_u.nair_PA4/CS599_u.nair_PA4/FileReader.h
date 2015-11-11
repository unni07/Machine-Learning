#pragma once
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
//typedef std::map<std::string, std::vector<std::string>> file;
typedef std::vector<std::string> lines;

class FileReader
{
public:	
	//functions
	void readFile(std::string, int);										//function to read file
	lines returnRawDatabse();												//function to return databse created
	void setValueToAvoidLine(char);											//set starting character of line needed to omit
	void setOmitValue(char);
	void clear();
private:
	//file database;														//database read from file
	char omitMe;
	//character needed to be ommited
	lines inputs;
	//file database; 
	FileReader();
	~FileReader();



};

