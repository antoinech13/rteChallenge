#include "Exclusions.h"
#include "Parser.h"

vector<pair<string, vector<double>>> Exclusions::getData() {
	return this->data;
}

Exclusions::Exclusions(string vFile) {
	this->data = extractData(vFile);
}

vector<pair<string, vector<double>>> Exclusions::extractData(string vFile) {
	Parser I(vFile);
	vector<string> main = I.getMain();
	vector<string> values = I.getValues();
	pair<string, vector<double>> p;
	vector<string> tab;
	vector<int> tabInter;
	vector<pair<string, vector<double>>> val;

	for (int i = 0; i < values.size(); i++) {
		tab = Parser::toStringTable(values[i]);
		p.first = tab[tab.size()-1];
		tab.pop_back();
		p.second = Parser::strTabToDbTabWithoutFirstCharacther(tab, '_', 1);
		val.push_back(p);
	}

	return val;

}
