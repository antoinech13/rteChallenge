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

float dataCollector::getComputationalTime() {
	return this->cpTime;
}

vector<double> dataCollector::getScenarioNumber() {
	return this->scenariosNumber;
}

vector<Intervention> dataCollector::getInterventions() {
	return this->interventions;
}

vector<pair<int, map<string, vector<double>>>> dataCollector::getResources() {
	return this->resources;
}

vector<pair<string, vector<double>>> dataCollector::getExclusions() {
	return this->exclusions;
}

map<string, vector<double>> dataCollector::getSeasons() {
	return this->seasons;
}


dataCollector::dataCollector(FILE* vFile) {
	cout << "begin to parse the file\n";
	Parser I(vFile);
	cout << "the file is well parse\n";
	Exclusions E(I.getValues()[I.keyFind("Exclusions")]);
	Resources R(I.getValues()[I.keyFind("Resources")]);
	Seasons S(I.getValues()[I.keyFind("Seasons")]);
	cout << "get T\n";
	this->T = stoi(I.getValues()[I.keyFind("T")]);
	cout << "get alpha\n";
	this->alpha = stof(I.getValues()[I.keyFind("Alpha")]);
	cout << "get quantile\n";
	this->quantile = stof(I.getValues()[I.keyFind("Quantile")]);
	cout << "get scenario\n";
	this->scenariosNumber = Parser::toDbTable(I.getValues()[I.keyFind("Scenarios_number")]);
	cout << "get Interventions\n";
	this->interventions = buildInterventions(I.getValues()[I.keyFind("Interventions")]);
	cout << "get resources\n";
	this->resources = R.getData();
	cout << "get exclusions\n";
	this->exclusions = E.getData();
	cout << "get seasons\n";
	this->seasons = S.getData();
	cout << "get computation Time \n";
	try
	{
		this->cpTime = stof(I.getValues()[I.keyFind("ComputationTime")]);
	}
	catch (const std::exception& e)
	{
		this->cpTime = 1;
	}
	

}

dataCollector::dataCollector() {};

vector<Intervention> dataCollector::buildInterventions(string vFile) {
	Parser I(vFile);
	vector<string> main = I.getMain();
	vector<string> values = I.getValues();
	vector<Intervention> val;
	//vector<double> ids = Parser::strTabToDbTabWithoutFirstCharacther(main, '_', 1);
	vector<double> ids = Parser::extractDbVecWords(main);
	ids = Parser::substract(ids, 1);

	for (int i = 0; i < values.size(); i++) {
		Intervention it(values[i]);
		it.setId(ids[i]);
		it.setName(main[i]);
		val.push_back(it);
	}
	return val;

}

int dataCollector::IdToIdx(int id) {
	for (int i = 0; i < this->interventions.size(); i++) {
		if (id == interventions[i].getInterId()) {
			return i;
		}
	}
		
	cout << "intervention not found!\n";
	return -1;
}