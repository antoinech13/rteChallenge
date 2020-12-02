#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include "Intervention.h"
#include "Parser.h"

using namespace std;


int Intervention::getTmax() {
	return this->tmax;
}

vector<int> Intervention::getDelta() {
	return this->Delta;
}

vector<pair<int, vector<vector<pair<int, int>>>>> Intervention::getWorkload() {
	return this->workload;
}

vector<vector<pair<int, vector<int>>>> Intervention::getRisk() {
	return this->risk;
}


Intervention::Intervention(string vFile) {
	Parser I(vFile);
	this->tmax = stoi(I.getValues()[I.keyFind("tmax")]);
	this->Delta = I.toIntTable(I.getValues()[I.keyFind("Delta")]);
	this->workload = extractWorkLoad(I.getValues()[I.keyFind("workload")]);
	this->risk = extractRisk(I.getValues()[I.keyFind("risk")]);
}


vector<vector<pair<int, vector<int>>>>	Intervention::extractRisk(string vFile) {
	Parser I(vFile);
	vector<string> main = I.getMain();
	vector<string> value = I.getValues();
	vector<pair<int, vector<int>>> p;
	vector<vector<pair<int, vector<int>>>> val;

	for (int i = 0; i < value.size(); i++) {
		p = extractTr(value[i]);
		val.push_back(p);
	}

	return val;
}

vector<pair<int, vector<int>>> Intervention::extractTr(string vFile) {
	Parser I(vFile);
	vector<string> main = I.getMain();
	vector<string> value = I.getValues();
	vector<pair<int, vector<int>>> val;
	pair<int, vector<int>> p;

	for (int i = 0; i < value.size(); i++) {
		p.first = stoi(main[i]);
		p.second = Parser::toIntTable(value[i]);
		val.push_back(p);
	}

	return val;
}


vector<pair<int, vector<vector<pair<int, int>>>>> Intervention::extractWorkLoad(string vFile) {
	Parser I(vFile);
	vector<string> main = I.getMain();
	vector<string> value = I.getValues();
	vector<vector<pair<int, int>>> p;
	vector<pair<int, vector<vector<pair<int, int>>>>> val;

	for (int i = 0; i < value.size(); i++) {
		p = extractC(value[i]);
		val.push_back(make_pair(stoi(main[i].erase(0))-1,p));
	}

	return val;

}

vector<vector<pair<int, int>>> Intervention::extractC(string vFile) {
	Parser I(vFile);
	vector<string> main = I.getMain();
	vector<string> value = I.getValues();
	vector<pair<int, int>> p;
	vector<vector<pair<int, int>>> val;

	for (int i = 0; i < value.size(); i++) {
		p = extractTstep(value[i]);
		val.push_back(p);
	}

	return val;

}

vector<pair<int, int>> Intervention::extractTstep(string vFile) {
	Parser I(vFile);
	vector<string> main = I.getMain();
	vector<string> value = I.getValues();
	pair<int, int> p;
	vector<pair<int, int>> val;

	for(int i = 0; i < value.size(); i++) {
		p.first = stoi(main[i]);
		p.second = stoi(value[i]);
		val.push_back(p);
	}

	return val;
}



