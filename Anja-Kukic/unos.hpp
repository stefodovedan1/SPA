#pragma once
#include <string>
#include "datum.hpp"

class Unos {

private:
	int id;
	int vaznost;
	std::string opis;
	std::string vrijeme;
	std::string sadrzaj;
	Datum datum;

	Unos* sljedeci;
	Unos* prethodni;

public:
	Unos();
	Unos(int id, const std::string& opis, const Datum& datum, const std::string& vrijeme,
		int vaznost, const std::string& sadrzaj);
	Unos(const Unos& other) = default;
	Unos& operator=(const Unos& other) = default;
	~Unos() = default;

	Unos(Unos&& other) noexcept = default;
	Unos& operator=(Unos&& other) noexcept = default;

	//getteri
	int getId() const { return id; }
	int getVaznost() const { return vaznost; }
	const Datum getDatum() const { return datum; }
	const std::string& getOpis() const { return opis; }
	const std::string& getVrijeme() const { return vrijeme; }
	const std::string& getSadrzaj() const { return sadrzaj; }

	Unos* getSljedeci() const { return sljedeci; }
	Unos* getPrethodni() const { return prethodni; }

	//setteri
	void setOpis(const std::string& o) { opis = o; }
	void setVaznost(int v) { vaznost = v; }
	void setSadrzaj(const std::string& s) { sadrzaj = s; }

	void setSljedeci(Unos* noviSljedeci) { sljedeci = noviSljedeci; }
	void setPrethodni(Unos* noviPrethodni) { prethodni = noviPrethodni; }

	bool jeURasponu(const Datum& pocetni, const Datum& krajnji) const;
	void prikaziInfo() const;
	void prikaziDetalje() const;



};