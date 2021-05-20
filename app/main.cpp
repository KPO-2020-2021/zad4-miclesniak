#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "../tests/doctest/doctest.h"
#endif
#include <iostream>
#include <iomanip>
#include <fstream>
#include "../include/Wektor3D.hh"
#include "../include/Macierz3x3.hh"
#include "../include/Prostopadloscian.hh"
#include "../include/Rotacja.hh"
#include "../include/lacze_do_gnuplota.hh"

using namespace std;

#define DL_BOK 150
#define KR_BOK 100
#define POP_BOK 70

/**
 * @file main.cpp 
 * 
 *
 * @brief Główny plik programu
 * 
 */

int main()
{      
       

       // zmienne niezbedne do funkcjonowania programu
       Macierz3x3 macierz;         //Macierz obrotu
       Wektor3D wektor;            // Wektor przesuniecia
       Prostopadloscian Prost;     //Prostopadloscian
       Rotacja rot;                // Skladowe macierzy obrotu
       double Tab[12];             // tablica przechowujaca dlugosci bokow prostokata
       char wyb, os;               // wybor menu
       double kat;                 // kat obrotu
       int il;                     // ilosc powtorzen obrotu
       int obr = 0;                // zmienna sluzaca do sygnalizowania czy zostala utworzona macierz obrotu
       PzG::LaczeDoGNUPlota Lacze; // Ta zmienna jest potrzebna do wizualizacji
                                   // rysunku prostokata
       //-------------------------------------------------------
       //  Wspolrzedne wierzcholkow beda zapisywane w pliku "prostokat.dat"
       //  Ponizsze metody powoduja, ze dane z pliku beda wizualizowane
       //  na dwa sposoby:
       //   1. Rysowane jako linia ciagl o grubosci 2 piksele
       //
       Lacze.DodajNazwePliku("prostopadloscian.dat", PzG::RR_Ciagly, 2);
       //
       //  Ustawienie trybu rysowania 3D, tzn. rysowany zbiór punktów
       //  znajduje się na wspólnej płaszczyźnie. Z tego powodu powoduj
       //  jako wspolrzedne punktow podajemy x,y,z.
       //
       Lacze.ZmienTrybRys(PzG::TR_3D);

       // Ustawienie zakresow poszczegolnych osi
       Lacze.UstawZakresY(-300, 300);
       Lacze.UstawZakresX(-300, 300);
       Lacze.UstawZakresZ(-300, 300);

       Prost.Inicjalizuj(0, KR_BOK, DL_BOK, POP_BOK);
       Prost.Porownaj(Tab);
       cout << endl;
       cout << "o - obrot bryly o zadana sekwencje katow\n";
       cout << "t - powtorzenie poprzedniego obrotu\n";
       cout << "r - wyswietlenie macierzy rotacji\n";
       cout << "p - przesuniecie prostopadloscianu o zadany wektor\n";
       cout << "w - wyswietlenie wspolrzednych wierzcholkow\n";
       cout << "s - sprawdzenie dlugosci przeciwleglych bokow\n";
       cout << "m - wyswietl menu\n";
       cout << "n - narysuj prostopadloscian\n";
       cout << "k - koniec dzialania programu\n";

       while (wyb != 'k')
       {

              cout << "\nTwoj wybor? (m - menu) > ";
              cin >> wyb;

              switch (wyb)
              {
              case 'o':
                     cout << "Podaj sekwencje oznaczen osi oraz katy obrotu w stopniach\n";
                     cout << "Aby przerwac pobieranie, podaj znak kropki\n";
                     while (os != '.')
                     {
                            cin >> os;
                            if (os != '.')
                            {
                                   cin >> kat;
                                   if (os == 'x' || os == 'y' || os == 'z')
                                   {
                                          rot = rot.dodaj(kat, os);
                                   }
                                   else
                                   {
                                          cout << ":( Bledne oznaczenie osi. Dopuszczalne znaki to: x y z .\n";
                                          cout << ":( Sprobuj jeszcze raz.\n";
                                          cin.clear();
                                          cin.ignore(99999, '\n');
                                   }
                            }
                     }
                     cout << "Ile razy operacja obrotu ma byc powtorzona?\n";
                     cin >> il;
                     macierz = rot.Ustalkoniec();
                     for (int i = 0; i < il; ++i)
                            Prost.Rotacja(macierz);
                     Prost.Porownaj(Tab);
                     cin.clear();
                     os = ' ';
                     obr = 1;
                     break;

              case 't':
                     if (obr == 1)
                     {
                            for (int i = 0; i < il; ++i)
                                   Prost.Rotacja(macierz);
                            Prost.Porownaj(Tab);
                     }
                     else
                            cout << "Nie podano informacji na temat obrotu\n";
                     break;

              case 'r':
                     if (obr == 1)
                            cout << endl
                                 << macierz << endl;
                     else
                            cout << "Macierz rotacji nie zostala podana\n";
                     break;

              case 's':
                     Prost.Porownaj(Tab);
                     break;

              //wczytanie wektora oraz przesuniecie prostokata
              case 'p':
                     cout
                         << "Wprowadz wspolrzedne wektora translacji w postaci trzech liczb\n";
                     cout << "tzn. wspolrzednej x, y oraz z.\n";
                     cin >> wektor;
                     while (cin.fail())
                     {
                            cerr << "Blad, zapisu Wektora. Sprobuj jeszcze raz.\n";
                            cout << "Wprowadz wspolrzedne wektora translacji w postaci trzech liczb\n";
                            cout << "tzn. wspolrzednej x, y oraz z.\n";
                            cin.clear();
                            cin.ignore(99999, '\n');
                            cin >> wektor;
                     }
                     Prost.Przesun(wektor);
                     break;

              case 'w':
                     cout << Prost << endl;
                     break;

              // Zaktualizowanie pliku oraz narysowanie prostokata
              case 'n':
                     if (!Prost.ZapisDoPliku("prostopadloscian.dat"))
                            cerr << "Niepoprawny zapis do pliku!\n";
                     Lacze.Rysuj(); // <- Tutaj gnuplot rysuje, to co zapisaliśmy do pliku
                     cout << "Naciśnij ENTER, aby kontynuowac" << endl;
                     cin.ignore(100000, '\n');
                     break;
                     
              case 'm':
                     cout << "o - obrot bryly o zadana sekwencje katow\n";
                     cout << "t - powtorzenie poprzedniego obrotu\n";
                     cout << "r - wyswietlenie macierzy rotacji\n";
                     cout << "p - przesuniecie prostopadloscianu o zadany wektor\n";
                     cout << "w - wyswietlenie wspolrzednych wierzcholkow\n";
                     cout << "s - sprawdzenie dlugosci przeciwleglych bokow\n";
                     cout << "m - wyswietl menu\n";
                     cout << "n - narysuj prostopadloscian\n";
                     cout << "k - koniec dzialania programu\n";
                     break;

              case 'k':
                     continue;
                     break;
              default:
                     cout << "Podano niepoprawna opcje!\n";
                     break;
              }
       }
      
}
