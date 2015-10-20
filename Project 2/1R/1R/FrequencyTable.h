#pragma once
#include <iostream>
#include <unordered_map>
class leaf
{
public:
	leaf(std::string);
	~leaf();
	//leaf();
	void addChild(std::string);
	int getCount();
	leaf * find(std::string);
	void operator++(int);
	std::vector<std::string> getListOfNames();
	//int getCount();
	void setCount(int);
	//::leaf operator++(int);
	//void node->add
	std::string getName();
private:
	std::string attributeName;
	std::unordered_map<std::string, leaf*> listofNode;
	int count;
	std::vector<std::string> listOfNames;
	//leaf * utilFind(std::string, std::unordered_map<std::string, leaf*>::iterator);
	//leaf * child;
};

class FrequencyTable
{
public:
	FrequencyTable(std::string name);
	FrequencyTable();
	~FrequencyTable();
	void addChild(std::string);
	void addChildTo(std::string, std::string);
	int getCount(std::string);
	void addOutcome(std::vector<std::string>);
	std::vector<std::string> getListOfNames();
	leaf * getChildof(std::string);
	std::string getName();
private:
	leaf * node;
};
