#pragma once
#include "angajat.h"

class Asistent : public Angajat {
public:
    Asistent(int id, string nume, string prenume, string cnp, chrono::system_clock::time_point dataAngajare);
    ~Asistent() override = default;

    double CalculeazaSalariuLunaCurenta() const override;

    bool EsteZiuaDeNastere() const override {
        return Angajat::EsteZiuaDeNastere();
    }
};
