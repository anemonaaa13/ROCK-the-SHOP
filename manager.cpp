#include "manager.h"
using namespace std;

Manager::Manager(int id, string nume, string prenume, string cnp, chrono::system_clock::time_point dataAngajare) : Angajat(id, nume, prenume, cnp, dataAngajare){}

double Manager::CalculeazaSalariuLunaCurenta() const {

    double salariu = SALARIU_BAZA + 100.0 * CalculeazaVechimeInAni();
    salariu *= 1.25;
    return salariu;
}
