//#include "stekUnosa.hpp"
//#include <stdexcept>
//#include <iostream>
//
//void StekUnosa::kopiraj(const StekUnosa& other) {
//	vrh = nullptr;
//	if (other.vrh == nullptr) return;
//
//	// Privremeni stek
//	auto trenutni = other.vrh;
//	StekUnosa tempStek;
//
//	while (trenutni != nullptr) {
//		tempStek.push(trenutni->getPodatak());
//		trenutni = trenutni->getSljedeci();
//	}
//
//	//Kopiranje iz privremenog steka u originalni redoslijed
//	trenutni = tempStek.vrh;
//	while (trenutni != nullptr) {
//		push(trenutni->getPodatak());
//		trenutni = trenutni->getSljedeci();
//	}
//}
//
//void StekUnosa::izbrisi() {
//	while (!isEmpty()) {
//		pop();
//	}
//}
//
//StekUnosa::StekUnosa() : vrh(nullptr) {}
//
//StekUnosa::StekUnosa(const StekUnosa& other) {
//	kopiraj(other);
//}
//
//StekUnosa& StekUnosa::operator=(const StekUnosa& other) {
//	if (this != &other) {
//		izbrisi();
//		kopiraj(other);
//	}
//	return *this;
//}
//
//StekUnosa::~StekUnosa() {
//	izbrisi();
//}
//
//StekUnosa::StekUnosa(StekUnosa&& other) noexcept : vrh(other.vrh) {
//	other.vrh = nullptr;
//}
//
//StekUnosa& StekUnosa::operator=(StekUnosa&& other) noexcept {
//	if (this != &other) {
//		izbrisi();
//		vrh = other.vrh;
//		other.vrh = nullptr;
//	}
//	return *this;
//}
//
//void StekUnosa::push(const Unos& unos) {
//	auto noviCvor = std::make_shared<Cvor<Unos>>(unos);
//	noviCvor->setSljedeci(vrh);
//	vrh = noviCvor;
//}
//
//Unos StekUnosa::pop() {
//	if (isEmpty()) {
//		throw std::runtime_error("Stek je prazan. Nema elemenata za ukloniti.");
//	}
//
//	Unos podatak = vrh->getPodatak();
//	vrh = vrh->getSljedeci();
//	return podatak;
//}
//
//bool StekUnosa::isEmpty() const {
//	return vrh == nullptr;
//}
//
