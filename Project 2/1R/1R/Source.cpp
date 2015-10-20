#include <iostream>
#include "FileReader.h"
#include "oneR.h"
#include <fstream>
int main()
{
	OneR obj1,obj2,obj3;
	
	obj1.readMetaData("WeatherMetaData.csv");
	obj1.readFile("WeatherCSV.csv");
	obj1.process("Play");
	obj1.test("WeatherTestData.csv");
	std::ofstream output;

	output.open("output.txt");
	output << "Test Number 1 \n";

	obj1.writeResultToFile(output);
	output << "\n" << "\n";
	output << "Test Number 2 \n";

	obj2.readMetaData("VotingDataMeta.csv");
	obj2.readFile("Voting Data.csv");
	obj2.process("Vote");
	obj2.test("VotingTestData.csv");
	obj2.writeResultToFile(output);
	//output << "Test Number "
	output << "\n" << "\n";
	output << "Test Number 3 \n";

	obj3.readMetaData("AnimalMeta.csv");
	obj3.readFile("AnimalData.csv");
	std::vector<std::string> data;
	data.push_back("fish");
	data.push_back("mammal");
	obj3.process("type",data);
	obj3.test("AnimalTestData.csv");
	obj3.writeResultToFile(output);

	output.close();
	return 0;
}