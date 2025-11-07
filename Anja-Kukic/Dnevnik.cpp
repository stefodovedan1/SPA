#include "dnevnik.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <filesystem>

Dnevnik::Dnevnik() : nextId(1) {
	std::filesystem::create_directory("unosi");
	std::cout << "AAAAAAAAAAAAAAAAAAAAAAA\n";
	ucitajIzFajla();
}

Dnevnik::~Dnevnik() {
	sacuvajUFajl();
}

void Dnevnik::ucitajIzFajla() {
	std::ifstream ulazniFajl("dnevnik.txt");

	if (!ulazniFajl.is_open()) {
		//std::ofstream noviFajl("dnevnik.txt");
		//noviFajl.close();
		return;
	}

	std::string linija;

	while (std::getline(ulazniFajl, linija)) {
		std::istringstream iss(linija);
		int id;
		int vaznost;
		std::string opis;
		std::string datumStr;
		std::string vrijeme;
		std::string temp;

		if (std::getline(iss, temp, ',')) {
			id = std::stoi(temp);
			if (std::getline(iss, opis, ',') &&
				std::getline(iss, datumStr, ',') &&
				std::getline(iss, vrijeme, ',') &&
				iss >> vaznost) {
				std::cout << temp << " " << opis << " " << datumStr << " " << vrijeme << " " << vaznost << "\n";
				try {
					Datum datum(datumStr);

					std::string sadrzaj;
					std::ifstream contentFile("unosi/unos" + std::to_string(id) + ".txt");
					if (contentFile.is_open()) {
						std::stringstream contentSS;
						contentSS << contentFile.rdbuf();
						sadrzaj = contentSS.str();
						contentFile.close();
					}

					Unos novi(id, opis, datum, vrijeme, vaznost, sadrzaj);
					listaUnosa.dodajUnos(novi);
					prioritetniRedUnosa.dodaj(novi);
					std::cout << "Ucitani" << id << " aaaaaaaaa\n";
					nextId = std::max(nextId, id + 1);
				}
				catch (const std::exception& e) {
					std::cerr << "Greska pri ucitavanju unosa: " << e.what() << std::endl;
				}
			}
		}
	}
	ulazniFajl.close();
}

void Dnevnik::sacuvajUFajl() {
	std::ofstream file("dnevnik.txt");
	const Unos* trenutni = listaUnosa.getPrvi();

	while (trenutni != nullptr) {
		file << trenutni->getId() << ", "
			<< trenutni->getOpis() << ", "
			<< trenutni->getDatum().toString() << ", "
			<< trenutni->getVrijeme() << ", "
			<< trenutni->getVaznost() << "\n";
		trenutni = trenutni->getSljedeci();
	}
	file.close();
}

void Dnevnik::sacuvajSadrzajUnosa(const Unos& unos) {
	std::ofstream file("unosi/unos" + std::to_string(unos.getId()) + ".txt");
	if (file.is_open()) {
		file << unos.getSadrzaj();
		file.close();
	}
}

void Dnevnik::obrisiSadrzajUnosa(int id) {
	std::string file = "unosi/unos" + std::to_string(id + 1) + ".txt";
	if (std::filesystem::exists(file)) {
		std::filesystem::remove(file);
	}
}

std::string Dnevnik::getTrenutnoVrijeme() const {
    auto trenutno = std::time(nullptr);
    std::tm tmPtr;
#if defined(_MSC_VER)
    localtime_s(&tmPtr, &trenutno);
#else
    tmPtr = *std::localtime(&trenutno);
#endif
    std::ostringstream oss;
    oss << std::put_time(&tmPtr, "%H:%M");
    return oss.str();
}

bool Dnevnik::validirajVrijeme(const std::string& vrijeme) const {
	if (vrijeme.length() != 5 || vrijeme[2] != ':') return false;

	try {
		int sati = std::stoi(vrijeme.substr(0, 2));
		int minute = std::stoi(vrijeme.substr(3, 2));

		return (sati >= 0 && sati < 24 && minute >= 0 && minute < 60);
	}
	catch (...) {
		return false;
	}
}

void Dnevnik::dodajUnos() {
	std::cout << "Dodavanje novog unosa:\n";

	std::cin.ignore(); // Clear input buffer
	std::string opis;
	std::cout << "Unesite opis unosa: ";
	std::getline(std::cin, opis);

	std::string datumStr;
	do {
		std::cout << "Unesite datum (dd.mm.yyyy): ";
		std::getline(std::cin, datumStr);
		if(!Datum::validirajString(datumStr)) {
			std::cout << "Neispravan format datuma. Koristiti dd.mm.yyyy.\n";
		}
	} while (!Datum::validirajString(datumStr));

	Datum datum;
	try {
		datum = Datum(datumStr);
	}
	catch (const std::exception& e) {
		std::cerr << "Greska pri kreiranju datuma: " << e.what() << "\n";
		return;
	}

	std::string vrijeme;
	do {
		std::cout << "Unesite vrijeme (hh:mm): ";
		std::getline(std::cin, vrijeme);
		if (!validirajVrijeme(vrijeme)) {
			std::cout << "Neispravan format vremena. Koristiti hh:mm.\n";
		}
	} while (!validirajVrijeme(vrijeme));

	int vaznost;
	do {
		std::cout << "Unesite vaznost unosa [1-10]: ";
		std::cin >> vaznost;
		if(vaznost < 1 || vaznost > 10) {
			std::cout << "Vaznost mora biti izmedju 1 i 10.\n";
		}
	} while (vaznost < 1 || vaznost > 10);

	std::string sadrzaj;
	std::cin.ignore(); // Clear input buffer
	std::cout << "Unesite sadrzaj unosa: ";
	std::getline(std::cin, sadrzaj);

	Unos noviUnos(nextId++, opis, datum, vrijeme, vaznost, sadrzaj);
	listaUnosa.dodajUnos(noviUnos);
	prioritetniRedUnosa.dodaj(noviUnos);
	sacuvajSadrzajUnosa(noviUnos);
	sacuvajUFajl();

	std::cout << "Unos uspjesno dodat!\n";
}

void Dnevnik::undoUnos() {
	if (listaUnosa.isEmpty()) {
		std::cout << "Nema unosa za ponistiti.\n";
		return;
	}

	const Unos* zadnjiUnos = listaUnosa.getZadnji();
	if (zadnjiUnos != nullptr) {
		obrisiSadrzajUnosa(zadnjiUnos->getId());
		prioritetniRedUnosa.undoUnos(*zadnjiUnos);
	}
	listaUnosa.obrisiPosljednjiUnos();
	sacuvajUFajl();

	std::cout << "Zadnji unos uspjesno obrisan!\n";
} 

void Dnevnik::prikaziTop5Vaznosti() {
	prioritetniRedUnosa.prikaziTop5Vaznosti();
}

void Dnevnik::pregledDnevnika() {
	std::cin.ignore(); // Clear input buffer

	std::string datumStr;
	std::cout << "Unesite datum za pregled pojedinacnog unosa (dd.mm.yyyy): ili nazad za povratak";
	std::getline(std::cin, datumStr);

	if(datumStr == "nazad") {
		return;
	}

	if (!Datum::validirajString(datumStr)) {
		std::cout << "Neispravan format datuma. Koristiti dd.mm.yyyy.\n";
		return;
	}
	
	try {
		Datum trazeniDatum(datumStr);
		const Unos* unos = listaUnosa.getUnosPoDatumu(trazeniDatum);
		if (unos != nullptr) {
			unos->prikaziDetalje();
		} else {
			std::cout << "Nema unosa za zadati datum.\n";
		}
	}	catch (const std::exception& e) {
		std::cout << "Greska pri kreiranju datuma: " << e.what() << "\n";
	}
}

void Dnevnik::filtriranjeUnosa() {
	std::cin.ignore(); // Clear input buffer
	std::string pocetniDatumStr, krajnjiDatumStr;

	do {
		std::cout << "Unesite pocetni datum (dd.mm.yyyy): ";
		std::getline(std::cin, pocetniDatumStr);
		if(!Datum::validirajString(pocetniDatumStr)) {
			std::cout << "Neispravan format datuma. Koristiti dd.mm.yyyy.\n";
		}
	} while (!Datum::validirajString(pocetniDatumStr));

	do {
		std::getline(std::cin, krajnjiDatumStr);
		std::cout << "Unesite krajnji datum (dd.mm.yyyy): ";
		if(!Datum::validirajString(krajnjiDatumStr)) {
			std::cout << "Neispravan format datuma. Koristiti dd.mm.yyyy.\n";
		}
	} while (!Datum::validirajString(krajnjiDatumStr));
	
	try {
		Datum pocetniDatum(pocetniDatumStr);
		Datum krajnjiDatum(krajnjiDatumStr);

		if (krajnjiDatum < pocetniDatum) {
			std::cout << "Krajnji datum ne moze biti prije pocetnog datuma.\n";
			return;
		}

		listaUnosa.prikaziPoOpseguDatuma(pocetniDatum, krajnjiDatum);
	}
	catch (const std::exception& e) {
		std::cout << "Greska pri kreiranju datuma: " << e.what() << "\n";
	}
}

void Dnevnik::prikazMenija() {
	int izbor = 0;

	do {
		std::cout << "\nDigitalni Dnevnik\n";
		std::cout << "1. Dodaj novi unos\n";
		std::cout << "2. Ponisti zadnji unos - undo\n";
		std::cout << "3. Prikazi top 5 unosa po vaznosti\n";
		std::cout << "4. Pregled unosa po datumu\n";
		std::cout << "5. Filtriranje unosa po opsegu datuma\n";
		std::cout << "6. Izlaz\n";
		//std::cout << "Izaberite opciju (1-6): ";
		std::cin >> izbor;
		switch (izbor) {
		case 1:
			dodajUnos();
			break;
		case 2:
			undoUnos();
			break;
		case 3:
			prikaziTop5Vaznosti();
			break;
		case 4:
			pregledDnevnika();
			break;
		case 5:
			filtriranjeUnosa();
			break;
		case 6:
			std::cout << "Izlaz iz dnevnika.\n";
			break;
		default:
			std::cout << "Neispravan izbor. Pokusajte ponovo.\n";
		}
	} while (izbor != 6);
}