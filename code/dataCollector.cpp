#include "dataCollector.h"
#include "Parser.h"
#include "Intervention.h"
#include "Resources.h"
#include "Seasons.h"
#include "Exclusions.h"


int dataCollector::getT() {
	return this->T;
}

float dataCollector::getAlpha() {
	return this->alpha;
}

float dataCollector::getQuantile() {
	return this->quantile;
}

vector<int> dataCollector::getScenarioNumber() {
	return this->scenariosNumber;
}

vector<Intervention> dataCollector::getInterventions() {
	return this->interventions;
}

vector<pair<string, map<string, vector<int>>>> dataCollector::getResources() {
	return this->resources;
}

vector<pair<string, vector<int>>> dataCollector::getExclusions() {
	return this->exclusions;
}

map<string, vector<int>> dataCollector::getSeasons() {
	return this->seasons;
}

dataCollector::dataCollector(FILE* vFile) {
	Parser I(vFile);
	Exclusions E(I.getValues()[I.keyFind("Exclusions")]);
	Resources R(I.getValues()[I.keyFind("Resources")]);
	Seasons S(I.getValues()[I.keyFind("Seasons")]);

	this->T = stoi(I.getValues()[I.keyFind("T")]);
	this->alpha = stof(I.getValues()[I.keyFind("Alpha")]);
	this->quantile = stof(I.getValues()[I.keyFind("Quantile")]);
	this->scenariosNumber = Parser::toIntTable(I.getValues()[I.keyFind("Scenarios_number")]);
	this->interventions = buildInterventions(I.getValues()[I.keyFind("Interventions")]);
	this->resources = R.getData();
	this->exclusions = E.getData();
	this->seasons = S.getData();

}

dataCollector::dataCollector() {};

vector<Intervention> dataCollector::buildInterventions(string vFile) {
	Parser I(vFile);
	vector<string> main = I.getMain();
	vector<string> values = I.getValues();
	vector<Intervention> val;

	for (int i = 0; i < values.size(); i++) {
		Intervention it(values[i]);
		val.push_back(it);
	}
	return val;

}
