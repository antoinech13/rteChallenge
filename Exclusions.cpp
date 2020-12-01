#include "Exclusions.h"
#include "Parser.h"

vector<pair<string, vector<string>>> Exclusions::getData() {
	return this->data;
}

Exclusions::Exclusions(string vFile) {
	this->data = extractData(vFile);
}

vector<pair<string, vector<string>>> Exclusions::extractData(string vFile) {
	Parser I(vFile);
	vector<string> main = I.getMain();
	vector<string> values = I.getValues();
	pair<string, vector<string>> p;
	vector<pair<string, vector<string>>> val;

	for (int i = 0; i < values.size(); i++) {
		p.first = main[i];
		p.second = Parser::toStringTable(values[i]);
		val.push_back(p);
	}

	return val;

}
