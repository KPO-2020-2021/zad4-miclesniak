#ifndef ROTACJA_HH
#define ROTACJA_HH
/**
 * @file Rotacja.hh
 * @brief plik zawierający definicję klasy Rotacja oraz jej metod
 * 
 * 
 */
#include "Wektor3D.hh"
#include "Macierz3x3.hh"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
/**
 * @brief Klasa Rotacja przechowująca dane w celu wielokrotnego obrotu prostopadłościanu
 * 
 * Klasa Rotacja została utworzona w celu zgromadzenia danych, odnośnie wielu macierzy rotacji,
 * a następnie utworzenie jednej, ostatecznej macierzy, która będzie wynikiem wszystkich obrotów
 * 
 */
class Rotacja
{
    /**
     * @brief Obiekt typu string przechowujący dane na temat osi obrotu
     * 
     */
    string _os;
    /**
     * @brief Obiekt typu vector przechowujący wartości double odpowiadające za kąt rotacji
     * 
     */
    vector<double> _kat;

public:
    /**
 * @brief Ustalenie końcowej macierzy rotacji
 * 
 * Metoda ma na celu utworzenie końcowej macierzy rotacji,
 * w oparciu o podane przez użytkownika osie oraz kąty następujących
 * po sobie macierzy
 * 
 * @return Macierz3x3 - Macierz wynikowa
 */
    Macierz3x3 Ustalkoniec();
    /**
 * @brief Dodanie elementu
 * 
 * Metoda ma na celu pobranie danych odnośnie kolejnych macierzy
 * oraz zapisanie ich do poszczególnych elementów klasy Rotacja
 * 
 * @param alfa - wartości kątow 
 * @param os - oznaczenia osi rotacji
 * @return Rotacja& - Obiekt klasy Rotacja przechowujący dane
 */
    Rotacja &dodaj(const double alfa, const char os)
    {
        _os.push_back(os);
        _kat.push_back(alfa);
        return *this;
    }
};

#endif