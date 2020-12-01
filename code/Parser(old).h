#pragma once
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>


using namespace std;

class parser {
    //RteInInstance inInstance;
public:
    FILE* file;
    vector<int> vFile;
    vector<string> main;
    vector<string> values;
    char currentChar;

    /**
    *
    *Return the next char of a file
    *
    *This function return the next char of a type *FILE and
    *eliminate tabultatio, whitespace etc...
    *
    *@return int value which is the ASCII code a the char founded.
    *
    */
    int nextChar() {
        char c = fgetc(file);
        if (c == '\n' || c == ' ' || c == '\f' || c == '\r' || c == '\t' || c == '\v') {
            return nextChar();
        }
        return c;
    }

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
    int* find(vector<int> vFile, string key) {
        int N = key.size();
        string File = "";
        int idx[2];

        for (int i = 0; i < vFile.size(); i++)
            File.push_back(vFile[i]);

        idx[0] = File.find(key);
        idx[1] = key.size() + idx[0];

        return idx;
    }

    /**
    *
    *Function for find idex of a string key in a vector<string> of keys
    *
    *@param vector<string> keyTab: tab of keys
    *@param string key: key to find in keyTab
    * 
    *@return int idex of key in keyTab
    *
    */
    int find(vector<string> keyTab, string key) {
        for (int i = 0; i < keyTab.size(); i++) {
            if (keyTab[i] == key)
                return i;
        }
        return NULL;
    }

    /**
    *
    *stock a file of type *FILE in a vector<int> (char) whithout whitspace, tab etc...
    *
    *
    *
    *@return a vector<int> of all char in the *FILE
    *
    */
    vector<int> toVector() {
        vector<int> c;
        do {
            c.push_back(nextChar());
        } while (c.back() != EOF);

        return c;
    }

    vector<int> stringToInt(string source) {
        vector<int> intter;
        for (int inter : source)
            intter.push_back(inter);
        return intter;
    }

    vector<int> toIntTable(string tab) {
        string value;
        vector<int> values;
        int bra = 0;
        for (int i = 0; i < tab.size(); i++) {
            if (tab[i] == ',') {

                values.push_back(stoi(value));
                value = "";
            }
            if (tab[i] == ']') {
                bra--;
                values.push_back(stoi(value));
                return values;

            }
            if (bra == 1 && tab[i] != ',') {
                value.push_back(tab[i]);
            }
            if (tab[i] == '[')
                bra++;
        }

       
    }


    /**
    *
    *function which return a vector<string> of first keys of a vector of char
    *
    *
    *@param vFile, is a vector<int> of char.
    *@return vector<String> of all first keys of the first layer.
    *
    *
    *
    */
    vector<string> mainSequence(vector<int> vFile) {
        vector<string> main;
        int bra = 0;
        int com = 0;
        bool endsection = false;
        string newmain;

        for (int i = 0; i < vFile.size(); i++) {
            if (vFile[i] == '"')
                com++;

            if (com > 1) {
                if (vFile[i] == '{')
                    bra++;

                else if (vFile[i] == '}')
                    bra--;
            }

            if (com % 2 != 0 && bra == 0) {
                if (vFile[i] != '"') {
                    newmain.push_back(vFile[i]);
                    endsection = false;
                }
            }
            else if (com % 2 == 0 && !endsection && ((bra == 1 && vFile[i + 1] == '}') || (bra == 0 && vFile[i] == ',')) || bra < 0) {
                main.push_back(newmain);
                newmain = "";
                endsection = true;
            }

        }
        return main;

    }
    /**
    *
    *function which return a vector<string> of different keys blocks of a vector of char
    *
    *@param vFile, is a vector<int> of char.
    *@return vector<String> of all keys blocks of the same layer.
    *
    *
    */
    vector<string> divideSection(vector<int> vFile) {
        string sect;
        vector<string> section;
        int doublepoint = 0;
        int accolade = 0;
        int crochet = 0;
        for (int i = 0; i < vFile.size(); i++) {

            if (doublepoint > 0) {
                if (vFile[i] == '{')
                    accolade++;
                if (vFile[i] == '}')
                    accolade--;
            }

            if (vFile[i] == ':' && accolade == 0 && doublepoint == 0) {
                doublepoint++;
            }
            else if (doublepoint == 1)
                sect.push_back(vFile[i]);
            if (vFile[i] == '[' && accolade == 0)
                crochet++;
            if (vFile[i] == ']' && accolade == 0)
                crochet--;

            if (doublepoint == 1 && accolade < 1 && crochet == 0) {
                if (vFile[i] == ',' || accolade < 0) {
                    sect.pop_back();
                    section.push_back(sect);
                    sect = "";
                    doublepoint--;
                }
            }

        }
        return section;
    }

  


    parser(FILE* file) {
        this->file = file;
        this->vFile = toVector();
        this->main = mainSequence(vFile);
    }

    parser(vector<int> vFile) {
        this->vFile = vFile;
        this->main = mainSequence(vFile);
        this->values = divideSection(vFile);
    }
};