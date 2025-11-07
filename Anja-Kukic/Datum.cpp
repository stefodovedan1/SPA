#include "datum.hpp"
#include <sstream>
#include <iomanip>
#include <stdexcept>

Datum::Datum() : dan(1), mjesec(1), godina(1999) {}

Datum::Datum(int dan, int mjesec, int godina) : dan(dan), mjesec(mjesec), godina(godina) {
	if (!isValid()) {
		throw std::invalid_argument("Nevalidan datum!");
	}
}

Datum::Datum(const std::string& datumString) {
	if(!validirajString(datumString)) {
		throw std::invalid_argument("Nevalidan format datuma! (Koristiti dd.mm.yyy.");
	}

	dan = std::stoi(datumString.substr(0, 2));
	mjesec = std::stoi(datumString.substr(3, 2));
	godina = std::stoi(datumString.substr(6, 4));

	if (!isValid()) {
		throw std::invalid_argument("Nevalidan datum!");
	}
}

std::string Datum::toString() const {
	std::ostringstream oss;
	oss << std::setw(2) << std::setfill('0') << dan << "."
		<< std::setw(2) << std::setfill('0') << mjesec << "."
		<< std::setw(4) << std::setfill('0') << godina << ".";
	return oss.str();
}

bool Datum::isValid() const {
	if (godina < 1999 || godina > 2100 || mjesec < 1 || mjesec > 12 || dan < 1 || dan > 31) return false;

	// Provjera broja dana u mjesecu
	if (mjesec == 2) {
		// Provjera prijestupne godine
		bool prijestupna = (godina % 4 == 0 && godina % 100 != 0) || (godina % 400 == 0);
		return dan <= (prijestupna ? 29 : 28);
	}

	if (mjesec == 4 || mjesec == 6 || mjesec == 9 || mjesec == 11) {
		return dan <= 30;
	}

	return dan <= 31;
}

bool Datum::validirajString(const std::string& datumString) {
	if (datumString.length() != 11 || datumString[2] != '.' || datumString[5] != '.' || datumString[10] != '.') return false;

	try {
		int d = std::stoi(datumString.substr(0, 2));
		int m = std::stoi(datumString.substr(3, 2));
		int g = std::stoi(datumString.substr(6, 4));

		Datum temp(d, m, g);
		return temp.isValid();
	}
	catch (...) {
		return false;
	}

	/*for (size_t i = 0; i < datumStr.length(); ++i) {
		if (i == 2 || i == 5) continue;
		if (!isdigit(datumStr[i])) return false;
	}
	return true;*/

}

bool Datum::operator==(const Datum& other) const {
	return dan == other.dan && mjesec == other.mjesec && godina == other.godina;
}

bool Datum::operator!=(const Datum& other) const {
	return !(*this == other);
}

bool Datum::operator<(const Datum& other) const {
	if (godina != other.godina) return godina < other.godina;
	if (mjesec != other.mjesec) return mjesec < other.mjesec;
	return dan < other.dan;
}

bool Datum::operator<=(const Datum& other) const {
	return *this < other || *this == other;
}

bool Datum::operator>(const Datum& other) const {
	return !(*this <= other);
}

bool Datum::operator>=(const Datum& other) const {
	return !(*this < other);
}

Datum Datum::getTrenutniDatum() {
	std::time_t vrijeme = std::time(nullptr);
	std::tm trenutno;
#ifdef _WIN32
	localtime_s(&trenutno, &vrijeme);
#else
	std::tm* pTrenutno = std::localtime(&vrijeme);
	if (pTrenutno)
		trenutno = *pTrenutno;
	else
		trenutno = std::tm(); // fallback to zeroed struct
#endif
	return Datum(trenutno.tm_mday, trenutno.tm_mon + 1, trenutno.tm_year + 1900);
}

bool Datum::jeUOpsegu(const Datum& pocetni, const Datum& krajnji) const {
	return *this >= pocetni && *this <= krajnji;
}