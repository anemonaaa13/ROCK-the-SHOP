#pragma once
#include "angajat.h"

class Manager : public Angajat {
public:
    Manager(int id, string nume, string prenume, string cnp, chrono::system_clock::time_point dataAngajare);
    ~Manager() override = default;

    double CalculeazaSalariuLunaCurenta() const override;
    bool EsteZiuaDeNastere() const override {
        return false; // nu primeste bonus niciodata
    }
};
