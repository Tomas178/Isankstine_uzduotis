#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H

#include <map>
#include <vector>
#include <string>
#include <regex>
#include <set>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <cctype>
#include <iomanip>

extern std::map<std::string, std::pair<int, std::set<int>>> Zodziai;
extern std::map<std::string, std::pair<int, std::set<int>>> url;

void Skaitymas();
void ZodziuIsvedimas(const std::map<std::string, std::pair<int, std::set<int>>> Zodziai);
void URLIsvedimas(const std::map<std::string, std::pair<int, std::set<int>>> &URL);

#endif