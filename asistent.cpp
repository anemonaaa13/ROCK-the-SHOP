#include "asistent.h"
using namespace std;
#include<iostream>

Asistent::Asistent(int id, string nume, string prenume, string cnp, chrono::system_clock::time_point dataAngajare): Angajat(id, nume, prenume, cnp, dataAngajare){}

double Asistent::CalculeazaSalariuLunaCurenta() const {

    double salariu = SALARIU_BAZA + 100.0 * CalculeazaVechimeInAni();
    salariu *= 0.75;
    if(EsteZiuaDeNastere()) {
        salariu += 100.0;
    }
    return salariu;
}
