#pragma once
#include "angajat.h"

class OperatorComenzi : public Angajat {
private:
    double totalValoareComenziProcesate;

public:
    OperatorComenzi(int id, string nume, string prenume, string cnp, chrono::system_clock::time_point dataAngajare);
    ~OperatorComenzi() override = default;

    void AdaugaValoareComanda(double valoare);
    double GetTotalValoareComenzi() const;
    double CalculeazaSalariuLunaCurenta() const override;
    bool EsteZiuaDeNastere() const override {
        return Angajat::EsteZiuaDeNastere();
    }
};
