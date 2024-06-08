#include "../Headers/Funkcijos.h"

void Skaitymas(){
    std::ifstream DF("Tekstas.txt");
    if(!DF.good()){
        std::cout << "Failas nerastas";
        return;
    }
    std::string line;
    std::regex URL_CHECK = std::regex("(((http|https)://)?www\\.)?[a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)");
    int eilutesNR = 0;
    while(!DF.eof()){
        eilutesNR++;
        std::getline(DF, line);
        
        std::stringstream stream(line);
        std::string zodis;

        int zodzioNumeris = 0;
        while(stream >> zodis){
            zodzioNumeris++;
            std::transform(zodis.begin(), zodis.end(), zodis.begin(), [](unsigned char c) { return std::tolower(c); });

            if(std::regex_match(zodis, URL_CHECK)){
                if(zodis[zodis.length() - 1] == ',' || zodis[zodis.length() - 1] == '.'){
                    zodis.resize(zodis.length() - 1);
                }   
                url.insert({zodis, {zodzioNumeris, {eilutesNR}}});
                zodis.clear();
            }
            if(isdigit(zodis[0]) || ispunct(zodis[0])){
                    for (int i = 0; i < zodis.length(); i++){
                        if (isdigit(zodis[i]) || ispunct(zodis[i])){
                            zodis = zodis.substr(i + 1);
                            i = -1;
                        }
                    }
            }
            if(zodis[zodis.length() - 2] == '\''){
                zodis.resize(zodis.length() - 2);
            }

            if(isdigit(zodis[zodis.length() - 1]) || ispunct(zodis[zodis.length() - 1])){         
                for(int i = zodis.length() - 1; i > 0; i--){
                    if(!std::isalpha(zodis[i])){
                        zodis.resize(i);
                        i = zodis.length();
                    }
                }
            }
            if(!zodis.empty()){
                auto it = Zodziai.find(zodis);
                if (it != Zodziai.end()) {
                    it->second.first++;
                    it->second.second.insert(eilutesNR);
                } else {
                    Zodziai.insert({zodis, {1, {eilutesNR}}});
                }
            }
        }
    }
}

void ZodziuIsvedimas(const std::map<std::string, std::pair<int, std::set<int>>> Zodziai){
    std::ofstream RF("Zodziai.txt");
    RF << "Visi žodziai pasikartojantys daugiau nei 1 kartą: " << std::endl;
    for (const auto &elem : Zodziai){
        if (elem.second.first > 1){
            RF << "Žodis '"<< elem.first << "' Pasikartoja " << elem.second.first << " kartus eilutėse [";
            for(const auto &eilute : elem.second.second){
                RF << eilute;
                if(eilute != *elem.second.second.rbegin()){
                    RF << ", ";
                } else {
                    RF << "].";
                }
            }
            RF << std::endl;
        }
    }
    RF.close();
    std::cout << "Zodziai isvesti i Zodziai.txt faila:)" << std::endl;
}

void URLIsvedimas(const std::map<std::string, std::pair<int, std::set<int>>> &URL){
    std::ofstream RF("URL.txt");
    RF << "URL: " << URL.size() << std::endl;
    for (auto elem : URL){
        RF << elem.first << std::endl;
    }
    RF.close();
    std::cout << "URL isvesti i URL.txt faila:)" << std::endl;
}