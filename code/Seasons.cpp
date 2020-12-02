#include "Seasons.h"
#include "Parser.h"

map<string, vector<int>> Seasons::getData() {
	return this->data;
}

Seasons::Seasons(string vFile) {
	this->data = extractData(vFile);
}

map<string, vector<int>> Seasons::extractData(string vFile) {
	Parser I(vFile);
	vector<string> main = I.getMain();
	vector<string> values = I.getValues();
	pair<string, vector<int>> p;
	map<string, vector<int>>  val;

	for (int i = 0; i < values.size(); i++) {
		val[main[i]] = Parser::toIntTable(values[i]);
	}
	return val;
}