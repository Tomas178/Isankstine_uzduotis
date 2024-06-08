#include "../Headers/Funkcijos.h"

void Skaitymas(){
    std::ifstream DF("Tekstas.txt");
    if(!DF.good()){
        std::cout << "Failas nerastas";
        return;
    }
    string line;
    regex URL_CHECK = regex("(((http|https)://)?www\\.)?[a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)");
    int eilutesNR = 0;
    while(!DF.eof()){
        crossCheck.clear();
        eilutesNR++;
        getline(DF, line);
        
        std::stringstream stream(line);
        string zodis;

        int zodzioNumeris = 0;
        while(stream >> zodis){
            zodzioNumeris++;
            std::transform(zodis.begin(), zodis.end(), zodis.begin(), [](unsigned char c) { return std::tolower(c); });

            if(std::regex_match(zodis, URL_CHECK)){
                if(zodis[zodis.length() - 1] == ',' || zodis[zodis.length() - 1] == '.'){
                    zodis.resize(zodis.length() - 1);
                }   
                url.push_back(zodis);
                zodis.clear();
            }
            if(isdigit(zodis[0]) || ispunct(zodis[0])){
                if (zodis.find("th") == string::npos){
                    for (int i = 0; i < zodis.length(); i++){
                        if (isdigit(zodis[i]) || ispunct(zodis[i])){
                            zodis = zodis.substr(i + 1);
                            i = -1;
                        }
                    }
                }
            }
            if(zodis[zodis.length() - 2] == '\''){
                zodis.resize(zodis.length() - 2);
            }

            if(isdigit(zodis[zodis.length() - 1]) || ispunct(zodis[zodis.length() - 1])){         
                if(zodis[zodis.length() - 1] != 'h' && zodis[zodis.length() - 2] != 't'){
                    for(int i = zodis.length() - 1; i > 0; i--){
                        if(isdigit(zodis[i]) || ispunct(zodis[i])){
                            zodis.resize(i);
                            i = zodis.length();
                        }
                    }
                }
            }
            if(!zodis.empty()){
                crossCheck.insert({ zodis, {0} });
                crossCheck[zodis].push_back(zodzioNumeris);

                auto it = Zodziai.find(zodis);
                if (it != Zodziai.end()) {
                    it->second++;
                } else {
                    Zodziai[zodis] = 1;
                }
            }
        }
        IsvestiCrossReferenceLentele(crossCheck, eilutesNR);
    }
}

void IsvestiCrossReferenceLentele(const std::map<string, vector<int>> &crossCheck, const int eilutesNR){
    std::ofstream RF("CrossReference.txt", std::ios::app);
    RF << eilutesNR << " - osios eilutes zodziu numeriai: " << endl;
    for (auto elem : crossCheck){
        if (elem.second.size() > 1){
            RF << elem.first << " ";
        }
            
        for(int i = 1; i < elem.second.size(); i++){
            RF << elem.second.at(i) << " ";
        }

        RF << endl;
    }
    RF << endl;
    RF.close();
}

void ZodziuIsvedimas(const std::map<string, int> &Zodziai){
    std::ofstream RF("Zodziai.txt");
    RF << "Visi zodziai pasikartojantys daugiau nei 1 karta: " << endl;
    for (auto elem : Zodziai){
        if (elem.second > 1){
            RF << elem.first << " " << elem.second << endl;
        }
    }
    RF.close();
    cout << "Zodziai isvesti i Zodziai.txt faila:)" << endl;
}

void URLIsvedimas(const vector<string> &URL){
    std::ofstream RF("URL.txt");
    RF << "URL: " << URL.size() << endl;
    for (auto elem : URL){
        RF << elem << endl;
    }
    RF.close();
    cout << "URL isvesti i URL.txt faila:)" << endl;
}