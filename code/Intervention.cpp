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

vector<double> Intervention::getDelta() {
	return this->Delta;
}

vector<pair<int, vector<vector<pair<int, double>>>>> Intervention::getWorkload() {
	return this->workload;
}

vector<vector<pair<int, vector<double>>>> Intervention::getRisk() {
	return this->risk;
}

double Intervention::getInterId() {
	return this->interId;
}

void Intervention::setId(double id) {
	this->interId = id;
}

Intervention::Intervention(string vFile) {
	Parser I(vFile);

	this->tmax = Parser::getDoubleWithoutCom(I.getValues()[I.keyFind("tmax")]);
	this->Delta = I.toDbTable(I.getValues()[I.keyFind("Delta")]);
	this->workload = extractWorkLoad(I.getValues()[I.keyFind("workload")]);
	this->risk = extractRisk(I.getValues()[I.keyFind("risk")]);
}


vector<vector<pair<int, vector<double>>>>	Intervention::extractRisk(string vFile) {
	Parser I(vFile);
	vector<string> main = I.getMain();
	vector<string> value = I.getValues();
	vector<pair<int, vector<double>>> p;
	vector<vector<pair<int, vector<double>>>> val;

	for (int i = 0; i < value.size(); i++) {
		p = extractTr(value[i]);
		val.push_back(p);
	}

	return val;
}

vector<pair<int, vector<double>>> Intervention::extractTr(string vFile) {
	Parser I(vFile);
	vector<string> main = I.getMain();
	vector<string> value = I.getValues();
	vector<pair<int, vector<double>>> val;
	pair<int, vector<double>> p;

	for (int i = 0; i < value.size(); i++) {
		p.first = stoi(main[i]);
		p.second = Parser::toDbTable(value[i]);
		val.push_back(p);
	}

	return val;
}


vector<pair<int, vector<vector<pair<int, double>>>>> Intervention::extractWorkLoad(string vFile) {
	Parser I(vFile);
	vector<string> main = I.getMain();
	vector<string> value = I.getValues();
	vector<vector<pair<int, double>>> p;
	vector<pair<int, vector<vector<pair<int, double>>>>> val;
	vector<double> mainVal = Parser::strTabToDbTabWithoutFirstCharacther(main, '_', 1);
	
	for (int i = 0; i < value.size(); i++) {
		p = extractC(value[i]);
		val.push_back(make_pair(mainVal[i], p));
	}

	return val;

}

vector<vector<pair<int, double>>> Intervention::extractC(string vFile) {
	Parser I(vFile);
	vector<string> main = I.getMain();
	vector<string> value = I.getValues();
	vector<pair<int, double>> p;
	vector<vector<pair<int, double>>> val;

	for (int i = 0; i < value.size(); i++) {
		p = extractTstep(value[i]);
		val.push_back(p);
	}

	return val;

}

vector<pair<int, double>> Intervention::extractTstep(string vFile) {
	Parser I(vFile);
	vector<string> main = I.getMain();
	vector<string> value = I.getValues();
	pair<int, double> p;
	vector<pair<int, double>> val;

	for(int i = 0; i < value.size(); i++) {
		p.first = stoi(main[i]);
		p.second = stod(value[i]);
		val.push_back(p);
	}

	return val;
}



