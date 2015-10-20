#include "FileReader.h"


FileReader::FileReader()
{
}


FileReader::~FileReader()
{
}

void FileReader::readFile(std::string filePath, int index)
{

	std::ifstream file(filePath);
	std::string line;
	int tempIndex = index;
	while (tempIndex>0)
	{
		std::getline(file, line);
		tempIndex--;
	}
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			if (line[0] == omitMe)
			{
				//ignore
			}
			else
			{
				inputs.push_back(line);
			}
		}
		file.close();
	}
	else
	{
		std::cout << "Failed to load file";
	}
}

lines FileReader::returnRawDatabse()
{
	return inputs;
}

void FileReader::setValueToAvoidLine(char value)
{
	omitMe = value;
}

void FileReader::setOmitValue(char value)
{
	omitMe = value;
}

void FileReader::clear()
{
	inputs.clear();
}

