#include "Prostopadloscian.hh"

/**
 * @file Prostopadloscian.cpp
 * 
 * @brief Plik zawiera rozwinięcie metod klasy Prostopadloscian 
 * 
 */

void Prostopadloscian::Inicjalizuj(const double wsp, const double bokx,
                                   const double boky, const double bokz)
{
    _wsp[0].setW(wsp, wsp, wsp);
    _wsp[1].setW(wsp + bokx, wsp, wsp);
    _wsp[2].setW(wsp, wsp + boky, wsp);
    _wsp[3].setW(wsp + bokx, wsp + boky, wsp);
    _wsp[4].setW(wsp, wsp + boky, wsp + bokz);
    _wsp[5].setW(wsp + bokx, wsp + boky, wsp + bokz);
    _wsp[6].setW(wsp, wsp, wsp + bokz);
    _wsp[7].setW(wsp + bokx, wsp, wsp + bokz);
}

void Prostopadloscian::ZapiszBoki(double Tab[IL_B]) const
{
    ZapiszBokiX(Tab);
    ZapiszBokiY(Tab);
    ZapiszBokiZ(Tab);
}

void Prostopadloscian::ZapiszBokiZ(double Tab[IL_B]) const
{
    Wektor3D tmp;
    tmp = _wsp[6] - _wsp[0];
    Tab[8] = sqrt(tmp[0] * tmp[0] + tmp[1] * tmp[1] + tmp[2] * tmp[2]);
    tmp = _wsp[7] - _wsp[1];
    Tab[9] = sqrt(tmp[0] * tmp[0] + tmp[1] * tmp[1] + tmp[2] * tmp[2]);
    tmp = _wsp[5] - _wsp[3];
    Tab[10] = sqrt(tmp[0] * tmp[0] + tmp[1] * tmp[1] + tmp[2] * tmp[2]);
    tmp = _wsp[4] - _wsp[2];
    Tab[11] = sqrt(tmp[0] * tmp[0] + tmp[1] * tmp[1] + tmp[2] * tmp[2]);
}

void Prostopadloscian::ZapiszBokiX(double Tab[IL_B]) const
{
    Wektor3D tmp;
    int licz = 0;
    for (int i = 0; i < ROZM_P; i += 2) //Boki na osi OX
    {
        tmp = _wsp[i + 1] - _wsp[i];
        Tab[licz] = sqrt((tmp[0] * tmp[0]) + (tmp[1] * tmp[1]) + (tmp[2] * tmp[2]));
        licz++; //zapisanie dlugosci boku ze wzoru
    }
}

void Prostopadloscian::ZapiszBokiY(double Tab[IL_B]) const
{
    Wektor3D tmp;

    tmp = _wsp[2] - _wsp[0];
    Tab[4] = sqrt(tmp[0] * tmp[0] + tmp[1] * tmp[1] + tmp[2] * tmp[2]);
    tmp = _wsp[3] - _wsp[1];
    Tab[5] = sqrt(tmp[0] * tmp[0] + tmp[1] * tmp[1] + tmp[2] * tmp[2]);
    tmp = _wsp[4] - _wsp[6];
    Tab[6] = sqrt(tmp[0] * tmp[0] + tmp[1] * tmp[1] + tmp[2] * tmp[2]);
    tmp = _wsp[5] - _wsp[7];
    Tab[7] = sqrt(tmp[0] * tmp[0] + tmp[1] * tmp[1] + tmp[2] * tmp[2]);
}

void Prostopadloscian::Porownaj(double Tab[IL_B]) const
{
    ZapiszBoki(Tab); //porownanie poszczegolnych bokow, wyswietlenie komunikatu

    if (!Sprawdzboki(0, Tab)) // i odpowiednich wartosci
    {
        std::cout << "\n:O  Krotsze przeciwlegle boki nie sa rowne!!!\n";
        Wyswietlboki(0, Tab);
    }
    else
    {
        std::cout << "\n:)  Krotsze przeciwlegle boki sa sobie rowne\n";
        Wyswietlboki(0, Tab);
    }
    if (!Sprawdzboki(4, Tab))
    {
        std::cout << ":O  Dluzsze przeciwlegle boki nie sa rowne!!!\n";
        Wyswietlboki(4, Tab);
    }
    else
    {
        std::cout << ":)  Dluzsze przeciwlegle boki sa sobie rowne\n";
        Wyswietlboki(4, Tab);
    }
    if (!Sprawdzboki(8, Tab))
    {
        std::cout << ":O  Poprzeczne przeciwlegle boki nie sa rowne!!!\n";
        Wyswietlboki(8, Tab);
    }
    else
    {
        std::cout << ":)  Poprzeczne przeciwlegle boki sa sobie rowne\n";
        Wyswietlboki(8, Tab);
    }
}

bool Prostopadloscian::Sprawdzboki(const int nr_boku, double Tab[IL_B]) const
{
    for (size_t i = 0; i < 4; ++i)
    {
        if (i == 3)
        {
            if (Tab[nr_boku + i] != Tab[nr_boku])
                return false;
        }
        else
        {
            if (Tab[nr_boku + i] != Tab[nr_boku + i + 1])
                return false;
        }
    }
    return true;
}

void Prostopadloscian::Wyswietlboki(const int nr_boku, double Tab[IL_B]) const
{
    std::cout << "Dlugosc pierwszego boku: ";
    std::cout << std::setw(16) << std::fixed << std::setprecision(10) << Tab[nr_boku] << std::endl;
    std::cout << "  Dlugosc drugiego boku: ";
    std::cout << std::setw(16) << std::fixed << std::setprecision(10) << Tab[nr_boku + 1] << std::endl;
    std::cout << "Dlugosc trzeciego boku: ";
    std::cout << std::setw(16) << std::fixed << std::setprecision(10) << Tab[nr_boku + 2] << std::endl;
    std::cout << "Dlugosc czwartego boku: ";
    std::cout << std::setw(16) << std::fixed << std::setprecision(10) << Tab[nr_boku + 3] << std::endl;
}

void Prostopadloscian::ZapisDoStr(std::ostream &Str) const
{
    for (int i = 0; i < ROZM_P; i++)
    { //zapisanie wspolrzednych prostokata do strumienia
        Str << _wsp[i] << std::endl;
        if (i % 2)
            Str << std::endl;
    }
    Str << _wsp[0] << std::endl; //ponowne zapisanie pierwszej wspolrzednej aby gnuplot narysowal linie
    Str << _wsp[1];
}

bool Prostopadloscian::ZapisDoPliku(const char *NazwaPliku) const
{
    std::ofstream plik;
    plik.open(NazwaPliku, std::ios::out);
    if (!plik.is_open())
    {
        std::cerr << ":(  Operacja otwarcia do zapisu \"" << NazwaPliku << "\"" << std::endl
                  << ":(  nie powiodla sie." << std::endl;
        return false;
    }
    ZapisDoStr(plik);
    plik.close();
    return !plik.fail();
}

std::ostream &operator<<(std::ostream &out, const Prostopadloscian &Pr)
{
    for (int i = 0; i < ROZM_P; i++)
    {
        if (!i % 2)
            out << std::endl;      //wykorzystanie stworzonego wczesniej przeciazenia operatora dla
        out << Pr[i] << std::endl; //wektora dla kazdej wspolrzednej
    }
    return out;
}
