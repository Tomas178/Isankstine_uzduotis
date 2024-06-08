#include "../Headers/Funkcijos.h"

std::map<string, int> Zodziai;
std::map<string, vector<int>> crossCheck;
vector<string> url;

int main(){
    Skaitymas();
    ZodziuIsvedimas(Zodziai);
    URLIsvedimas(url);
    return 0;
}