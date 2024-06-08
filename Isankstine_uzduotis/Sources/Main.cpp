#include "../Headers/Funkcijos.h"

std::map<std::string, std::pair<int, std::set<int>>> Zodziai;
std::map<std::string, std::pair<int, std::set<int>>> url;

int main(){
    Skaitymas();
    ZodziuIsvedimas(Zodziai);
    URLIsvedimas(url);
    return 0;
}