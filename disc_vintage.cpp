#include "disc_vintage.h"
#include <iostream>
using namespace std;

DiscVintage::DiscVintage(int codUnic, string denumire, int stoc, double pretBaza, string casaDeDiscuri, chrono::system_clock::time_point dataLansare, string trupa, string album, TipDisc tipDisc, bool mint, int coeficientRaritate): Disc(codUnic, denumire, stoc, pretBaza, casaDeDiscuri, dataLansare, trupa, album, tipDisc), mint(mint),coeficientRaritate(coeficientRaritate) {}

double DiscVintage::CalculeazaPretFinal() const
{
    double pretNormal = Disc::CalculeazaPretFinal();
    double extra = 15.0 * coeficientRaritate;
    return pretNormal + extra;
}

void DiscVintage::AfiseazaInformatii() const
{
    Disc::AfiseazaInformatii();
    cout << "(Vintage: " << (mint ? "Mint condition" : "Not mint") << ", Coef Raritate: " << coeficientRaritate << ")\n";
}

bool DiscVintage::IsIdenticCu(const Produs &p) const
{

    const DiscVintage *dv = dynamic_cast<const DiscVintage*>(&p);
    if(!dv)
        return false;

    if(!Disc::IsIdenticCu(p))
    {
        return false;
    }

    return (this->mint == dv->mint && this->coeficientRaritate == dv->coeficientRaritate);
}

string DiscVintage::GetCasaDeDiscuri() const
{
    return casaDeDiscuri;
}

string DiscVintage::GetTrupa() const
{
    return trupa;
}

string DiscVintage::GetAlbum() const
{
    return album;
}

TipDisc DiscVintage::GetTipDisc() const
{
    return tipDisc;
}

bool DiscVintage::IsMint()
{
    return mint;
}

int DiscVintage::GetCoeficientRaritate()
{
    return coeficientRaritate;
}
