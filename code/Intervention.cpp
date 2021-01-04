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

vector<pair<int, vector<pair<int, vector<pair<int, double>>>>>> Intervention::getWorkload() {
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

string Intervention::getName() {
	return this->name;
}

void Intervention::setName(string name) {
	this->name = name;
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


vector<pair<int, vector<pair<int, vector<pair<int, double>>>>>> Intervention::extractWorkLoad(string vFile) {
	Parser I(vFile);
	vector<string> main = I.getMain();
	vector<string> value = I.getValues();
	vector<pair<int, vector<pair<int, double>>>> p;
	vector<pair<int, vector<pair<int, vector<pair<int, double>>>>>> val;
	//vector<double> mainVal = Parser::strTabToDbTabWithoutFirstCharacther(main, '_', 1);
	vector<double> mainVal = Parser::extractDbVecWords(main);
	mainVal = Parser::substract(mainVal, 1);
	for (int i = 0; i < value.size(); i++) {
		p = extractC(value[i]);
		val.push_back(make_pair(mainVal[i], p));
	}

	return val;

}

vector<pair<int, vector<pair<int, double>>>> Intervention::extractC(string vFile) {
	Parser I(vFile);
	vector<string> main = I.getMain();
	vector<string> value = I.getValues();
	vector<pair<int, double>> p;
	vector<pair<int, vector<pair<int, double>>>> val;

	for (int i = 0; i < value.size(); i++) {
		p = extractTstep(value[i]);
		val.push_back(make_pair(Parser::getDoubleWithoutCom(main[i]), p));
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
		p.first = Parser::getDoubleWithoutCom(main[i]);
		p.second = stod(value[i]);
		val.push_back(p);
	}

	return val;
}



