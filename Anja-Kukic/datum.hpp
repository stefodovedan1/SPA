#pragma once
#include <string>

class Datum {
private:
	int dan;
	int mjesec;
	int godina;

public:
	Datum();
	Datum(int dan, int mjesec, int godina);
	Datum(const std::string& datumStr);
	Datum(const Datum& other) = default;
	~Datum() = default;

	Datum(Datum&& other) noexcept = default;
	Datum& operator=(Datum&& other) noexcept = default;

	int getDan() const { return dan; }
	int getMjesec() const { return mjesec; }
	int getGodina() const { return godina; }

	std::string toString() const;
	bool isValid() const;
	static bool validirajString(const std::string& datumStr);

	bool operator==(const Datum& other) const;
	bool operator!=(const Datum& other) const; 
	bool operator<(const Datum& other) const;
	bool operator<=(const Datum& other) const;
	bool operator>(const Datum& other) const;
	bool operator>=(const Datum& other) const;

	static Datum getTrenutniDatum();
	bool jeUOpsegu(const Datum& pocetni, const Datum& krajnji) const;

};