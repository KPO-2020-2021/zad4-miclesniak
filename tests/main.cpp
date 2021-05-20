#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../tests/doctest/doctest.h"
#include "../include/Wektor3D.hh"
#include "../include/Macierz3x3.hh"
#include "../include/Prostopadloscian.hh"
#include "../include/Rotacja.hh"

TEST_CASE("Test Konstruktora Bezparametrycznego Wektora")
{
    Wektor3D tmp;
    tmp = Wektor3D();
    double x = 0;
    CHECK(tmp[0] == x);
    CHECK(tmp[1] == x);
    CHECK(tmp[2] == x);
}

TEST_CASE("Test Konstruktora Parametrycznego Wektora")
{
    Wektor3D tmp;
    double ttmp[] = {10, 20, 30};
    tmp = Wektor3D(ttmp);
    double x = 10, y = 20, z = 30;
    CHECK(tmp[0] == x);
    CHECK(tmp[1] == y);
    CHECK(tmp[2] == z);
}

TEST_CASE("Test metody ustalającej paramerty wektora")
{
    Wektor3D tmp;
    tmp.setW(3, 31, 43);
    double x = 3, y = 31, z = 43;
    CHECK(tmp[0] == x);
    CHECK(tmp[1] == y);
    CHECK(tmp[2] == z);
}

TEST_CASE("Test porownania wektorów")
{
    double tmp1[] = {15, 10, 10};
    Wektor3D V1 = Wektor3D(tmp1);
    Wektor3D V2 = Wektor3D(tmp1);
    CHECK_EQ(V1 == V2, true);
}

TEST_CASE("Test porownania 2 wektorów")
{
    double tmp1[] = {15, 10, 10}, tmp2[] = {13, 11, 10};
    Wektor3D V1 = Wektor3D(tmp1);
    Wektor3D V2 = Wektor3D(tmp2);
    CHECK_EQ(V1 == V2, false);
}

TEST_CASE("Test dodawania wektorów")
{
    double tmp1[] = {10, 20, 30};
    double tmp2[] = {3.5, 7.89, 9.11};
    Wektor3D V1 = Wektor3D(tmp1);
    Wektor3D V2 = Wektor3D(tmp2);
    Wektor3D V3;
    V3 = V1 + V2;
    double wynik[] = {13.5, 27.89, 39.11};
    Wektor3D V4 = Wektor3D(wynik);

    CHECK(V3 == V4);
}

TEST_CASE("Test odejmowania wektorów")
{
    double tmp1[] = {15.0, 23.0, 10.0}, tmp2[] = {3.5, 7.89, 6.66};
    Wektor3D V1 = Wektor3D(tmp1);
    Wektor3D V2 = Wektor3D(tmp2);
    Wektor3D V3;
    V3 = V1 - V2;
    double wynik[] = {11.5, 15.11, 3.34};
    Wektor3D V4 = Wektor3D(wynik);

    CHECK(V3 == V4);
}

TEST_CASE("Test mnożenia wektora przez macierz")
{
    double tmp1[] = {1, 2, 3};
    double tmp2[] = {3, 6, 9};
    Wektor3D V1, Wynik, Prawidlowy;
    V1 = Wektor3D(tmp1);
    Prawidlowy = Wektor3D(tmp2);
    Macierz3x3 M1 = Macierz3x3(3);
    Wynik = V1 * M1;
    CHECK(Wynik == Prawidlowy);
}

TEST_CASE("Test wypisywania Wektora")
{
    std::stringstream os;
    Wektor3D tmp;
    double tab[] = {1, 2, 3};
    tmp = Wektor3D(tab);
    os << tmp;
    CHECK_EQ("    1.0000000000    2.0000000000    3.0000000000", os.str());
}

TEST_CASE("Test wczytywania Wektora")
{
    std::stringstream is;
    double tab[] = {3, 3, 2};
    Wektor3D V1, V2;
    V2 = Wektor3D(tab);
    is << "3 3 2 ";
    is >> V1;
    CHECK(V1 == V2);
}

TEST_CASE("Test operatora [] dla Wektora")
{
    Wektor3D V1;
    double tab[] = {5, 7, 1.11};
    V1 = Wektor3D(tab);
    CHECK_EQ(V1[0], 5);
    CHECK_EQ(V1[1], 7);
    CHECK_EQ(V1[2], 1.11);
}

TEST_CASE("Test konstruktora Macierzy")
{
    Macierz3x3 tmp;
    tmp = Macierz3x3();
    CHECK(tmp(0, 1) == 0);
    CHECK(tmp(1, 0) == 0);
    CHECK(tmp(1, 1) == 0);
    CHECK(tmp(0, 0) == 0);
    CHECK(tmp(0, 2) == 0);
    CHECK(tmp(1, 2) == 0);
    CHECK(tmp(2, 0) == 0);
    CHECK(tmp(2, 1) == 0);
    CHECK(tmp(2, 2) == 0);
}

TEST_CASE("Test konstruktora Macierzy z argumentem")
{
    Macierz3x3 tmp;
    tmp = Macierz3x3(3);
    CHECK(tmp(0, 1) == 0);
    CHECK(tmp(1, 0) == 0);
    CHECK(tmp(1, 1) == 3);
    CHECK(tmp(0, 0) == 3);
    CHECK(tmp(0, 2) == 0);
    CHECK(tmp(1, 2) == 0);
    CHECK(tmp(2, 0) == 0);
    CHECK(tmp(2, 1) == 0);
    CHECK(tmp(2, 2) == 3);
}

TEST_CASE("Test konstruktora parametrycznego Macierzy")
{
    double tmp1[3][3] = {{10, 20, 54.3}, {29.999, 40.6, 123}, {14.1, 21.1, 15.17}};
    Macierz3x3 tmp;
    tmp = Macierz3x3(tmp1);
    CHECK(tmp(0, 1) == 20);
    CHECK(tmp(1, 0) == 29.999);
    CHECK(tmp(1, 1) == 40.6);
    CHECK(tmp(0, 0) == 10);
    CHECK(tmp(0, 2) == 54.3);
    CHECK(tmp(1, 2) == 123);
    CHECK(tmp(2, 0) == 14.1);
    CHECK(tmp(2, 1) == 21.1);
    CHECK(tmp(2, 2) == 15.17);
}

TEST_CASE("Test przeciazenia porownania dla Macierzy")
{
    Macierz3x3 M1, M2;
    double tmp1[3][3] = {{10.123, 20.89, 54.3}, {29.999, 40.654, 123}, {14.13, 21.1, 15.17}};
    double tmp2[3][3] = {{10.123, 20.89, 54.3}, {29.999, 40.654, 123}, {14.13, 21.1, 15.17}};
    M1 = Macierz3x3(tmp1);
    M2 = Macierz3x3(tmp2);

    CHECK_EQ(M1 == M2, true);
}

TEST_CASE("Test przeciazenia porownania dla Macierzy 2")
{
    Macierz3x3 M1, M2;
    double tmp1[3][3] = {{10.123, 20.89, 54.3}, {29.999, 40.654, 123}, {14.13, 21.1, 15.17}};
    double tmp2[3][3] = {{10.100, 20.89, 54.3}, {29.999, 40.654, 123}, {14.13, 21.1, 15.17}};
    M1 = Macierz3x3(tmp1);
    M2 = Macierz3x3(tmp2);

    CHECK_EQ(M1 == M2, false);
}

TEST_CASE("Test przeciazenia mnozenia Macierz Razy Macierz")
{
    Macierz3x3 M1, M2, Wynik, Prawidlowy;
    double tmp1[3][3] = {{10, 20, 54}, {29, 40, 12}, {14, 21, 15}};
    double tmp2[3][3] = {{10, 5, 3}, {2, 45, 13}, {4, 1, 1.5}};
    double tmp3[3][3] = {{356, 1004, 371}, {418, 1957, 625}, {242, 1030, 337.5}};
    M1 = Macierz3x3(tmp1);
    M2 = Macierz3x3(tmp2);
    Prawidlowy = Macierz3x3(tmp3);
    Wynik = M1 * M2;
    CHECK(Wynik == Prawidlowy);
}

TEST_CASE("Przeciazenie () dla Macierzy")
{
    Macierz3x3 M1;
    double tmp1[3][3] = {{10.123, 20.89, 54.3}, {29.999, 40.654, 123}, {14.13, 21.1, 15.17}};
    M1 = Macierz3x3(tmp1);

    CHECK(M1(0, 0) == 10.123);
    CHECK(M1(1, 0) == 29.999);
    CHECK(M1(2, 2) == 15.17);
}

TEST_CASE("Test metody clear")
{
    Macierz3x3 tmp;
    double tmp1[3][3] = {{10.123, 20.89, 54.3}, {29.999, 40.654, 123}, {14.13, 21.1, 15.17}};
    tmp = Macierz3x3(tmp1);
    tmp.clear();

    CHECK(tmp(0, 1) == 0);
    CHECK(tmp(1, 0) == 0);
    CHECK(tmp(1, 1) == 0);
    CHECK(tmp(0, 0) == 0);
    CHECK(tmp(0, 2) == 0);
    CHECK(tmp(1, 2) == 0);
    CHECK(tmp(2, 0) == 0);
    CHECK(tmp(2, 1) == 0);
    CHECK(tmp(2, 2) == 0);
}

TEST_CASE("Test metody SetX"){
    Macierz3x3 M1;
    double alfa = 0.5;
    M1 = Macierz3x3();
    M1.setX(alfa);
    CHECK(M1(1,1) == cos(alfa * PI / 180));
    CHECK(M1(1,2) == -sin(alfa * PI / 180)); 
    CHECK(M1(2,1) == sin(alfa * PI / 180));  
    CHECK(M1(2,2) == cos(alfa * PI / 180));
    CHECK(M1(0,0) == 1);
}

TEST_CASE("Test metody SetY"){
    Macierz3x3 M1;
    double alfa = 0.5;
    M1 = Macierz3x3();
    M1.setY(alfa);
    CHECK(M1(0,0) == cos(alfa * PI / 180));
    CHECK(M1(2,0) == -sin(alfa * PI / 180)); 
    CHECK(M1(0,2) == sin(alfa * PI / 180));  
    CHECK(M1(2,2) == cos(alfa * PI / 180));
    CHECK(M1(1,1) == 1);
}

TEST_CASE("Test metody SetZ"){
    Macierz3x3 M1;
    double alfa = 0.5;
    M1 = Macierz3x3();
    M1.setZ(alfa);
    CHECK(M1(0,0) == cos(alfa * PI / 180));
    CHECK(M1(0,1) == -sin(alfa * PI / 180)); 
    CHECK(M1(1,0) == sin(alfa * PI / 180));  
    CHECK(M1(1,1) == cos(alfa * PI / 180));
    CHECK(M1(2,2) == 1);
}



TEST_CASE("Przeciazenie wypisywania dla Macierzy")
{
    std::stringstream os;
    Macierz3x3 M1;
    double tmp[3][3] = {{15, 22, 11}, {3, 11, 5},{1, 2 , 3}};
    M1 = Macierz3x3(tmp);
    os << M1;
    CHECK_EQ("|    15.0000000000    22.0000000000    11.0000000000 |\n|     3.0000000000    11.0000000000     5.0000000000 |\n|     1.0000000000     2.0000000000     3.0000000000 |\n", os.str());
}

TEST_CASE("Test konstruktora Prostopadłościanu i przeciazenia []"){
    Prostopadloscian P1;
    P1 = Prostopadloscian();
    Wektor3D W1 = Wektor3D();
    CHECK(P1[0] == W1);
    CHECK(P1[1] == W1);
    CHECK(P1[2] == W1);
    CHECK(P1[3] == W1);
    CHECK(P1[4] == W1);
    CHECK(P1[5] == W1);
    CHECK(P1[6] == W1);
    CHECK(P1[7] == W1);

}

TEST_CASE("Test metody Inicjalizacji Prostopadloscianu"){
    Prostopadloscian P1;
    P1 = Prostopadloscian();
    double tmp0[]={0,0,0},tmp1[]={3,0,0},tmp2[]={0,4,0},tmp3[]={3,4,0},tmp4[]={0,4,5},tmp5[]={3,4,5},tmp6[]={0,0,5},tmp7[]={3,0,5};
    P1.Inicjalizuj(0,3,4,5);
    Wektor3D W0 = Wektor3D(tmp0);
    Wektor3D W1 = Wektor3D(tmp1);
    Wektor3D W2 = Wektor3D(tmp2);
    Wektor3D W3 = Wektor3D(tmp3);
    Wektor3D W4 = Wektor3D(tmp4);
    Wektor3D W5 = Wektor3D(tmp5);
    Wektor3D W6 = Wektor3D(tmp6);
    Wektor3D W7 = Wektor3D(tmp7);

    CHECK(P1[0] == W0);
    CHECK(P1[1] == W1);
    CHECK(P1[2] == W2);
    CHECK(P1[3] == W3);
    CHECK(P1[4] == W4);
    CHECK(P1[5] == W5);
    CHECK(P1[6] == W6);
    CHECK(P1[7] == W7);
}

TEST_CASE("test metody przesuniecia prostopadłoscianu "){
    Prostopadloscian P1;
    P1 = Prostopadloscian();
    P1.Inicjalizuj(0,3,4,5);
    
    double tab_pr[]={3,3,3};
    Wektor3D W_przesuniecia = Wektor3D(tab_pr);
    P1.Przesun(W_przesuniecia);
    double wyn0[]={3,3,3},wyn1[]={6,3,3},wyn2[]={3,7,3},wyn3[]={6,7,3},wyn4[]={3,7,8},wyn5[]={6,7,8},wyn6[]={3,3,8},wyn7[]={6,3,8};
    Wektor3D WK0 = Wektor3D(wyn0);
    Wektor3D WK1 = Wektor3D(wyn1);
    Wektor3D WK2 = Wektor3D(wyn2);
    Wektor3D WK3 = Wektor3D(wyn3);
    Wektor3D WK4 = Wektor3D(wyn4);
    Wektor3D WK5 = Wektor3D(wyn5);
    Wektor3D WK6 = Wektor3D(wyn6);
    Wektor3D WK7 = Wektor3D(wyn7);



    CHECK(P1[0] == WK0);
    CHECK(P1[1] == WK1);
    CHECK(P1[2] == WK2);
    CHECK(P1[3] == WK3);
    CHECK(P1[4] == WK4);
    CHECK(P1[5] == WK5);
    CHECK(P1[6] == WK6);
    CHECK(P1[7] == WK7);
}

TEST_CASE("test metody rotacji prostopadłoscianu "){
    Prostopadloscian P1;
    P1 = Prostopadloscian();
    P1.Inicjalizuj(0,3,4,5);
    
    Macierz3x3 M1 = Macierz3x3(3);
    P1.Rotacja(M1);
    double wyn0[]={0,0,0},wyn1[]={9,0,0},wyn2[]={0,12,0},wyn3[]={9,12,0},wyn4[]={0,12,15},wyn5[]={9,12,15},wyn6[]={0,0,15},wyn7[]={9,0,15};
    Wektor3D WK0 = Wektor3D(wyn0);
    Wektor3D WK1 = Wektor3D(wyn1);
    Wektor3D WK2 = Wektor3D(wyn2);
    Wektor3D WK3 = Wektor3D(wyn3);
    Wektor3D WK4 = Wektor3D(wyn4);
    Wektor3D WK5 = Wektor3D(wyn5);
    Wektor3D WK6 = Wektor3D(wyn6);
    Wektor3D WK7 = Wektor3D(wyn7);



    CHECK(P1[0] == WK0);
    CHECK(P1[1] == WK1);
    CHECK(P1[2] == WK2);
    CHECK(P1[3] == WK3);
    CHECK(P1[4] == WK4);
    CHECK(P1[5] == WK5);
    CHECK(P1[6] == WK6);
    CHECK(P1[7] == WK7);
}

TEST_CASE("Test Zapisu bokow X"){
    Prostopadloscian P1;
    P1 = Prostopadloscian();
    P1.Inicjalizuj(0,3,4,5);
    double tab[12];
    P1.ZapiszBokiX(tab);
    CHECK(tab[0] == 3);
    CHECK(tab[1] == 3);
    CHECK(tab[2] == 3);
    CHECK(tab[3] == 3);
}

TEST_CASE("Test Zapisu bokow Y"){
    Prostopadloscian P1;
    P1 = Prostopadloscian();
    P1.Inicjalizuj(0,3,4,5);
    double tab[12];
    P1.ZapiszBokiY(tab);
    CHECK(tab[4] == 4);
    CHECK(tab[5] == 4);
    CHECK(tab[6] == 4);
    CHECK(tab[7] == 4);
}

TEST_CASE("Test Zapisu bokow Z"){
    Prostopadloscian P1;
    P1 = Prostopadloscian();
    P1.Inicjalizuj(0,3,4,5);
    double tab[12];
    P1.ZapiszBokiZ(tab);
    CHECK(tab[8] == 5);
    CHECK(tab[9] == 5);
    CHECK(tab[10] == 5);
    CHECK(tab[11] == 5);
}

TEST_CASE("Test sprawdzania boków"){
    Prostopadloscian P1;
    P1 = Prostopadloscian();
    P1.Inicjalizuj(0,3,4,5);
    double tab[12];
    P1.ZapiszBoki(tab);
    CHECK_EQ(P1.Sprawdzboki(0,tab),true);
    CHECK_EQ(P1.Sprawdzboki(4,tab),true);
    CHECK_EQ(P1.Sprawdzboki(8,tab),true);
    CHECK_EQ(P1.Sprawdzboki(2,tab),false);
    CHECK_EQ(P1.Sprawdzboki(5,tab),false);
}

TEST_CASE("Test Zapisu do Strumienia"){
std::stringstream os;
Prostopadloscian P1;
P1 = Prostopadloscian();
P1.Inicjalizuj(0,3,4,5);
P1.ZapisDoStr(os);
CHECK_EQ("    0.0000000000    0.0000000000    0.0000000000\n    3.0000000000    0.0000000000    0.0000000000\n\n    0.0000000000    4.0000000000    0.0000000000\n    3.0000000000    4.0000000000    0.0000000000\n\n    0.0000000000    4.0000000000    5.0000000000\n    3.0000000000    4.0000000000    5.0000000000\n\n    0.0000000000    0.0000000000    5.0000000000\n    3.0000000000    0.0000000000    5.0000000000\n\n    0.0000000000    0.0000000000    0.0000000000\n    3.0000000000    0.0000000000    0.0000000000",os.str());
}

TEST_CASE("Test przeciżenia wyświetlania"){
std::stringstream os;
Prostopadloscian P1;
P1 = Prostopadloscian();
P1.Inicjalizuj(0,3,4,5);
os<<P1;
CHECK_EQ("\n    0.0000000000    0.0000000000    0.0000000000\n    3.0000000000    0.0000000000    0.0000000000\n    0.0000000000    4.0000000000    0.0000000000\n    3.0000000000    4.0000000000    0.0000000000\n    0.0000000000    4.0000000000    5.0000000000\n    3.0000000000    4.0000000000    5.0000000000\n    0.0000000000    0.0000000000    5.0000000000\n    3.0000000000    0.0000000000    5.0000000000 \n",os.str());
}

TEST_CASE("Test metody dodaj i Ustalenia koncowej macierzy rotacji"){
    Rotacja R1;
    Macierz3x3 tmp;
    R1.dodaj(30,'X');
    tmp = R1.Ustalkoniec();
    CHECK(tmp(0, 1) == 0.0);
    CHECK(tmp(1, 0) == 0.0);
    CHECK(tmp(1, 1) == 0.0);
    CHECK(tmp(0, 0) == 0.0);
    CHECK(tmp(0, 2) == 0.0);
    CHECK(tmp(1, 2) == 0.0);
    CHECK(tmp(2, 0) == 0.0);
    CHECK(tmp(2, 1) == 0.0);
    CHECK(tmp(2, 2) == 0.0);

}