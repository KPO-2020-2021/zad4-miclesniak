#include "Rotacja.hh"
/**
 * @file Rotacja.cpp
 * @brief Plik zawiera rozwinięcie metod klasy Rotacja
 *  
 */

Macierz3x3 Rotacja::Ustalkoniec()
{
    Macierz3x3 Wynik(1);
    Macierz3x3 tmp;
    std::cout << Wynik << std::endl;
    for (size_t i = 0; i < _kat.size(); ++i)
    {
        tmp.setM(_kat[i], _os[i]);
        std::cout << tmp << std::endl;
        Wynik = Wynik * tmp;
        std::cout << Wynik << std::endl;
        tmp.clear();
    }
    _os.clear();
    _kat.clear();
    return Wynik;
}