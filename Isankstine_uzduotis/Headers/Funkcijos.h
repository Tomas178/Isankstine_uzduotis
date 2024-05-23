#include <vector>
#include <map>
#include <string>
#include <regex>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <fstream>
#include <sstream>
#include <filesystem>

bool isURL (const std::string& zodis);
std::string GalimiFailai();
std::string Zodziu_Tvarkymas(const std::string& zodis);
void Prideti_Zodi(const std::string& zodis, std::map<std::string, std::vector<int>>& sarasas, int eilutesNumeris);
void Skaitymas(const std::string& fileChoice,  std::map<std::string, std::vector<int>>& sarasas, std::vector<std::string>& urls);
void Isvedimas ( std::map<std::string, std::vector<int>>& sarasas,std::vector<std::string> urls);

