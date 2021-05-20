#ifndef PROSTOKAT_HH
#define PROSTOKAT_HH

#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
#include "Wektor3D.hh"
#include "Macierz3x3.hh"
#define ROZM_P 8
#define IL_B 12

/**
 * @file Prostopadloscian.hh
 * 
 * @brief Definicja klasy Prostopadloscian oraz deklaracja jej metod
 * 
 */

/**
 * @brief Klasa modeluje pojęcie prostopadłościanu
 * 
 */
class Prostopadloscian
{
  /**
   * @brief Tablica obiektów Wektor3D zawierająca wierzchołki figury
   * 
   */
  Wektor3D _wsp[ROZM_P];

public:
  /**
 * @brief Konstruktor domyślny
 * 
 */
  Prostopadloscian()
  {
    for (Wektor3D &wek : _wsp)
      wek = Wektor3D();
  }

  /**
   * @brief Przeciążenie operatora indeksowania
   * 
   * Przeciążenie operatora w celu użycia w funkcjach bez modyfikacji elementu.
   * 
   * @param[in] i - indeks tablicy obiektów klasy Wektor3D
   * @return Wektor3D - Wektor3D znajdujący się pod danym indeksem 
   */
  Wektor3D operator[](const int i) const
  {
    return _wsp[i];
  }

  /**
   * @brief Przeciążenie operatora indeksowania
   * 
   * Przeciążenie operatora w celu użycia w funkcjach modyfikujących element.
   * 
   * @param[in] i - indeks tablicy obiektów klasy Wektor3D
   * @return Wektor3D& - Wektor3D znajdujący się pod danym indeksem, jest on modyfikowalny
   */
  Wektor3D &operator[](const int i)
  {
    return _wsp[i];
  }

  /**
   * @brief Przesunięcie prostopadłościanu
   * 
   * Metoda przesuwa współrzędne prostopadłościanu o zadany wektor,
   * modyfikuje prostopadłościan
   * 
   * @param[in] wek - wektor przesunięcia 
   */
  void Przesun(const Wektor3D &wek)
  {
    for (int i = 0; i < ROZM_P; i++)
      _wsp[i] = _wsp[i] + wek;
  }

  /**
   * @brief Rotacja prostopadłościanu
   * 
   * Metoda wykonuje rotację współrzędnych prostopadłościanu przy
   * pomocy macierzy rotacji.
   * 
   * @param[in] macierz - macierz rotacji 
   */
  void Rotacja(const Macierz3x3 &macierz)
  {
    for (int i = 0; i < ROZM_P; i++)
      _wsp[i] = _wsp[i] * macierz;
  }

  /**
   * @brief Zapisanie prostopadłościanu do strumienia
   * 
   * Metoda zapisuje współrzedne prostopadłościanu do strumienia
   * aby następnie mogły one zostać zapisane do pliku
   * 
   * @param[in] Str - strumień wyjściowy, do którego mają zostać
   * zapisane kolejne współrzędne.
   */
  void ZapisDoStr(std::ostream &Str) const;

  /**
   * @brief Zapisanie prostopadłościanu do pliku
   * 
   * Metoda zapisująca współrzędne prostopadłościanu do pliku, z ktorego
   * dane odczyta program gnuplot i narysuje je w swoim oknie graficznym.
   * 
   * @param[in] NazwaPliku - - nazwa pliku, do którego zostana zapisane wspolrzędne punktów.
   * @return true - gdy operacja zapisu powiodla sie
   * @return false - w wypadku przeciwnym
   */
  bool ZapisDoPliku(const char *NazwaPliku) const;

  /**
   * @brief Zapisanie bokow prostopadloscianu
   * 
   * Metoda wykorzystana w \link Prostopadloscian::Porownaj \endlink
   * w celu zapisania dlugosci bokow prostokata do tablicy typu double.
   * 
   * @param[in] Tab - tablica liczb typu double, w ktorej zapisywane sa
   *dlugosci odpowiednich bokow, po kolei na osiach X, Y, Z
   */
  void ZapiszBoki(double Tab[IL_B]) const;

  /**
   * @brief Zapisanie bokow z osi X prostopadloscianu
   * 
   * Metoda zapisujaca w tablicy typu double dlugosci bokow lezacych na osi X
   * 
   * @param[in] Tab - tablica liczb typu double, w ktorej zapisywane sa
   *dlugosci odpowiednich bokow, po kolei na osiach X, Y, Z
   */
  void ZapiszBokiX(double Tab[IL_B]) const;

  /**
   * @brief Zapisanie bokow z osi Y prostopadloscianu
   * 
   * Metoda zapisujaca w tablicy typu double dlugosci bokow lezacych na osi Y
   * 
   * @param[in] Tab - tablica liczb typu double, w ktorej zapisywane sa
   *dlugosci odpowiednich bokow, po kolei na osiach X, Y, Z
   */
  void ZapiszBokiY(double Tab[IL_B]) const;

  /**
   * @brief Zapisanie bokow z osi Z prostopadloscianu
   * 
   * Metoda zapisujaca w tablicy typu double dlugosci bokow lezacych na osi Z
   * 
   * @param[in] Tab - tablica liczb typu double, w ktorej zapisywane sa
   *dlugosci odpowiednich bokow, po kolei na osiach X, Y, Z
   */
  void ZapiszBokiZ(double Tab[IL_B]) const;

  /**
   * @brief Wyswietlenie dlugosci bokow prostopadloscianu
   * 
   * Metoda wykorzystana w metodzie Prostopadloscian::Porownaj
   * ma za zadanie zwiekszenie czytelnosci kodu oraz jego skrocenie
   * Wyswietla ona wartosci odpowiednich przeciwleglych bokow figury.
   * 
   * @param[in] nr_boku - parametr odpowiadajacy za odpowiednie boki, ktore
   * zostana porownane 
   * @param[in] Tab - tablica liczb typu double przechowujaca wartosci odpowiednich bokow
   */
  void Wyswietlboki(const int nr_boku, double Tab[IL_B]) const;

  /**
   * @brief Porownanie dlugosci bokow prostopadloscianu
   * 
   * Metoda porownujaca dlugosci przeciwleglych bokow oraz
   * wyswietlajaca ich wartosc oraz informacje czy sa sobie rowne
   * 
   * @param[in] Tab - tablica liczb typu double, przechowujaca wartosci odpowiednich bokow
   */
  void Porownaj(double Tab[IL_B]) const;

  /**
 * @brief Sprawdzenie długości boków prostopadłościanu
 * 
 * Metoda pobiera z tablicy zapisane długości boków prostokąta, a następnie
 * porównuje odpowiednie boki ze sobą, dając informację czy są sobie równe
 * 
 * @param[in] nr_boku - parametr odpowiadający za to, które boki aktualnie
 * zostaną porównane 
 * @param[in] Tab - Tablica przechowująca wartości długości boków 
 * @return true - gdy boki są równe
 * @return false - gdy boki nie są sobie równe
 */
  bool Sprawdzboki(const int nr_boku, double Tab[IL_B]) const;

  /**
   * @brief Utworzenie prostopadłościanu
   * 
   * Metoda, która tworzy prostopadłościan z podanymi parametrami
   * 
   * @param[in] wsp - współrzędna X, Y, Z pierwszego wierzchołka 
   * @param[in] bokx - długość boków na osi x 
   * @param[in] boky - długość boków na osi y 
   * @param[in] bokz - długość boków na osi z 
   */
  void Inicjalizuj(const double wsp, const double bokx,
                   const double boky, const double bokz);
};

/**
 * @brief Przeciazenie operatora bitowego w celu wyswietlenia prostopadloscianu
 * 
 * Przeciazenie operatora bitowego w celu wyswietlenia
 * wierzcholkow prostopadloscianu
 * Dane sa odpowiednio sformatowane,
 * tzn. przyjęto notację stałoprzecinkową z dokładnością do 10 miejsca po przecinku.
 * Szerokość wyświetlanego pola to 16 miejsc, sposób wyrównywania - do prawej strony.
 * 
 * @param[in] Pr - Prostopadloscian, ktorego wierzcholki maja zostac wyswietlone
 * @param[in] out - Strumien wyjsciowy, na ktorym ma zostac wyswietlony prostopadloscian
 * 
 * @return ostream - Strumien wyjsciowy
 * */
std::ostream &operator<<(std::ostream &out, const Prostopadloscian &Pr);

#endif
