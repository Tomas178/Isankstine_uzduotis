#include "../Headers/Funkcijos.h"

std::vector <std::string> urls;
std::map <std::string, std::vector<int>> sarasas;


int main() {
    std::string Norimas_Failas;
    std::ifstream DF(Norimas_Failas);
    while(true){
        Norimas_Failas = GalimiFailai();
        std::ifstream DF(Norimas_Failas);

        if (!DF.is_open()) {
            std::cout << "Nurodyto failo nepavyko atidaryti:(" << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            break;
        }
    }

    std::cout << "\nPalaukite kol failas bus nuskaitytas..." << std::endl;
    Skaitymas(Norimas_Failas, sarasas, urls);
    DF.close();
    std::cout << "\nFailas nuskaitytas. Rezultatus rasite faile " << "rezultatai.txt" << std::endl;
    Isvedimas(sarasas, urls);
}