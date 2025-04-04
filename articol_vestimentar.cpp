#include "articol_vestimentar.h"
#include <iostream>
using namespace std;

ArticolVestimentar::ArticolVestimentar(int codUnic, string denumire, int stoc, double pretBaza,string culoare, string marca): Produs(codUnic, denumire, stoc, pretBaza),culoare(culoare), marca(marca){}

double ArticolVestimentar::CalculeazaPretFinal() const {
    return pretBaza + 20.0;
}

void ArticolVestimentar::AfiseazaInformatii() const {
    cout << "\n\n-------- [Articol Vestimentar] --------\n";
    cout << "Cod: " << codUnic << "\n";
    cout << "Denumire: " << denumire << "\n";
    cout << "Stoc: " << stoc << "\n";
    cout << "PretBaza: " << pretBaza << "\n";
    cout << "Culoare: " << culoare << "\n";
    cout << "Marca: " << marca << "\n";
}

bool ArticolVestimentar::IsIdenticCu(const Produs &p) const {

    const ArticolVestimentar *av = dynamic_cast<const ArticolVestimentar*>(&p);
    if(!av)
        return false;

    return (this->denumire == av->denumire && this->culoare == av->culoare && this->marca == av->marca);
}
