#include "disc.h"
#include <iostream>
#include <iomanip>
using namespace std;

Disc::Disc(int codUnic, string denumire, int stoc, double pretBaza, string casaDeDiscuri, chrono::system_clock::time_point dataLansare, string trupa, string album, TipDisc tipDisc): Produs(codUnic, denumire, stoc, pretBaza),casaDeDiscuri(casaDeDiscuri),dataLansare(dataLansare),trupa(trupa),album(album),tipDisc(tipDisc) {}

double Disc::CalculeazaPretFinal() const
{
    return pretBaza + 5.0;
}

void Disc::AfiseazaInformatii() const
{
    cout << "\n\n-------- [DISC] -------- \n";
    cout << "Cod: " << codUnic << "\n";
    cout << "Denumire: " << denumire << "\n";
    cout << "Stoc: " << stoc << "\n";
    cout << "PretBaza: " << pretBaza << "\n";
    cout << "Casa De Discuri: " << casaDeDiscuri << "\n";
    cout << "Trupa: " << trupa << "\n";
    cout << "Album: " << album << "\n";
    cout << "TipDisc: " << (tipDisc == TipDisc::CD ? "CD" : "Vinil") << "\n";
}

bool Disc::IsIdenticCu(const Produs &p) const
{
    const Disc *d = dynamic_cast<const Disc*>(&p);
    if(!d)
return false;

    return (this->denumire == d->denumire && this->casaDeDiscuri == d->casaDeDiscuri && this->trupa == d->trupa && this->album == d->album && this->tipDisc == d->tipDisc);
}

chrono::system_clock::time_point Disc::GetDataLansare() const
{
    return dataLansare;
}

string Disc::GetCasaDeDiscuri() const
{
    return casaDeDiscuri;
}

string Disc::GetTrupa() const
{
    return trupa;
}

string Disc::GetAlbum() const
{
    return album;
}

TipDisc Disc::GetTipDisc()
{
    return tipDisc;
}
