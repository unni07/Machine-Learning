#pragma once
#include "FileReader.h"
#include "cluster.h"
#include "Points.h"
#include "positionVector.h"

typedef std::map<std::string, std::vector<std::string>> virtualFile;
typedef std::vector<std::string> filter;

class KMean
{
public:
	/*Guaranteed to have single instance*/
	static KMean& getInstance();
	void readFile(std::string,int);
	/*this will output the result into a text file*/
	void printOutputwithFileName(std::string);
	
private:
	/*reading lines from the file and saving it in vector of srings. Each line an object of the vector*/
	lines rawFromat;
	/*Number of clusters*/
	int k;
	/*this fucntion will read the file in raw format and save it in "rawFormat"*/
	void getRawFormat(std::string);
	/*collection of vectors*/
	std::vector<cluster*>clustersData;
	/*collection of points*/
	std::vector<Points*>points;
	/*reader object to read files*/
	FileReader reader;
	/*Converting into required data format*/
	void convertTheFileintoKMeanFormat();
	/*initialize clusters*/
	void initRandomClusters();
	/*Virtual file to save the content of the file into a readable file format*/
	virtualFile file;
	/*Process and convert data into Kmean format*/
	void processData();
	/*once all data is obtained. Begin Clustering*/
	void clustering();
	lines filter;
	/*to hold cluster and cluster data*/
	std::map<int, std::vector<int>> clustersX;
	std::map<int, std::vector<int>> clustersY;
	//Max Value
	int maxValueX;
	int maxValueY;
	/*return distance*/
	double distance(positionVector,positionVector);
	/*Re compile cluster positions*/
	void recompileClusterPositions();
	KMean();
	~KMean();
};

