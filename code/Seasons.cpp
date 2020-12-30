#include "Seasons.h"
#include "Parser.h"

map<string, vector<double>> Seasons::getData() {
	return this->data;
}

Seasons::Seasons(string vFile) {
	this->data = extractData(vFile);
}

map<string, vector<double>> Seasons::extractData(string vFile) {
	Parser I(vFile);
	vector<string> main = I.getMain();
	vector<string> values = I.getValues();
	pair<string, vector<double>> p;
	map<string, vector<double>>  val;

	for (int i = 0; i < values.size(); i++) {
		if(values[i].size() > 2)
			val[main[i]] = Parser::toDbTable(values[i]);
	}
	return val;
}