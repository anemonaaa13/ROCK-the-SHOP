#pragma once
#include "produs.h"
#include <chrono>

enum class TipDisc {
    CD,
    VINIL
};

class Disc : public Produs {
protected:
    string casaDeDiscuri;
    chrono::system_clock::time_point dataLansare;
    string trupa;
    string album;
    TipDisc tipDisc;

public:
    Disc(int codUnic, string denumire, int stoc, double pretBaza, string casaDeDiscuri, chrono::system_clock::time_point dataLansare, string trupa, string album, TipDisc tipDisc);

    double CalculeazaPretFinal() const override;
    void AfiseazaInformatii() const override;
    bool IsIdenticCu(const Produs &) const override;

    chrono::system_clock::time_point GetDataLansare() const;
    string GetCasaDeDiscuri() const;
    string GetTrupa() const;
    string GetAlbum() const;
    TipDisc GetTipDisc();
};
