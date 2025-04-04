#include "produs.h"
#include <iostream>
using namespace std;

Produs::Produs(int codUnic, string denumire, int stoc, double pretBaza): codUnic(codUnic), denumire(denumire), stoc(stoc), pretBaza(pretBaza){}

int Produs::GetCodUnic() const {
    return codUnic;
}

string Produs::GetDenumire() const {
    return denumire;
}

int Produs::GetStoc() const {
    return stoc;
}

double Produs::GetPretBaza() const {
    return pretBaza;
}

void Produs::SetDenumire(string denumireNoua) {
    denumire = denumireNoua;
}

void Produs::SetStoc(int stocNou) {
    stoc = stocNou;
}

void Produs::SetPretBaza(double pretNou) {
    pretBaza = pretNou;
}
