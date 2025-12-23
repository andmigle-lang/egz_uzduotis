int main() {
	SetConsoleOutputCP(CP_UTF8); 
	SetConsoleCP(CP_UTF8); 
	locale::global(locale("en_US.UTF-8"));
	locale utf8("en_US.UTF-8");

	//1 ir 2 uzduotis - isvedama i ta pati faila rez.txt
	ifstream F("Vilnius.txt");
	F.imbue(utf8);

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

			for (unsigned char raide : zodis) {
				if (isalpha(raide)) {
					raide = tolower(raide);
					zodis_be_skyrybos += raide;
				}
				//ieskoma ne ASCII raidziu - t. y. tu, kuriose pirmas bitas yra 1 (bitine operacija)
				else if (raide & 0x80) {
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
	G.imbue(utf8);

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
    return 0;
}
