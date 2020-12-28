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
    cout << "ici \n";
    Solver s(D);
    cout << "la \n";


    vector<int> violation = s.estimateViolation(s.getTime());
    for (int i = 0; i < violation.size(); i++)
        cout << violation[i] << " ";
    cout << '\n';
    s.move();
    cout << "new violation" << '\n';
    violation = s.estimateViolation(s.getTime());
    for (int i = 0; i < violation.size(); i++)
        cout << violation[i] << " ";
    cout << '\n';



}



