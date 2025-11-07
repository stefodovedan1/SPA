#pragma once
#include "unos.hpp"
#include "datum.hpp"

//class Unos;

//Klasa Liste unosa
class ListaUnosa {
private:
	Unos* prvi;
	Unos* zadnji;
	int brojUnosa;

	void kopiraj(const ListaUnosa& other);
	void izbrisi();

public:
	ListaUnosa();
	ListaUnosa(const ListaUnosa& other);
	ListaUnosa& operator=(const ListaUnosa& other);
	~ListaUnosa();

	ListaUnosa(ListaUnosa&& other) noexcept;
	ListaUnosa& operator=(ListaUnosa&& other) noexcept;


	void dodajUnos(const Unos& unos);
	void obrisiPosljednjiUnos();

	const Unos* getPrvi() { return prvi; }
	const Unos* getZadnji() { return zadnji; }
	const Unos* getUnosPoDatumu(const Datum& datum) const;
	

	void prikaziSveUnose() const;
	void prikaziPoOpseguDatuma(const Datum& pocetniDatum, const Datum& krajnjiDatum) const;
	int getBrojUnosa() const;
	bool isEmpty() const { return brojUnosa == 0; }

	//void urediUnos(int id, const std::string& noviOpis, int novaVaznost);
	//int dohvatiBrojUnosa() const;
};