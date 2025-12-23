#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <cctype>
#include <iomanip>
#include <vector>
#include <set>
#include <regex>

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
using std::left;
using std::set;
using std::regex;
using std::smatch;
using std::ostream;
using std::cin;

int utf8_ilgis(const string& zodis);
void zodziu_ir_tarpu_spausdinimas(ostream& out, const string& zodis, int sk);

int main() {
	//1 ir 2 uzduotis - isvedama i ta pati faila rez.txt
	
	string failo_pavadinimas;
	ifstream F;
	while (true) {
		cout << "Iveskite failo pavadinima (Vilnius.txt): ";
		cin >> failo_pavadinimas;
		F.open(failo_pavadinimas);
		if (F) {
			break;
		}
		else {
			string pasirink;
			while (true) {
				cout << "Failo nepavyko atidaryti. Ar norite bandyti dar karta (rasykite 1), ar norite uzbaigti programa (rasykite 2)? ";
				cin >> pasirink;
				if (pasirink == "1") {
					break;
				}
				else if (pasirink == "2") {
					exit(0);
				}
				else {
					cout << "Neteisingas pasirinkimas. Bandykite dar karta." << endl;
				}
			}
		}
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

			for (size_t i = 0; i < zodis.size(); i++) {
				unsigned char raide = static_cast<unsigned char>(zodis[i]);

				//ASCII raide (vieno baito)
				if (raide < 128) {
					if (isalpha(raide)) {
						raide = tolower(raide);
						zodis_be_skyrybos += raide;
					}
				}
				//UTF‑8 dvieju baitu raides (lietuviskos, rusiskos ir t.t.) 
				//pirmas baitas turi forma 110xxxxx, t.y. (raide & 0xE0) == 0xC0
				else if ((raide & 0xE0) == 0xC0) {
					if (i + 1 < zodis.size()) {
						unsigned char raide2 = static_cast<unsigned char>(zodis[i + 1]);

						//antras (continuation) baitas uzsiraso forma 10xxxxxx
						if ((raide2 & 0xC0) == 0x80) {
							zodis_be_skyrybos += raide; //pirmas baitas
							zodis_be_skyrybos += raide2; //antras baitas
							i++; //praleidziame antra baita (continuation) ivesties cikle (kad nebutu perrasyta)
						}
					}
				}
				//3 baitu skyrybos zenklai ignoruojami
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

	G << left << setw(20) << "Zodis"
		<< left << setw(10) << "Kiekis"
		<< left << setw(30) << "Eilutes"<<"\n\n";

	for (const auto& duomuo : zodziu_skaicius) {

		if (duomuo.second > 1) {
			const string& zodis = duomuo.first;
			const vector<int>& eilutes = zodziu_eiluciu_nr[zodis];

			//G << left << setw(20) << duomuo.first;
			//cia padarytos atskiros funkcijos, nes kadangi ne ASCII raides (lietuviskos) uzima daugiau nei 1 baita, susigadina lygiuote
			zodziu_ir_tarpu_spausdinimas(G, duomuo.first, 20);
			G << left << setw(10) << duomuo.second;

			for (int nr : eilutes) {
				G << nr << " ";
			}
			G << endl;
		}
	}

	G.close();

	//3 uzduotis
	//istraukiame pletinius is failo
	set<string> pletiniai;
	ifstream T("URLs.txt");
	string pletinys;

	while (T >> pletinys) {
		for (int i = 0; i < pletinys.size(); i++)
			pletinys[i] = tolower(pletinys[i]);
		pletiniai.insert(pletinys);
	}
	T.close();

	//regex'as URL paieskai
	regex url_regex(R"((https?://)?(www\.)?[A-Za-z0-9\.-]+(/[A-Za-z0-9\./\-\_\?\=\&]*)?)");

	set<string> rasti_url;

	ifstream F2(failo_pavadinimas);
	string eilute_2;

	while (getline(F2, eilute_2)) {

		stringstream ss(eilute_2);
		string zodis_2;

		while (ss >> zodis_2) {

			smatch match;
			string url_kunas = "";

			//bandoma surasti URL dali is zodzio naudojant regex'a
			if (regex_search(zodis_2, match, url_regex)) {
				url_kunas = match.str(0);
			}
			else {
				continue; //nerastas URL
			}

			//padarome lowercase
			string lowercase_zodis_2 = url_kunas;
			for (int i = 0; i < lowercase_zodis_2.size(); i++)
				lowercase_zodis_2[i] = tolower(lowercase_zodis_2[i]);

			//tikriname ar tai yra URL pagal pletinius
			int paskutinio_tasko_indeksas = -1;
			for (int i = 0; i < lowercase_zodis_2.size(); i++) {
				if (lowercase_zodis_2[i] == '.') {
					paskutinio_tasko_indeksas = i;
				}
			}

			if (paskutinio_tasko_indeksas == -1) {
				continue; //jei nera tasko, tai ne URL
			}

			string pabaiga = "";
			for (int i = paskutinio_tasko_indeksas + 1; i < lowercase_zodis_2.size(); i++) {
				if (lowercase_zodis_2[i] == '/') break;
				pabaiga += lowercase_zodis_2[i];
			}

			if (pabaiga.empty()) {
				continue;
			}

			if (pletiniai.count(pabaiga)) {
				rasti_url.insert(url_kunas);
			}
		}
	}
	F2.close();

	//isvedame rastus url'us i faila
	ofstream U("rez_urls.txt");

	U << "Rasti URL adresai:\n\n";

	for (const auto& url : rasti_url)
		U << url << endl;

	U.close();
	cout << "Rezultatai isvesti i failus rez.txt ir rez_urls.txt" << endl;
	return 0;
}


int utf8_ilgis(const string& zodis) {
	int sk = 0;
	for (unsigned char raide : zodis) {
		//tikrinama, ar ne ASCII simbolis ir tada ar ne antras (continuation) baitas
		if ((raide & 0xC0) != 0x80) {
			sk++;
		}
	}
	return sk;
}

void zodziu_ir_tarpu_spausdinimas(ostream& out, const string& zodis, int sk) {
	int len = utf8_ilgis(zodis);
	out << zodis;
	for (int i = len; i < sk; i++)
		out << ' ';
}
