#pragma once

#ifndef DNEVNIK_H
#define DNEVNIK_H

#include <string>
#include <ctime>	
#include "listaUnosa.hpp"
#include "stekUnosa.hpp"
#include "prioritetniRedUnosa.hpp"

class Dnevnik {
private:
	ListaUnosa listaUnosa;
	//StekUnosa stekUnosa;
	PrioritetniRedUnosa prioritetniRedUnosa;
	int nextId;

	void ucitajIzFajla();
	void sacuvajUFajl();
	void sacuvajSadrzajUnosa(const Unos& unos);
	void obrisiSadrzajUnosa(int id);
	std::string getTrenutnoVrijeme() const;
	bool validirajVrijeme(const std::string& vrijeme) const;

public:
	Dnevnik();
	~Dnevnik();

	Dnevnik(const Dnevnik&) = delete;
	Dnevnik& operator=(const Dnevnik&) = delete;
	Dnevnik(Dnevnik&&) = delete;
	Dnevnik& operator=(Dnevnik&&) = delete;

	void dodajUnos(); //upis unosa sa standardnog ulaza na listu, stek, prioritetni red i u fajl
	void undoUnos(); //birsanje iz liste
	void prikaziTop5Vaznosti(); //prikaz iz prioritetnog reda
	void pregledDnevnika(); //prikaz za odredjeni datum
	void filtriranjeUnosa(); //prikaz unosa u opsegu datuma
	void prikazMenija(); //meni koristenjem switcha
};

#endif 
