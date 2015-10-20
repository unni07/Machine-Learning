#include "KMean.h"

int main()
{
	KMean& obj = KMean::getInstance();
	obj.readFile("Tshirt Data.csv",3);
	obj.printOutputwithFileName("Output1");
	
}