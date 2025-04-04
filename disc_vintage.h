#pragma once
#include "disc.h"

class DiscVintage : public Disc {
private:
    bool mint;
    int coeficientRaritate;

public:
    DiscVintage(int codUnic, string denumire, int stoc, double pretBaza, string casaDeDiscuri, chrono::system_clock::time_point dataLansare, string trupa, string album, TipDisc tipDisc, bool mint, int coeficientRaritate);

    double CalculeazaPretFinal() const override;
    void AfiseazaInformatii() const override;
    bool IsIdenticCu(const Produs &) const override;

    string GetCasaDeDiscuri() const;
    string GetTrupa() const;
    string GetAlbum() const;
    TipDisc GetTipDisc() const;
    bool IsMint();
    int GetCoeficientRaritate();
};
