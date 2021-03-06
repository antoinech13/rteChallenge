#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <list>
#include <vector>
#include <utility>
#include "Parser.h"
#include "Intervention.h"
#include "dataCollector.h"
#include "Solver.h"

void writeSoluce(vector<int> time, dataCollector D, string savePath)
{
    ofstream monFlux(savePath);

    if (monFlux)
    {
        for (int inter = 0; inter < time.size(); inter++)
        {
            monFlux << D.getInterventions()[inter].getName() << " " << time[inter] << endl;
        }
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
    }

    monFlux.close();
}


using namespace std;

void print(vector<int> tab) {
    for (int i = 0; i < tab.size(); i++)
        cout << tab[i] << " ";
    cout << '\n';
}

void print(vector<double> tab) {
    for (int i = 0; i < tab.size(); i++)
        cout << tab[i] << " ";
    cout << '\n';
}

void print(vector<string> tab) {
    for (int i = 0; i < tab.size(); i++)
        cout << tab[i] << " ";
    cout << '\n';
}

int main(int argc, char* argv[]) {
    double timeStart = clock();
    char* path;
    string savePath, seed;
    int team = 62;
    int timeLimit = -1;

    cout << argc;
    for (int i = 0; i < argc; i++) {
        if ((string)argv[i] == "-t") {
            timeLimit = stoi(argv[i + 1]);
            cout << "timeLimit: " << timeLimit << '\n';
        }
        else if ((string)argv[i] == "-p") {
            path = argv[i + 1];
            cout << "instance_name: " << path << '\n';
        }
        else if ((string)argv[i] == "-o") {
            savePath = argv[i + 1];
            cout << "new_solution_filename: " << savePath << '\n';
        }
        else if ((string)argv[i] == "-name") {
            cout << "j" << team << '\n';
            return team;
        }
        else if ((string)argv[i] == "-s") {
            seed = argv[i + 1];
            cout << "seed: " << seed << '\n';
        }
  
    }
            


    FILE* exemple;
    

    vector<int> c;
    exemple = fopen(path, "r");

    if (exemple == NULL) {
        printf("errore to open file\n");
        return 0;
    }
    else {
        printf("open file\n");
    }
    

    srand(stoi(seed));

    dataCollector D;
    
    if (timeLimit != -1)
        D = dataCollector(exemple, timeLimit);
        
    else 
        D = dataCollector (exemple);
        
    
   /*
    cout << "test of the dataCollector \n";
    cout << "alpha \n";
    cout << D.getAlpha() << '\n';
    cout << "T\n";
    cout << D.getT() << '\n';
    cout << "quantile \n";
    cout << D.getQuantile() <<'\n';
    cout << "computational time \n";
    cout << D.getComputationalTime() << '\n';
    cout << "scenario numbers:\n";
    print(D.getScenarioNumber());
    cout << "get resources:\n";
    vector<pair<int, map<string, vector<double>>>> res = D.getResources();
    cout << " first: " << res[0].first << '\n';
    cout << " second:\n";
    print(res[0].second["max"]);
    cout << "exclusion:\n";
    vector<pair<string, vector<double>>> exclu = D.getExclusions();
    cout << " first: " << exclu[0].first << '\n';
    cout << " second:\n";
    print(exclu[0].second);
    cout << "seasons:\n";
    map<string, vector<double>> seas = D.getSeasons();
    print(seas["winter"]);
    cout << "Interventions: \n";
    vector<Intervention> inter = D.getInterventions();
    cout << " Tmax:\n";
    cout << inter[0].getTmax() << '\n';
    cout << " Delta\n";
    print(inter[0].getDelta());
    cout << "InterId\n";
    cout << inter[0].getInterId() << '\n';
    cout << "workload:\n";
    vector<pair<int, vector<pair<int, vector<pair<int, double>>>>>> wk = inter[0].getWorkload();
    cout << "first: " << wk[0].first <<'\n';
    cout << "value 0 first: " << wk[0].second[0].first << '\n';
    cout << "value 0 0 first: " << wk[0].second[0].second[0].first << '\n';
    cout << "value value " << wk[0].second[0].second[0].second << '\n';
    cout << "risk \n";
    vector<vector<pair<int, vector<double>>>> rsk = inter[0].getRisk();
    cout << "first 0 0 " << rsk[0][0].first << '\n';
    cout << "value\n";
    print(rsk[0][0].second);
    */
    
    
    
   
       
    Solver s(D);
    cout << "la \n";

    vector<int> time;
    vector<int> violation = s.estimateViolation(s.getTime());
    cout << "violation" << '\n';
    for (int i = 0; i < violation.size(); i++)
        cout << violation[i] << " ";
    cout << '\n';
    s.move(timeStart);
    cout << "new violation" << '\n';
    violation = s.estimateViolation(s.getTime());
    for (int i = 0; i < violation.size(); i++)
        cout << violation[i] << " ";
    cout << '\n';
    time = s.getTime();
    cout << "time" << '\n';
    for (int i = 0; i < time.size(); i++)
        cout << time[i] << " ";
   
   writeSoluce(time, D, savePath);

    

}



