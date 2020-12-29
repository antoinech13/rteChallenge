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


using namespace std;

int main() {

    const char* path = "example1.json";
    FILE* exemple;
   
    vector<int> c;
    exemple = fopen(path, "r");

    if (exemple != NULL) {
        printf("cannot open file\n");
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
    



}



