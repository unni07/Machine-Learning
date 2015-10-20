#include "FrequencyTable.h"


FrequencyTable::FrequencyTable(std::string name) : node(new leaf(name))
{
	//node = new leaf(name);
}

FrequencyTable::FrequencyTable()
{
	node = NULL;
}


FrequencyTable::~FrequencyTable()
{

}

leaf::leaf(std::string name) :attributeName(name), count(0)
{
	//attributeName = name;
	//listofNode[name];
}

leaf::~leaf()
{
	/*auto size = listofNode.size();
	auto iterator = listofNode.begin();
	unsigned int itr = 0;
	while (itr>size)
	{
		auto tempLeaf = iterator->second;
		if (tempLeaf)
		{
			delete tempLeaf;
		}
		itr++;
	}*/
}

leaf* leaf::find(std::string name)
{
	auto itr = listofNode.begin();
	auto reqItr = listofNode.find(name);
	auto itrEnd = listofNode.end();
	if (reqItr == itrEnd)
	{
		return NULL;
	}
	else
		return reqItr->second;
	//return utilFind(name, itr);
}

//leaf* leaf::utilFind(std::string name, std::unordered_map<std::string, leaf*>::iterator itr)
//{
//	auto childLeaf = 
//}

void leaf::addChild(std::string name)
{
	auto data = listofNode.find(name);
	auto itrEnd = listofNode.end();
	if (data == itrEnd)
	{
		//data->second = new leaf(name);
		listofNode.insert(std::make_pair(name, new leaf(name)));
		listOfNames.push_back(name);
	}
	/*else
	{
		listofNode.insert(std::make_pair(name, new leaf(name)));
	}*/
}

int leaf::getCount()
{
	return count;
}

void FrequencyTable::addChild(std::string name)
{
	if (node)
		node->addChild(name);
	else
		node = new leaf(name);
}

int FrequencyTable::getCount(std::string name)
{
	auto data = node->find(name);
	return data->getCount();
}

void leaf::operator++(int)
{
	count++;
}

void FrequencyTable::addOutcome(std::vector<std::string> vec)
{
	//node->addOutcome(vec);
}

void FrequencyTable::addChildTo(std::string childName, std::string newChild)
{
	auto childFound = node->find(childName);
	childFound->addChild(newChild);

}

std::vector<std::string> FrequencyTable::getListOfNames()
{
	return node->getListOfNames();
}

std::vector<std::string> leaf::getListOfNames()
{
	return listOfNames;
}

leaf * FrequencyTable::getChildof(std::string name)
{
	return node->find(name);
}

void leaf::setCount(int num)
{
	count = num;
}

std::string FrequencyTable::getName()
{
	return node->getName();
}

std::string leaf::getName()
{
	return attributeName;
}