#include <map>
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include "Resources.h"
#include "Parser.h"

vector < pair<int, map<string, vector<int>>>> Resources::getData() {
	return this->data;
}

Resources::Resources(string vFile) {
	this->data = extractData(vFile);	
}

vector<pair<int, map<string, vector<int>>>> Resources::extractData(string vFile) {
	Parser I(vFile);
	vector<string> main = I.getMain();
	vector<string> values = I.getValues();
	pair<int, map<string, vector<int>>> p;
	vector<pair<int, map<string, vector<int>>>> val;

	for (int i = 0; i < values.size(); i++) {
		p.first = stoi(main[i].erase(0,1))-1;
		p.second = extractMap(values[i]);
		val.push_back(p);
	}

	return val;
}

map<string, vector<int>> Resources::extractMap(string vFile) {
	Parser I(vFile);
	vector<string> main = I.getMain();
	vector<string> values = I.getValues();
	vector<int> p;
	map<string, vector<int>> val;

	for (int i = 0; i < values.size(); i++) {
		val[main[i]] = Parser::toIntTable(values[i]);
	}
	return val;
}