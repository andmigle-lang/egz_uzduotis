#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <cctype>
#include <locale>
#include <iomanip>
#include <vector>

using std::ifstream;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::stringstream;
using std::ofstream;
using std::tolower;
using std::right;
using std::setw;
using std::fixed;
using std::vector;

int main() {

	ifstream F("Vilnius.txt");
	if (!F) {
		cout << "Failas neatidarytas" << endl;
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

			for (char raide : zodis) {
				if (isalpha(raide)) {
					raide = tolower(raide);
					zodis_be_skyrybos += raide;
				}
			}
			if (zodis_be_skyrybos != "") {
				zodziu_skaicius[zodis_be_skyrybos]+=1;

				if (zodziu_eiluciu_nr[zodis_be_skyrybos].size() == 0 || zodziu_eiluciu_nr[zodis_be_skyrybos].back() != eilutes_nr) {
					zodziu_eiluciu_nr[zodis_be_skyrybos].push_back(eilutes_nr);
				}
			}
		}
	}
	F.close();
	ofstream G("rez.txt");
	G << right << setw(15) << "Zodis" << right << setw(15) << "Kiekis" << right << setw(20) << "Eilutes" << endl;
	for (const auto& duomuo : zodziu_skaicius) {

		if (duomuo.second > 1) {
			const string& zodis = duomuo.first;
			const vector<int>& eilutes = zodziu_eiluciu_nr[zodis];
			G << right << setw(15) << duomuo.first << right << setw(15) << duomuo.second;
			for (int nr : eilutes) {
				G << nr << " ";
			}
			G << endl;

		}
	}
	G.close();

	return 0;
}
