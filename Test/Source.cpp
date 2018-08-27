/*
Copyright 2018 Ian Cruz Diaz

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#include "../Test/parseXML.h"
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
