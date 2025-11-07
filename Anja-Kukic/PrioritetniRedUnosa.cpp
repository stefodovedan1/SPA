#include "prioritetniRedUnosa.hpp"
#include <stdexcept>
#include <iostream>

//bool PrioritetniRedUnosa::uporedi(const Unos& unos1, const Unos& unos2) const {
//	if (unos1.getVaznost() != unos2.getVaznost()) {
//		return unos1.getVaznost() > unos2.getVaznost();
//	}
//	
//	if(unos1.getDatum() != unos2.getDatum()) {
//		return unos1.getDatum() > unos2.getDatum();
//	}
//
//	return unos1.getVrijeme() > unos2.getVrijeme();
//}
//
//void PrioritetniRedUnosa::prosiriKapacitet() {
//	int noviKapacitet = kapacitet * 2;
//	Unos* noviHeap = new Unos[noviKapacitet];
//
//	for (int i = 0; i < velicina; i++) {
//		noviHeap[i] = heap[i];
//	}
//	delete[] heap;
//	heap = noviHeap;
//	kapacitet = noviKapacitet;
//}
//
//void PrioritetniRedUnosa::dodajGore(int i) {
//	while (i > 0) {
//		int roditelj = (i - 1) / 2;
//		if (uporedi(heap[i], heap[roditelj])) {
//			std::swap(heap[i], heap[roditelj]);
//			i = roditelj;
//		} else break;
//	}
//}
//
//void PrioritetniRedUnosa::dodajDole(int i) {
//	int lijevo, desno, najveci;
//	while (true) {
//		lijevo = 2 * i + 1;
//		desno = 2 * i + 2;
//		najveci = i;
//
//		if (lijevo < velicina && uporedi(heap[lijevo], heap[najveci])) {
//			najveci = lijevo;
//		}
//		if (desno < velicina && uporedi(heap[desno], heap[najveci])) {
//			najveci = desno;
//		}
//		if (najveci != i) {
//			std::swap(heap[i], heap[najveci]);
//			i = najveci;
//		} else break;
//	}
//}
//
//void PrioritetniRedUnosa::kopiraj(const PrioritetniRedUnosa& other) {
//	kapacitet = other.kapacitet;
//	velicina = other.velicina;
//	heap = new Unos[kapacitet];
//	for (int i = 0; i < velicina; i++) {
//		heap[i] = other.heap[i];
//	}
//}
//
//void PrioritetniRedUnosa::izbrisi() {
//	delete[] heap;
//	heap = nullptr;
//	kapacitet = 0;
//	velicina = 0;
//}
//
//PrioritetniRedUnosa::PrioritetniRedUnosa() 	: kapacitet(10), velicina(0) {
//	heap = new Unos[kapacitet];
//}
//
//PrioritetniRedUnosa::~PrioritetniRedUnosa() {
//	delete[] heap;
//}
//
//PrioritetniRedUnosa::PrioritetniRedUnosa(const PrioritetniRedUnosa& other) {
//	kopiraj(other);
//}
//
//PrioritetniRedUnosa& PrioritetniRedUnosa::operator=(const PrioritetniRedUnosa& other) {
//	if(this != &other) {
//		izbrisi();
//		kopiraj(other);
//	}
//	return *this;
//}
//
//PrioritetniRedUnosa::PrioritetniRedUnosa(PrioritetniRedUnosa&& other) noexcept
//	: heap(other.heap), kapacitet(other.kapacitet), velicina(other.velicina) {
//	other.heap = nullptr;
//	other.kapacitet = 0;
//	other.velicina = 0;
//}
//
//PrioritetniRedUnosa& PrioritetniRedUnosa::operator=(PrioritetniRedUnosa&& other) noexcept {
//	if (this != &other) {
//		izbrisi();
//		heap = other.heap;
//		kapacitet = other.kapacitet;
//		velicina = other.velicina;
//		other.heap = nullptr;
//		other.kapacitet = 0;
//		other.velicina = 0;
//	}
//	return *this;
//}
//
//void PrioritetniRedUnosa::dodaj(const Unos& unos) {
//	if (velicina == kapacitet) {
//		prosiriKapacitet();
//	}
//	heap[velicina] = unos;
//	dodajGore(velicina);
//	velicina++;
//}

 

void PrioritetniRedUnosa::kopiraj(const PrioritetniRedUnosa& other) {
	prvi = nullptr;
	if (other.prvi == nullptr) return;

	// Privremeni red
	auto trenutni = other.prvi;
	PrioritetniRedUnosa tempRed;

	//Kopiranje
	while (trenutni != nullptr) {
		tempRed.dodaj(trenutni->getPodatak());
		trenutni = trenutni->getSljedeci();
	}
}

void PrioritetniRedUnosa::izbrisi() {
	while (!isEmpty()) {
		ukloni();
	}
}

PrioritetniRedUnosa::PrioritetniRedUnosa() : prvi(nullptr) {}

PrioritetniRedUnosa::PrioritetniRedUnosa(const PrioritetniRedUnosa& other) : prvi(nullptr) {
	kopiraj(other);
}

PrioritetniRedUnosa& PrioritetniRedUnosa::operator=(const PrioritetniRedUnosa& other) {
	if (this != &other) {
		izbrisi();
		kopiraj(other);
	}
	return *this;
}

PrioritetniRedUnosa::~PrioritetniRedUnosa() {
	izbrisi();
}

PrioritetniRedUnosa::PrioritetniRedUnosa(PrioritetniRedUnosa&& other) noexcept : prvi(other.prvi) {
	other.prvi = nullptr;
}

PrioritetniRedUnosa& PrioritetniRedUnosa::operator=(PrioritetniRedUnosa&& other) noexcept {
	if (this != &other) {
		izbrisi();
		prvi = other.prvi; //prvi = std::move(other.prvi) ???
		other.prvi = nullptr;
	}
	return *this;
}

void PrioritetniRedUnosa::dodaj(const Unos& unos) {
	auto noviCvor = std::make_shared<Cvor<Unos>>(unos);

	if(prvi == nullptr) {
		prvi = noviCvor;
		return;
	}
	
	auto trenutni = prvi;
	std::shared_ptr<Cvor<Unos>> prethodni = nullptr;

	while (trenutni != nullptr && imaVisiPrioritet(trenutni->getPodatak(), unos)) {
		prethodni = trenutni;
		trenutni = trenutni->getSljedeci();
	}

	if (prethodni == nullptr) {
		noviCvor->setSljedeci(prvi);
		prvi = noviCvor;
	}
	else {
		noviCvor->setSljedeci(trenutni);
		prethodni->setSljedeci(noviCvor);
	}
}

bool PrioritetniRedUnosa::imaVisiPrioritet(const Unos& postojeci, const Unos& novi) {

	if (postojeci.getVaznost() > novi.getVaznost()) return true;

	if (postojeci.getVaznost() < novi.getVaznost()) return false;

	if (postojeci.getDatum() > novi.getDatum()) return true; 

	if (postojeci.getDatum() < novi.getDatum()) return false; 

	return pomocnaZaVrijeme(postojeci.getVrijeme()) > pomocnaZaVrijeme(novi.getVrijeme());
}

int PrioritetniRedUnosa::pomocnaZaVrijeme(const std::string& vrijeme) {
	//u formatu hh:mm
	try {
		int sati = std::stoi(vrijeme.substr(0, 2));
		int minute = std::stoi(vrijeme.substr(3, 2));
		return sati * 60 + minute;
	}
	catch (const std::exception& e) {
		return 0;
	}
}

Unos PrioritetniRedUnosa::ukloni() {
	if (isEmpty()) {
		throw std::runtime_error("Prioritetni red unosa je prazan. Nema unosa za ukloniti.");
	}

	Unos uklonjeniCvor = prvi->getPodatak();
	prvi = prvi->getSljedeci();
	return uklonjeniCvor;
}

bool PrioritetniRedUnosa::isEmpty() const {
	return prvi == nullptr;
}

void PrioritetniRedUnosa::prikaziTop5Vaznosti() const {
	std::cout << "Top 5 unosa po vaznosti:\n";

	if (isEmpty()) {
		std::cout << "Prioritetni red unosa je prazan.\n";
		return;
	}

	//Red je vec sortiran po vaznosti, pa po datumu
	//Prikazujemo prvih 5 elemenata iz reda

	auto trenutni = prvi;
	int count = 0;

	while(trenutni != nullptr && count < 5) {
		trenutni->getPodatak().prikaziInfo();
		trenutni = trenutni->getSljedeci();
		count++;
	}
}

void PrioritetniRedUnosa::undoUnos(const Unos& unos) {
	if (isEmpty()) return;

	auto trenutni = prvi;
	std::shared_ptr<Cvor<Unos>> prethodni = nullptr;

	while (trenutni != nullptr) {
		if (trenutni->getPodatak().getId() == unos.getId()) {
			if (prethodni != nullptr) {
				prethodni->setSljedeci(trenutni->getSljedeci());
			}
			return;
		}
		prethodni = trenutni;
		trenutni = trenutni->getSljedeci();
	}
}
