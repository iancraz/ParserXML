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


#ifndef PARSEXML_H
#define PARSEXML_H
#include <expat.h>
#include <iostream>
#include <string>
#include <vector>

typedef struct
{
	std::string title;
	std::string pubDate;
}News_s;

typedef enum {WAITING,CHANNEL,NEWS,NEWS_TITLE, CHANNEL_TITLE, NEWS_PUB_DATE, FINISHED, NOT_RELEVANT_CH,NOT_RELEVANT_NEWS} State_t;

typedef struct
{
	std::vector<News_s> newsVector;
	State_t state;
	std::vector<char*> tagEnders;
	News_s currentNews;
}UserData_s;

class parseXML
{
public:
	parseXML(FILE * plainXMLTextFile = NULL, XML_Parser parser = NULL) ;
	~parseXML();
	void setParseXML(FILE * plainXMLTextFile = NULL, XML_Parser parser = NULL); //Funcion hecha para que la clase sea heredable
	bool parse();
	UserData_s * getData();
protected:
	UserData_s  * data;
	XML_Parser parser;
	FILE * plainXMLTextFile;
private:
	bool ready2Go;
};

#endif	//PARSEXML_H
