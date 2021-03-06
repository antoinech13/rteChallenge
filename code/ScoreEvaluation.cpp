#include "ScoreEvaluation.h"
#include <algorithm> 

using namespace std;


void ScoreEvaluation::print(vector<vector<vector<pair<int, vector<double>>>>> riskByInterventions) {
	for (int i = 0; i < riskByInterventions.size(); i++) {
		for (int j = 0; j < riskByInterventions[i].size(); j++) {
			for (int k = 0; k < riskByInterventions[i][j].size(); k++) {
				cout << "key: " << riskByInterventions[i][j][k].first << " ";
				for (int w = 0; w < riskByInterventions[i][j][k].second.size(); w++)
					cout << riskByInterventions[i][j][k].second[w] << " ";
				cout << '\n';
			}
			cout << '\n';
		}
	}
}

ScoreEvaluation::ScoreEvaluation(dataCollector data) {
	this->data = data;
	this->interventions = data.getInterventions();
	this->scenarios = data.getScenarioNumber();
	this->alpha = data.getAlpha();
	this->quantile = data.getQuantile();
}

ScoreEvaluation::ScoreEvaluation(){}

double ScoreEvaluation::extractScenario(vector<int> interTime) {
	vector<vector<double>> value; // line: scenario column: time
	vector<vector<vector<pair<int, vector<double>>>>> riskByInterventions = extractAllRisk();
	vector<double> risksAtTime, valueForOneScenario, scNb = this->scenarios;
	vector<int> idxStartTime = interTime;

	int idx, risk = 0;
	double avgBySc = 0, avgByTime = 0;
	this->means.clear();
	this->risks.clear();

	

	for (int j = 0; j < this->data.getT(); j++) {
		for (int k = 0; k < scNb[j]; k++) {
			for (int i = 0; i < riskByInterventions.size(); i++) {
				idx = keyToIdx(interTime[i], riskByInterventions[i][j]);
				
				//cout << "idx compute" << '\n';
				//cout << "Tmax: " << this->interventions[i].getTmax() << " j: " << j <<'\n';
				if (idx != -1 ) {
					try
					{
						cout << "idx: " << idx << " key: " << riskByInterventions[i][j][idx].first << '\n';
						risk += riskByInterventions[i][j][idx].second[k];
					}
					catch (const std::exception& e)
					{
						risk += 1;
					}
					
				}
			}
			valueForOneScenario.push_back(risk);
			avgBySc += risk;
			risksAtTime.push_back(risk);
			risk = 0;
		}
		cout << "j\n";
		value.push_back(valueForOneScenario);
		avgBySc /= valueForOneScenario.size();
		this->means.push_back(avgBySc);
		this->risks.push_back(risksAtTime);
		avgByTime += avgBySc;
		avgBySc = 0;
		valueForOneScenario.clear();
		risksAtTime.clear();

	}
	avgByTime /= value.size();
	return avgByTime;
}


int ScoreEvaluation::keyToIdx(int time, vector<pair<int, vector<double>>> rsk) {
	for (int i = 0; i < rsk.size(); i++) {
		if (rsk[i].first == time)
			return i;
	}
	cout << "didn't found the starting time, for the time step: " << time << '\n';
	return -1;
}

/*on extrait les valeurs de risque � un temps donn�, pour chaque sc�nario on somme les valeurs de risque pour chaque intervention
ex : au temps 1, pour le sc�nario 1 risque(sc�nario 1, temps 1) = risque(sc�nario 1, temps 1)_I1 + ... + risque(sc�nario 1, temps 1)_In;
Ensuite, on classe le tableau des sommes de risque pour chaque sc�nario � chaque temps par ordre croissant
et on prend la valeur de ce tableau tri� � l'entier arrondi au sup�rieur du quantile tau*(longueur du tableau)-1 qui est la valeur Q(quantile) au temps t.
Puis l'exc�s pour le quantile tau au temps t est la valeur absolue entre Qt et le risque moyen au temps t;
On somme les diff�rents exc�s pour tous les temps et on divise par la p�riode de temps T;


*/

bool compare(int i, int j) 
{ 
	return (i < j); 
}


double ScoreEvaluation::extractScenario2() {
	double score2 = 0;
	cout << "scenario2\n";
	for (int tim = 0; tim < this->risks.size(); tim++)
	{
		sort(this->risks[tim].begin() , this->risks[tim].end(), compare);

		int indiceScenar = this->risks[tim].size() * this->quantile - 1;

		if (this->risks[tim][indiceScenar]-this->means[tim] < 0)
		{
			score2 += 0;
		}
		else
		{
			score2 += this->risks[tim][indiceScenar] - this->means[tim];
		}
		
	}
	return score2 / this->risks.size();
}


double ScoreEvaluation::extractScenarioFinal(vector<int> interTime) {
	double score_final = 0;
	double risk1 = extractScenario(interTime);
	double risk2 = extractScenario2();
	
	cout << " TimeScore \n";
	for (int i = 0; i < interTime.size(); i++) {
		cout << interTime[i] << " ";
	}
	cout << "\n";
	cout << "risk2: " << risk2 << " risk1: " << risk1 << '\n';
	score_final = this->alpha * risk1 + (1 - this->alpha) * risk2;
	return score_final;

}



vector<vector<vector<pair<int, vector<double>>>>> ScoreEvaluation::extractAllRisk() {
	vector<vector<vector<pair<int, vector<double>>>>> value;

	for (int i = 0; i < this->interventions.size(); i++)
		value.push_back(this->interventions[i].getRisk());
	return value;
}