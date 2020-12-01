#include "Seasons.h"
#include "Parser.h"

vector<pair<string, vector<int>>> Seasons::getData() {
	return this->data;
}

Seasons::Seasons(string vFile) {
	this->data = extractData(vFile);
}

vector<pair<string, vector<int>>> Seasons::extractData(string vFile) {
	Parser I(vFile);
	vector<string> main = I.getMain();
	vector<string> values = I.getValues();
	pair<string, vector<int>> p;
	vector<pair<string, vector<int>>>  val;

	for (int i = 0; i < values.size(); i++) {
		p.first = main[i];
		p.second = Parser::toIntTable(values[i]);
		val.push_back(p);
	}
	return val;
}