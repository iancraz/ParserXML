#include "parseXML.h"
#define SIZE	100000
using namespace std;

void startTagHandler(void *userData, const XML_Char *name, const XML_Char **atts);
void endTagHandler(void *userData,const XML_Char *name);
void dataHandler(void *userData, const XML_Char *s, int len);

parseXML::parseXML(FILE * plainXMLTextFile, XML_Parser parser)
{
	setParseXML(plainXMLTextFile,parser);
	return;
}

parseXML::~parseXML()
{
	if(parser)
		XML_ParserFree(parser);
	return;
}

void parseXML::setParseXML(FILE * plainXMLTextFile, XML_Parser parser)
{
	if (plainXMLTextFile == NULL)
		ready2Go = false;
	else
		ready2Go = true;
	if(parser == NULL)
		parser = XML_ParserCreate(NULL);
	this->parser = parser;
	this->plainXMLTextFile = plainXMLTextFile;
	data = NULL;
	if (ready2Go)
	{
		this->data = new UserData_s;
		data->state = WAITING;
		XML_SetUserData(this->parser, this->data);
		XML_SetElementHandler(this->parser, &startTagHandler, &endTagHandler);
		XML_SetCharacterDataHandler(this->parser, &dataHandler);
	}
	return;
}

UserData_s * parseXML::getData()
{
	return data;
}

bool parseXML::parse()
{
	if (!ready2Go)
		return false;
	char buffer[SIZE];
	int exit = false;
	while (!exit)
	{
		int amountRead = fread(buffer, 1, SIZE, plainXMLTextFile);
		amountRead < SIZE ? exit = true : exit = false;
		if (XML_Parse(parser, buffer, amountRead, exit) == XML_STATUS_ERROR)
			return false;
	}
	return true;
}

void startTagHandler(void *userData,const XML_Char *name,const XML_Char **atts)
{
	UserData_s * data = (UserData_s*)userData;
	switch (data->state)
	{
	case WAITING:
		if (strcmp(name, "channel") == 0)
		{
			data->state = CHANNEL;
			data->tagEnders.push_back((char *)name);
		}
		break;
	case CHANNEL:
		data->tagEnders.push_back((char *)name);
		if (strcmp(name, "item") == 0)
		{
			data->state = NEWS;
			data->currentNews;
		}
		else if (strcmp(name, "title") == 0)
			data->state = CHANNEL_TITLE;
		else 
			data->state = NOT_RELEVANT_CH;
		break;
	case NEWS:
		data->tagEnders.push_back((char *)name);
		if (strcmp(name, "title") == 0) {
			data->state = NEWS_TITLE;
		}
		else if (strcmp(name, "pubDate") == 0) {
			data->state = NEWS_PUB_DATE;
		}
		else
			data->state = NOT_RELEVANT_NEWS;
		break;
	default:
		break;
	}
	return;
}

void endTagHandler(void *userData,const XML_Char *name)
{
	UserData_s * data = (UserData_s*)userData;
	if (data->state == FINISHED)
		return;
	if (strcmp(data->tagEnders[data->tagEnders.size() - 1], name) == 0)
	{
		switch (data->state) {
		case CHANNEL:
			data->tagEnders.pop_back();
			data->state = FINISHED;
			break;
		case NEWS:
			data->newsVector.push_back(data->currentNews);
			data->tagEnders.pop_back();
			data->state = CHANNEL;
			break;
		case CHANNEL_TITLE:
		case NOT_RELEVANT_CH:
			data->tagEnders.pop_back();
			data->state = CHANNEL;
			break;
		case NEWS_TITLE:
		case NEWS_PUB_DATE:
		case NOT_RELEVANT_NEWS:
			data->tagEnders.pop_back();
			data->state = NEWS;
			break;
		default:
			break;
		}
	}
	return;
}

void dataHandler(void *userData,const XML_Char *s, int len)
{
	UserData_s * data = (UserData_s*)userData;
	char * received = new char[len+1];
	for (int i = 0; i < len; i++)
		received[i] = s[i];
	received[len] = '\0';
	switch (data->state) {
	case NEWS_TITLE:
		data->currentNews.title = received;
		break;
	case NEWS_PUB_DATE:
		data->currentNews.pubDate = received;
		break;
	default:
		break;
	}
	delete received;
	return;
}