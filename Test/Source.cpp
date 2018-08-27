#include "parseXML.h"
#include <iostream>
#include <cstdio>

using namespace std;

int main(void)
{
	FILE * myFile;
	myFile = fopen("XMLX_RSS.txt", "r");
	parseXML myXML(myFile);
	if (!myXML.parse())
	{
		cout << "Error al leer el XML" << endl;
		getchar();
		return -1;
	}
	UserData_s myData = *myXML.getData();
	cout << myData.newsVector[0].title << myData.newsVector[0].pubDate << endl;
	getchar();
	return 0;
}