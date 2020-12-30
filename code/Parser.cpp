#include "Parser.h"
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>


using namespace std;


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
int Parser::nextChar() {
    char c = fgetc(file);
    if (c == '\n' || c == ' ' || c == '\f' || c == '\r' || c == '\t' || c == '\v') {
        return nextChar();
    }
    return c;
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
vector<int> Parser::toVector() {
    vector<int> c;
    do {
        c.push_back(nextChar());
    } while (c.back() != EOF);

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
int* Parser::find(string vFile, string key) {
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
    *Find index of a key
    *
    *This function return a int array (2x1) which are the index of the beginning of the first char
    *of first occurence of the string key and index of the last char of this occurence of the string key
    *in the vector file
    *
    *
    *@param key, is the string that you are looking for in vFile
    *
    *@return idx, an array of 2x1 where the first value is the index of the first char
    * and the second value is the index of the last char of the key in main (vector<string> of primary keys)
    *
    *
    */
int* Parser::find(string key) {

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
int Parser::keyFind(vector<string> keyTab, string key) {
    for (int i = 0; i < keyTab.size(); i++) {
        if (keyTab[i] == key)
            return i;
    }
    return NULL;
}

/**
*
*Function for find idex of a string key in the main vector<string> of primary keys
*
*@param string key: key to find in main
*
*@return int idex of key in main
*
*/
int Parser::keyFind(string key) {
    for (int i = 0; i < main.size(); i++) {
        if (main[i] == key)
            return i;
    }
    return NULL;
}

/**
*
* Function which convert string to a vector<int> (basicly a vector of char)
* 
* @param string source: the string that you want convert.
* @return vector<int> which 
* 
*/
vector<int> Parser::stringToInt(string source) {
    vector<int> intter;
    for (int inter : source)
        intter.push_back(inter);
    return intter;
}

double Parser::getDoubleWithoutCom(string str) {
    string val;
    for (int i = 0; i < str.size(); i++)
        if (str[i] != '"')
            val.push_back(str[i]);
    return stod(val);
}

/**
*
* Function which get values of table in JSON file
* 
* 
* @param string of data
* @return vector<int> which is the int table of data
* 
* 
*/
vector<double> Parser::toDbTable(string tab) {
    string value;
    vector<double> values;
    int comma = 0;
    int bra = 0;
    for (int i = 0; i < tab.size(); i++) {
        

        if (tab[i] == ',') {

            values.push_back(stod(value));
            value = "";
        }
        if (tab[i] == ']') {
            bra--;
            values.push_back(stod(value));
            return values;

        }
        if (bra == 1 && tab[i] != ',' && tab[i] != '"') {
            value.push_back(tab[i]);
        }
        if (tab[i] == '[')
            bra++;
    }


}

vector<string> Parser::toStringTable(string tab) {
    string value;
    vector<string> values;
    int bra = 0;
    for (int i = 0; i < tab.size(); i++) {
        if (tab[i] == ',') {

            values.push_back(value);
            value = "";
        }
        if (tab[i] == ']') {
            bra--;
            values.push_back(value);
            return values;

        }
        if (bra == 1 && tab[i] != ',' && tab[i] !='"') {
            value.push_back(tab[i]);
        }
        if (tab[i] == '[')
            bra++;
    }
}

vector<string> Parser::split(string str, char C) {
    vector<string> result;
    string val = "";

    for (int i = 0; i < str.size(); i++) {
        
        if (str[i] == C) {
            result.push_back(val);
            val = "";
        }
        else
            val.push_back(str[i]);
        
    }

    if (val.size() > 0)
        result.push_back(val);

    return result;
}



vector<double> Parser::strTabToDbTabWithoutFirstCharacther(vector<string> tab, char C, int idx) {
    vector<double> result;
    vector<string> nb;
    for (int i = 0; i < tab.size(); i++) {
        nb = split(tab[i], C);
        if(nb.size() > 0)
            if (nb[idx] != "\n" && nb[idx] != " " && nb[idx] != "\f" && nb[idx] != "\r" && nb[idx] != "\t" && nb[idx] != "\v" && nb[idx].size() > 0)
                result.push_back(stod(nb[idx]) - 1);
    }
    return result;
}

string Parser::toString(vector<int> vFile) {
    string val;
    for (int i = 0; i < vFile.size(); i++) {
        val.push_back(vFile[i]);
    }
    return val;
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
vector<string> Parser::mainSequence(string vFile) {
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
    *function which return a vector<string> of first keys
    *
    *
    *
    *@return vector<String> of all first keys of the first layer.
    *
    *
    *
    */
vector<string> Parser::mainSequence() {
    vector<string> main;
    int bra = 0;
    int com = 0;
    int croch = 0;
    bool endsection = false;
    string newmain;

    for (int i = 0; i < vFile.size(); i++) {
        if (vFile[i] == '"')
            com++;

        if (com > 1) {
            if (vFile[i] == '[')
                croch++;
            if (vFile[i] == ']')
                croch--;

            if (vFile[i] == '{')
                bra++;
            else if (vFile[i] == '}')
                bra--;
        }

        if (com % 2 != 0 && bra == 0 && croch == 0) {
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
 *function which return a vector<string> of different blocks of a vector of char (complementary to mainSequence which get keys)
 *
 *@param vFile, is a vector<int> of char.
 *@return vector<String> of all keys blocks of the same layer.
 *
 *
 */
vector<string> Parser::divideSection(string vFile) {
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

/**
 *
 *function which return a vector<string> of different blocks of the main vector (complementary to mainSequence which get keys)
 *
 *@return vector<String> of all keys blocks of the same layer.
 *
 *
 */
vector<string> Parser::divideSection() {
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

/**
*@return vFile: vector of char
*/
string Parser::getVFile() {
    return this->vFile;
}

/**
*@return main: vector of string
*/
vector<string> Parser::getMain() {
    return this->main;
}

/**
*@return values: vector of string
*/
vector<string> Parser::getValues() {
    return this->values;
}




Parser::Parser(FILE* file) {
    this->file = file;
    this->vFile = Parser::toString(toVector());
    this->main = mainSequence();
    this->values = divideSection();
}

Parser::Parser(string vFile) {
    this->vFile = vFile;
    this->main = mainSequence();
    this->values = divideSection();
}