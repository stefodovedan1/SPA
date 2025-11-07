#include "unos.hpp"
#include <iostream>

Unos::Unos() : id(0), vrijeme("00:00"), vaznost(0), sljedeci(nullptr), prethodni(nullptr) {}

Unos::Unos(int id, const std::string& opis, const Datum& datum, const std::string& vrijeme,
    int vaznost, const std::string& sadrzaj)
    : id(id), opis(opis), datum(datum), vrijeme(vrijeme),
    vaznost(vaznost), sadrzaj(sadrzaj), sljedeci(nullptr), prethodni(nullptr) {
}

//Unos::Unos(const Unos& other) : 
//	id(other.id), 
//	opis(other.opis), 
//	datum(other.datum), 
//	vrijeme(other.vrijeme), 
//	vaznost(other.vaznost), 
//	sadrzaj(other.sadrzaj), 
//	sljedeci(nullptr), 
//	prethodni(nullptr) {}

//Unos::Unos(Unos&& other) noexcept
//    : id(std::move(other.id)),
//    opis(std::move(other.opis)),
//    datum(std::move(other.datum)),
//    vrijeme(std::move(other.vrijeme)),
//    vaznost(std::move(other.vaznost)),
//    sadrzaj(std::move(other.sadrzaj)),
//    sljedeci(other.sljedeci),
//    prethodni(other.prethodni) {
//    other.sljedeci = nullptr;
//    other.prethodni = nullptr;
//}

//Unos& Unos::operator=(Unos&& other) noexcept {
//    if (this != &other) {
//        id = std::move(other.id);
//        opis = std::move(other.opis);
//        datum = std::move(other.datum);
//        vrijeme = std::move(other.vrijeme);
//        vaznost = std::move(other.vaznost);
//        sadrzaj = std::move(other.sadrzaj);
//        sljedeci = other.sljedeci;
//        prethodni = other.prethodni;
//
//        other.sljedeci = nullptr;
//        other.prethodni = nullptr;
//    }
//    return *this;
//}

bool Unos::jeURasponu(const Datum& pocetni, const Datum& krajnji) const {
    return datum.jeUOpsegu(pocetni, krajnji);
}

void Unos::prikaziInfo() const {
    std::cout << "Datum: " << datum.toString()
        << ", Vrijeme: " << vrijeme
        << ", Vaznost: " << vaznost
        << ", Opis: " << opis << std::endl;
}

void Unos::prikaziDetalje() const {
    std::cout << "\nDetalji unosa\n";
    std::cout << "ID: " << id << std::endl;
    std::cout << "Datum: " << datum.toString() << std::endl;
    std::cout << "Vrijeme: " << vrijeme << std::endl;
    std::cout << "Vaznost: " << vaznost << std::endl;
    std::cout << "Opis: " << opis << std::endl;
    std::cout << "Sadrzaj: " << sadrzaj << std::endl;
}