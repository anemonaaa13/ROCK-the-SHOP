#pragma once
#include "produs.h"

class ArticolVestimentar : public Produs {
private:
    string culoare;
    string marca;
public:
    ArticolVestimentar(int codUnic, string denumire, int stoc, double pretBaza, string culoare, string marca);

    double CalculeazaPretFinal() const override;
    void AfiseazaInformatii() const override;
    bool IsIdenticCu(const Produs &) const override;
};
