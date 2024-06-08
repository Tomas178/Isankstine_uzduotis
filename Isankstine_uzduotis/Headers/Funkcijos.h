#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <map>
#include <vector>
#include <string>
#include <regex>

using std::cout;
using std::regex;
using std::string;
using std::vector;
using std::endl;

extern std::map<string, int> Zodziai;
extern std::map<string, vector<int>> crossCheck;
extern vector<string> url;

void Skaitymas();
void IsvestiCrossReferenceLentele(const std::map<string, vector<int>> &crossCheck, const int eilutesNR);
void ZodziuIsvedimas(const std::map<string, int> &Zodziai);
void URLIsvedimas(const vector<string> &URL);

#endif