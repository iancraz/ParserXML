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

typedef enum {WAITING, IN_CHANNEL,IN_NEWS,IN_NEWS_TITLE, CHANNEL_TITLE, NEWS_PUB_DATE, FINISHED, NOT_RELEVANT_CH,NOT_RELEVANT_NEWS} State_t;

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