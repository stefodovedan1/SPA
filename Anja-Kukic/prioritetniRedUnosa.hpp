#pragma once
#include "unos.hpp"
#include "cvor.hpp"
#include <memory>

class PrioritetniRedUnosa {
private:
	std::shared_ptr<Cvor<Unos>> prvi;

	void kopiraj(const PrioritetniRedUnosa& other);
	void izbrisi();
	bool imaVisiPrioritet(const Unos& postojeci, const Unos& novi);
	int pomocnaZaVrijeme(const std::string& vrijeme);

public:
	PrioritetniRedUnosa();
	PrioritetniRedUnosa(const PrioritetniRedUnosa& other);
	PrioritetniRedUnosa& operator=(const PrioritetniRedUnosa& other);
	~PrioritetniRedUnosa();

	PrioritetniRedUnosa(PrioritetniRedUnosa&& other) noexcept;
	PrioritetniRedUnosa& operator=(PrioritetniRedUnosa&& other) noexcept;

	void dodaj(const Unos& unos);
	Unos ukloni();
	bool isEmpty() const;
	void prikaziTop5Vaznosti() const;
	void undoUnos(const Unos& unos);

};