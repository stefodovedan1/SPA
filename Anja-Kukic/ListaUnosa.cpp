//#include "dnevnik.hpp"
#include "listaUnosa.hpp"
#include <iostream>
#include <iomanip>

void ListaUnosa::kopiraj(const ListaUnosa& other) {
	prvi = zadnji = nullptr;
	brojUnosa = 0;

	Unos* trenutni = other.prvi;
	while (trenutni != nullptr) {
		dodajUnos(*trenutni);
		trenutni = trenutni->getSljedeci();
	}
}

void ListaUnosa::izbrisi() {
	Unos* trenutni = prvi;
	while (trenutni != nullptr) {
		Unos* sljedeci = trenutni->getSljedeci();
		delete trenutni;
		trenutni = sljedeci;
	}
	prvi = zadnji = nullptr;
	brojUnosa = 0;
}

ListaUnosa::ListaUnosa() : prvi(nullptr), zadnji(nullptr), brojUnosa(0) {}

ListaUnosa::ListaUnosa(const ListaUnosa& other) : prvi(nullptr), zadnji(nullptr), brojUnosa(0) {
	kopiraj(other);
}

ListaUnosa& ListaUnosa::operator=(const ListaUnosa& other) {
	if (this != &other) {
		izbrisi();
		kopiraj(other);
	}
	return *this;
}

ListaUnosa::~ListaUnosa() {
	izbrisi();
}

ListaUnosa::ListaUnosa(ListaUnosa&& other) noexcept	: prvi(other.prvi), zadnji(other.zadnji), brojUnosa(other.brojUnosa) {
	other.prvi = nullptr;
	other.zadnji = nullptr;
	other.brojUnosa = 0;
}

ListaUnosa& ListaUnosa::operator=(ListaUnosa&& other) noexcept {
	if (this != &other) {
		izbrisi();

		prvi = other.prvi;
		zadnji = other.zadnji;
		brojUnosa = other.brojUnosa;

		other.prvi = nullptr;
		other.zadnji = nullptr;
		other.brojUnosa = 0;
	}
	return *this;
}

void ListaUnosa::dodajUnos(const Unos& unos) {
	Unos* noviUnos = new Unos(unos);
	noviUnos->setSljedeci(nullptr);
	noviUnos->setPrethodni(zadnji);

	if (zadnji == nullptr) {
		prvi = zadnji = noviUnos;
	} else {
		zadnji->setSljedeci(noviUnos);
		zadnji = noviUnos;
	}
	brojUnosa++;
}

//void ListaUnosa::obrisiUnos(int id) {
//	Unos* trenutni = prvi;
//	while (trenutni != nullptr) {
//		if (trenutni->getId() == id) {
//			if (trenutni->getPrethodni() != nullptr) {
//				trenutni->getPrethodni()->setSljedeci(trenutni->getSljedeci());
//			} else {
//				prvi = trenutni->getSljedeci();
//			}
//			if (trenutni->getSljedeci() != nullptr) {
//				trenutni->getSljedeci()->setPrethodni(trenutni->getPrethodni());
//			} else {
//				zadnji = trenutni->getPrethodni();
//			}
//			delete trenutni;
//			brojUnosa--;
//			return;
//		}
//		trenutni = trenutni->getSljedeci();
//	}
//}

void ListaUnosa::obrisiPosljednjiUnos() {
	if (zadnji == nullptr) return;

	Unos* zaBrisanje = zadnji;
	if (prvi == zadnji) {
		prvi = zadnji = nullptr;
	} else {
		zadnji = zadnji->getPrethodni();
		zadnji->setSljedeci(nullptr);
	}
	delete zaBrisanje;
	brojUnosa--;
}


const Unos* ListaUnosa::getUnosPoDatumu(const Datum& datum) const {
	const Unos* trenutni = prvi;
	while (trenutni != nullptr) {
		if (trenutni->getDatum() == datum) {
			return trenutni;
		}
		trenutni = trenutni->getSljedeci();
	}
	return nullptr;
}

void ListaUnosa::prikaziSveUnose() const {
	const Unos* trenutni = prvi;
	std::cout << "Svi unosi u Dnevniku: \n";

	if(trenutni == nullptr) {
		std::cout << "Nema unosa u dnevniku.\n";
		return;
	}
	 


	while (trenutni != nullptr) {
		trenutni->prikaziInfo();
		trenutni = trenutni->getSljedeci();
	}
}

void ListaUnosa::prikaziPoOpseguDatuma(const Datum& pocetniDatum, const Datum& krajnjiDatum) const {
	const Unos* trenutni = prvi;
	std::cout << "\n Filtrirani unosi u opsegu od " << pocetniDatum.toString() << " do " << krajnjiDatum.toString() << ":\n";
	bool pronadjen = false;

	while (trenutni != nullptr) {
		if (trenutni->jeURasponu(pocetniDatum, krajnjiDatum)) {
			trenutni->prikaziInfo();
			pronadjen = true;
		}
		trenutni = trenutni->getSljedeci();
	}

	if(!pronadjen) {
		std::cout << "Nema unosa u zadatom opsegu datuma.\n";
	}
}

int ListaUnosa::getBrojUnosa() const {
	return brojUnosa;
}
