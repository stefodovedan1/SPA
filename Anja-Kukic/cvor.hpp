#pragma once
#include <memory>

template <typename T>
class Cvor {
private:
	T podatak;
	std::shared_ptr<Cvor<T>> sljedeci;

public:
	Cvor(const T& podatak) : podatak(podatak), sljedeci(nullptr) {}
	Cvor(T&& podatak) : podatak(std::move(podatak)), sljedeci(nullptr) {}

	Cvor(const Cvor<T>& other) = default;
	Cvor& operator=(const Cvor<T>& other) = default;
	Cvor(Cvor<T>&& other) noexcept = default;
	Cvor& operator=(Cvor<T>&& other) noexcept = default;
	~Cvor() = default;

	//getteri
	const T getPodatak() const { return podatak; }
	T& getPodatakRef() { return podatak; }
	std::shared_ptr<Cvor<T>> getSljedeci() const { return sljedeci; }

	//setteri
	void setPodatak(const T& noviPodatak) { podatak = noviPodatak; }
	void setSljedeci(std::shared_ptr<Cvor<T>> noviSljedeci) { sljedeci = noviSljedeci; }
};