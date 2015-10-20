#include "OneR.h"


OneR::OneR() 
{

}


OneR::~OneR()
{
}

void OneR::readMetaData(std::string filePath)
{
	reader.readFile(filePath, 0);
	setMetadata();
	reader.clear();
}

void OneR::setMetadata()
{
	auto rawData = reader.returnRawDatabse();
	auto iterator = rawData.begin();
	auto end = rawData.end();
	
	std::string line = *iterator;
	line = line + ',';
	auto length = line.size();
	std::string value="";
	
	for (unsigned int i = 0; i < length;++i)
	{
		if (line[i]!=',' )
		{
			value = value + line[i];
		}
		else
		{
			auto it =metaData.find(value);
			if (it==metaData.end())
			{
				metaData[value];
				metaData[value].reserve(10);
				database[value];
				database[value].reserve(10);
				testDatabase[value];
				testDatabase[value].reserve(10);
				frequencyTable.insert(std::make_pair(value, new FrequencyTable(value)));
				value.clear();
			}
		}
	}
	line.clear();
	++iterator;
	auto it = metaData.begin();
	for (; iterator != end; ++iterator)
	{
		line = *iterator;
		line = line + ',';
		length = line.size();
		value = "";
		for (unsigned int i = 0; i < length; ++i)
		{
			if (line[i] != ',')
			{
				value = value + line[i];
			}
			else 
			{
				if (!value.empty())
				{
					auto vec = metaData.find(it->first);
					auto data = frequencyTable.find(it->first);
					data->second->addChild(value);
					
					vec->second.push_back(value);

					value.clear();
				}
				it++;
			}
		}
		it = metaData.begin();
	}
	int a = 10;
}


void OneR::readFile(std::string filePath)
{
	reader.readFile(filePath, 1);
	setDatabase();
	reader.clear();
}

void OneR::setDatabase()
{
	auto rawData = reader.returnRawDatabse();
	auto iterator = rawData.begin();
	auto end = rawData.end();

	std::string line = *iterator;
	line = line + ',';
	auto length = line.size();
	std::string value = "";

	auto it = database.begin();
	for (; iterator != end; ++iterator)
	{
		line = *iterator;
		line = line + ',';
		length = line.size();
		value = "";
		for (unsigned int i = 0; i < length; ++i)
		{
			if (line[i] != ',')
			{
				value = value + line[i];
			}
			else if (!value.empty())
			{
				auto vec = database.find(it->first);
				it++;

				vec->second.push_back(value);
				value.clear();
			}
		}
		it = database.begin();
	}
}

void OneR::process(std::string outcome)
{
	setVerdict(outcome);
	auto size = metaData.size();

	auto itrDatabase = database.begin();
	auto itrendDatabase = database.end();
	itrendDatabase--;
	
	auto outcomeAttribute = database.find(outcome)->second;
	for (; itrDatabase != itrendDatabase; ++itrDatabase)
	{
		auto attribute = itrDatabase;
		auto col = attribute->second;
		auto sizeofCol = col.size();
		unsigned int i = 0;
		while (i < sizeofCol)
		{
			std::string name = attribute->first;
			

			FrequencyTable *tempTable = frequencyTable[attribute->first];
			std::string name1 = col[i];
			leaf * momLeaf = tempTable->getChildof(name1);
			std::string name2 = outcomeAttribute[i];
			leaf * childLeaf = momLeaf->find(name2);
			
			(*childLeaf)++;
			
			i++;
		}
	}
	getOneRRule(outcome);
}

void OneR::setVerdict(std::string outcome)
{
	auto col = metaData.find(outcome);
	auto colSize = col->second.size();
	auto itrMetaEnd = metaData.end();
	//itrEnd--; //need to fix this
	if (col != itrMetaEnd)
	{
		auto itrBegin = frequencyTable.begin();
		auto itrEnd = frequencyTable.end();
		auto iterator = itrBegin;

		auto metaIterator = metaData.begin();
		while (iterator != itrEnd)
		{
			auto table = iterator->second;
			auto vecNames = table->getListOfNames();
			auto size = vecNames.size();
			for (unsigned int i = 0; i < size;i++)
			{
				for (unsigned int j = 0; j < colSize;j++)
				table->addChildTo(vecNames[i], col->second[j]);
			}
		
			iterator++;
		}

	}
}

void OneR::getOneRRule(std::string outcome)
{
	auto size = frequencyTable.size();
	auto itrBegin = frequencyTable.begin();
	auto iterator = itrBegin;
	auto itrEnd = frequencyTable.end();
	itrEnd--;
	auto itrMetaBegin = metaData.begin();
	auto itrMetaEnd = metaData.end();
	itrMetaEnd--;
	auto iteratorMeta = itrMetaBegin;
	auto result = metaData.find(outcome);
	auto sizeVectorResult = result->second.size();
	std::vector<float> errorList;
	float errorMax = static_cast<float>(INT_MAX);
	float totalerror = 0.0f;
	int error = 0;
	auto itr =rule.end();
	while (iterator != itrEnd)
	{
		auto attribute = frequencyTable.find(iteratorMeta->first);
		auto size = attribute->second->getListOfNames().size();
		auto vecList = attribute->second->getListOfNames();
		int total = 0;
		int max = INT_MIN;
		int min = 0;
		int totalMin = 0;
		for (unsigned int i = 0; i < size; i++)
		{
			auto child = attribute->second->getChildof(vecList[i]);
			max = INT_MIN;
			min = 0;
			std::string status;
			std::string colName;
			//int totalCount = 0;
			total = 0;
			for (unsigned int j = 0; j < sizeVectorResult; j++)
			{
				auto child2 = child->find(result->second[j]);
				colName = child->getName();
				int tempMax = child2->getCount();
				total = total + tempMax;
				if (max < tempMax)
				{
					max = tempMax;
					status = child2->getName();
					
					min = min + (total - max);
				}
				
				
			}

			min = total - max;
			totalMin = totalMin + min;
			
			
				if (rule.find(attribute->first) == itr)
					rule[attribute->first].insert(std::make_pair(colName, status));
				else
				{
					
					rule.find(attribute->first)->second.insert(std::make_pair(colName, status));
				}
				
		}
	
		auto sizeofDatabase = database.find(attribute->first)->second.size();
		totalerror = totalMin / static_cast<float>(sizeofDatabase);
		if (totalerror<errorMax)
		{
			oneRule.clear();
			auto attr = rule.find(attribute->first);
			oneRule.insert(std::make_pair(attribute->first, rule.find(attribute->first)->second));
		
			errorMax = totalerror;
		}
		
		iteratorMeta++;
		iterator++;
	}
	int i = 10;
	i++;
	i = 10;
}

void OneR::test(std::string filePath)
{
	reader.readFile(filePath,1);
	setUpTestData();
}

void OneR::setUpTestData()
{
	auto testInput = reader.returnRawDatabse();
	auto rawData = reader.returnRawDatabse();
	auto iterator = rawData.begin();
	auto end = rawData.end();

	std::string line = *iterator;
	line = line + ',';
	auto length = line.size();
	std::string value = "";

	auto it = testDatabase.begin();
	for (; iterator != end; ++iterator)
	{
		line = *iterator;
		line = line + ',';
		length = line.size();
		value = "";
		for (unsigned int i = 0; i < length; ++i)
		{
			if (line[i] != ',')
			{
				value = value + line[i];
			}
			else if (!value.empty())
			{
				auto vec = testDatabase.find(it->first);
				it++;

				vec->second.push_back(value);
				value.clear();
			}
		}
		it = testDatabase.begin();
	}

}

void OneR::writeResultToFile(std::ofstream& output)
{
	auto data = oneRule.begin();
	auto attribute = data->first;
	auto vec = testDatabase.find(attribute);
	auto vecSize = vec->second.size();
	for (unsigned int i = 0; i < vecSize; i++)
	{
		auto val = vec->second[i];
		auto res = data->second.find(val);
		output << res->second << "\n";
	}
	auto val = vec->second.begin();
	auto res = data->second.find(*val);
	int i = 10;
	i++;
}

void OneR::process(std::string outcome,std::vector<std::string> data)
{
	setVerdict(outcome);
	auto size = metaData.size();
	auto itrDatabase = database.begin();
	auto itrendDatabase = database.end();
	itrendDatabase--;
	
	auto outcomeAttribute = data;
	auto sizeVector = data.size();
	for (; itrDatabase != itrendDatabase; ++itrDatabase)
	{
		auto attribute = itrDatabase;
		auto col = attribute->second;
		auto sizeofCol = col.size();
		unsigned int i = 0;
		unsigned int j = 0;
		while (i < sizeofCol)
		{
			std::string name = attribute->first;
			

			FrequencyTable *tempTable = frequencyTable[attribute->first];
			std::string name1 = col[i];
			leaf * momLeaf = tempTable->getChildof(name1);
			std::string name2;
			if (j < sizeVector)
				name2 = outcomeAttribute[j];
			else
			{
				j = 0;
				name2 = outcomeAttribute[j];
			}
			leaf * childLeaf = momLeaf->find(name2);
			
			(*childLeaf)++;
		
			i++;
			j++;
		}
	}
	getOneRRule(outcome);
}