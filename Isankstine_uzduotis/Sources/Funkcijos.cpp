#include "../Headers/Funkcijos.h"

std::string GalimiFailai() {
    std::cout << "\nGalimi failai:" << std::endl;
    const std::filesystem::path dirpath("./");
    for (const auto& i : std::filesystem::directory_iterator{dirpath}) {
        if (i.is_regular_file() && i.path().extension() == ".txt") {
            std::cout << i.path().filename() << std::endl;
        }
    }
    std::string Norimas_Failas;
    std::cout << "\nIveskite failo, kuri norite nuskaityti, pavadinima: "; std::cin >> Norimas_Failas; 

    if (Norimas_Failas.size() < 4 || Norimas_Failas.substr(Norimas_Failas.size() - 4) != ".txt")
        Norimas_Failas += ".txt";

    return Norimas_Failas.empty() ? "text.txt" : Norimas_Failas;
}


bool isURL (const std::string& zodis) {
    std::regex urlRegex("(((http|https)://)?www\\.)?[a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)");
    return std::regex_match(zodis, urlRegex);
}

std::string Zodziu_Tvarkymas(const std::string& zodis) {
    std::regex notFixedRegex("[^\\w]+");
    std::string Sutvarkytas_Zodis = std::regex_replace(zodis, notFixedRegex, "");
    transform(Sutvarkytas_Zodis.begin(), Sutvarkytas_Zodis.end(), Sutvarkytas_Zodis.begin(), ::tolower);
    return Sutvarkytas_Zodis;
}

void Prideti_Zodi(const std::string& zodis, std::map<std::string, std::vector<int>>& sarasas, int eilNr) {
    if (zodis.empty()) return;

    auto it = sarasas.find(zodis);

    if (it == sarasas.end()) {
        std::vector<int> eiluciuNr;
        eiluciuNr.push_back(eilNr);
        sarasas[zodis] = eiluciuNr;
    }
    else {
        std::vector<int>& eiluciuNr = it->second;
        if (eilNr != eiluciuNr.back()) {
            eiluciuNr.push_back(eilNr);
        }
    }
}

void Skaitymas(const std::string& Norimas_Failas,  std::map<std::string, std::vector<int>>& sarasas, std::vector<std::string>& urls) {
    std::ifstream DF(Norimas_Failas);
    std::stringstream tekstas;
    tekstas << DF.rdbuf();
    DF.close();
    std::string eilute;
    int eilNr = 0;

    while(std::getline(tekstas, eilute)) {
        eilNr++;
        std::string zodis;
        std::istringstream iss(eilute);
        while(iss >> zodis) {
            bool ArSkaicius = false; 
            for (char c : zodis) {
                if (isdigit(c)) {
                    ArSkaicius = true;
                    break;
                }
            }
            if(isURL(zodis)) {
                urls.push_back(zodis);
            }
            else if (!ArSkaicius) {
                zodis = Zodziu_Tvarkymas(zodis);
                Prideti_Zodi(zodis, sarasas, eilNr);
            }
        }
    }
}

void Isvedimas ( std::map<std::string, std::vector<int>>& sarasas,std::vector<std::string> urls) {
    std::ofstream RF("rezultatai.txt");
    std::stringstream FF;
    if (!RF.good()) {
        std::cout << "Failo nepavyko sukurti." << std::endl;
        return;
    }

    FF << "URL count: " << urls.size() << "." << std::endl;
    for (const auto& url : urls)
        FF << url << std::endl;

    FF << std::endl;

   if (!sarasas.empty()) {
        FF << std::left << std::setw(20) << "ZODIS" << std::setw(8) << "KIEKIS" << "EILUCIU NR." << std::endl;

        for (const auto& i : sarasas) {
            if (i.second.size() > 1){
                FF << std::left << std::setw(20) << i.first << std::setw(8) << i.second.size();

                for (int j : i.second) {
                    FF << std::setw(4) << j;
                }

            FF << std::endl;
            }
        }
    }
    RF << FF.str();
    FF.clear();
    RF.close();
}