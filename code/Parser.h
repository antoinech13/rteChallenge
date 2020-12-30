#pragma once
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Parser
{
public:
    int nextChar();
    vector<int> toVector();
    /**
    *
    *Find index of a key in a vector of int (int is char here)
    *
    *This function return a int array (2x1) which are the index of the beginning of the first char
    * of first occurence of the string key and index of the last char of this occurence of the string key
    * in the vector file
    *
    *@param vFile, is the vector<int> of char
    *@param key, is the string that you are looking for in vFile
    *
    *@return idx, an array of 2x1 where the first value is the index of the first char
    * and the second value is the index of the last char of the key in vFile
    *
    *
    */
    static int* find(string vFile, string key);
    int* find(string key);
    static int keyFind(vector<string> keyTab, string key);
    int keyFind(string key);
    static vector<int> stringToInt(string source);
    static vector<double> toDbTable(string tab);
    static vector<string> toStringTable(string tab);
    static vector<double> strTabToDbTabWithoutFirstCharacther(vector<string> tab, char C, int idx);
    static vector<string> mainSequence(string vFile);
    static vector<string> split(string str, char C);
    static double getDoubleWithoutCom(string str);
    vector<string> mainSequence();
    static vector<string> divideSection(string vFile);
    vector<string> divideSection();
    Parser(FILE* file);
    Parser(string vFile);
    static string toString(vector<int> vFile);
    string getVFile();
    vector<string> getMain();
    vector<string> getValues();
    

   
private:
    FILE* file;
    string vFile;
    vector<string> main;
    vector<string> values;

};

