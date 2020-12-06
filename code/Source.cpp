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
#include "WorkloadCheck.h"


using namespace std;

int main() {

    const char* path = "example2.json";
    FILE* exemple1;
    errno_t err;
    vector<int> c;
    err = fopen_s(&exemple1, path, "r");

    if (err != 0) {
        printf("cannot open file\n");
        return 0;
    }
    else {
        printf("open file\n");
    }

    

    dataCollector D(exemple1);
    Solver s(D);

    vector<int> nik = s.initTime;
    
    WorkloadCheck w(D);
    int score = w.workloadCheck(nik);
    vector<int> mauvais =w.getInterventionBad();

    cout << "solution :";
    for (int indice = 0; indice < nik.size(); indice++)
        cout << "intervention : " << indice+1 << " jour : "<<nik[indice]<<"  ";
    cout << "\n";

    cout << "workload_mine : ";
    vector<vector<int>> workloadmine = w.getArrayWorkload();
    for (int ligne = 0; ligne < workloadmine.size(); ligne++) {
        for (int colonne = 0; colonne < workloadmine[ligne].size(); colonne++)
            cout << workloadmine[ligne][colonne]<<" ";
        cout << "\n";
    }

    vector<vector<int>> tempsma = w.getTimeBad();

    cout << "jour mauvais : ";
    for (int ligne = 0; ligne < tempsma.size(); ligne++) {
        for (int colonne = 0; colonne < tempsma[ligne].size(); colonne++)
            cout << tempsma[ligne][colonne] << " ";
        cout << "\n";
    }

    cout << "score : " << score<<"\n";
    cout << "intervention mauvaise : ";
    for (int indice=0;indice<mauvais.size();indice++)
        cout << mauvais[indice] <<" " ;



}



