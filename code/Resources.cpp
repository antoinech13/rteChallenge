#include <map>
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include "Resources.h"
#include "Parser.h"

vector < pair<int, map<string, vector<double>>>> Resources::getData() {
	return this->data;
}

Resources::Resources(string vFile) {
	this->data = extractData(vFile);	
}

vector<pair<int, map<string, vector<double>>>> Resources::extractData(string vFile) {
	Parser I(vFile);
	vector<string> main = I.getMain();
	vector<string> values = I.getValues();
	pair<int, map<string, vector<double>>> p;
	vector<pair<int, map<string, vector<double>>>> val;

	vector<double> mainVal = Parser::strTabToDbTabWithoutFirstCharacther(main, '_', 1);


	for (int i = 0; i < values.size(); i++) {
		p.first = mainVal[i];
		p.second = extractMap(values[i]);
		val.push_back(p);
	}

	return val;
}

map<string, vector<double>> Resources::extractMap(string vFile) {
	Parser I(vFile);
	vector<string> main = I.getMain();
	vector<string> values = I.getValues();
	map<string, vector<double>> val;

	for (int i = 0; i < values.size(); i++) {
		val[main[i]] = Parser::toDbTable(values[i]);
	}
	return val;
}