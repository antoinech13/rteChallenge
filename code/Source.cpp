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
#include <fstream>

void writeSoluce(vector<int> time)
{
    ofstream monFlux("Soluce.txt");

    if (monFlux)
    {
        for (int inter = 0; inter < time.size(); inter++)
        {
            monFlux << "I" << inter + 1 << " " << time[inter] << endl;
        }
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
    }

    monFlux.close();
}


using namespace std;

int main(int argc, char* argv[]) {

    const char* path = argv[1];
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

    dataCollector D(exemple);
    cout << "ici \n";
    Solver s(D);
    cout << "la \n";

    vector<int> time;
    vector<int> violation = s.estimateViolation(s.getTime());
    cout << "violation" << '\n';
    for (int i = 0; i < violation.size(); i++)
        cout << violation[i] << " ";
    cout << '\n';
    s.move();
    cout << "new violation" << '\n';
    violation = s.estimateViolation(s.getTime());
    for (int i = 0; i < violation.size(); i++)
        cout << violation[i] << " ";
    cout << '\n';
    time = s.getTime();
    cout << "time" << '\n';
    for (int i = 0; i < time.size(); i++)
        cout << time[i] << " ";
    
    writeSoluce(time);



}



