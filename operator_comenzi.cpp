#include "operator_comenzi.h"
using namespace std;

OperatorComenzi::OperatorComenzi(int id, string nume, string prenume, string cnp, chrono::system_clock::time_point dataAngajare): Angajat(id, nume, prenume, cnp, dataAngajare),totalValoareComenziProcesate(0.0) {}

void OperatorComenzi::AdaugaValoareComanda(double valoare)
{
    totalValoareComenziProcesate += valoare;
}

double OperatorComenzi::GetTotalValoareComenzi() const
{
    return totalValoareComenziProcesate;
}


double OperatorComenzi::CalculeazaSalariuLunaCurenta() const
{

    double salariu = SALARIU_BAZA + 100.0 * CalculeazaVechimeInAni();
    double bonus = 0.005 * totalValoareComenziProcesate;
    salariu += bonus;
    if(EsteZiuaDeNastere())
    {
        salariu += 100.0;
    }
    return salariu;
}
