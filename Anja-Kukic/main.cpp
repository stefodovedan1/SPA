// Anja-Kukic.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "dnevnik.hpp"

int main()
{
    try {
		Dnevnik dnevnik;
		std::cout << "Dobrodosli u Digitalni Dnevnik!\n";
		dnevnik.prikazMenija();
	}
	catch (const std::exception& e) {
		std::cerr << "Greska: " << e.what() << std::endl;
	}
	catch (...) {
		std::cerr << "Nepoznata greska!" << std::endl;
	}
	return 0;
}