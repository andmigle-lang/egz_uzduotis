#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <cctype>
#include <locale>
#include <iomanip>
#include <vector>
#include <set>
#include <regex>
#include <codecvt>
#include <windows.h>

using std::ifstream;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::stringstream;
using std::ofstream;
using std::right;
using std::setw;
using std::fixed;
using std::vector;
using std::left;
using std::set;
using std::regex;
using std::smatch;

int main() {
    //std::locale::global(std::locale(""));
    //std::locale utf8_locale(std::locale(), new std::codecvt_utf8<char>);
    SetConsoleOutputCP(CP_UTF8); SetConsoleCP(CP_UTF8); std::locale::global(std::locale("en_US.UTF-8"));
    std::locale utf8("en_US.UTF-8");

    ifstream F("Vilnius.txt");
    F.imbue(utf8);
    /*F.imbue(utf8_locale);*/
    if (!F) {
        cout << "Failas neatidarytas" << endl;
        return 1;
    }

    map<string, int> zodziu_skaicius;
    map<string, vector<int>> zodziu_eiluciu_nr;

    string eilute;
    int eilutes_nr = 0;

    while (getline(F, eilute)) {
        eilutes_nr++;

        stringstream ss(eilute);
        string zodis;

        while (ss >> zodis) {
            string zodis_be_skyrybos;

            for (unsigned char c : zodis) {
                // ASCII raides
                if (std::isalpha(c)) {
                    zodis_be_skyrybos += std::tolower(c);
                }
                // bet kurie ne-ASCII baitai laikomi "raidžių" dalimi (UTF-8)
                else if (c & 0x80) {
                    zodis_be_skyrybos += c;
                }
                // visa kita (.,!?: ir t.t.) – praleidžiame
            }

            if (!zodis_be_skyrybos.empty()) {
                zodziu_skaicius[zodis_be_skyrybos] += 1;

                if (zodziu_eiluciu_nr[zodis_be_skyrybos].empty() ||
                    zodziu_eiluciu_nr[zodis_be_skyrybos].back() != eilutes_nr) {
                    zodziu_eiluciu_nr[zodis_be_skyrybos].push_back(eilutes_nr);
                }
            }
        }
    }
    F.close();

    ofstream G("rez.txt");
    G.imbue(utf8);
    /*G.imbue(utf8_locale);*/


    G << left << setw(20) << "Zodis"
      << left << setw(10) << "Kiekis"
      << left << setw(30) << "Eilutes" << endl << endl;

    for (const auto& duomuo : zodziu_skaicius) {
        if (duomuo.second > 1) {
            const string& zodis = duomuo.first;
            const vector<int>& eilutes = zodziu_eiluciu_nr[zodis];

            G << left << setw(20) << duomuo.first
              << left << setw(10) << duomuo.second;

            for (int nr : eilutes) {
                G << nr << " ";
            }
            G << endl;
        }
    }

    G.close();

    return 0;
}
