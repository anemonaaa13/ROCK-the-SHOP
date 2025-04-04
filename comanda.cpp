#include "comanda.h"
using namespace std;

Comanda::Comanda(int idComanda, chrono::system_clock::time_point dataPrimire, int durataRezolvare): idComanda(idComanda),dataPrimire(dataPrimire),durataRezolvare(durataRezolvare),valoareFaraLivrare(0.0),valoareTotalaCuLivrare(0.0),procesata(false),finalizata(false),idOperatorCareProceseaza(-1),invalida(false){}

bool Comanda::EsteProcesata() const {
    return procesata;
}

bool Comanda::EsteFinalizata() const {
    return finalizata;
}

bool Comanda::EsteInvalida() const {
    return invalida;
}

int Comanda::GetIdComanda() const {
    return idComanda;
}

chrono::system_clock::time_point Comanda::GetDataPrimire() const {
    return dataPrimire;
}

int Comanda::GetDurataRezolvare() const {
    return durataRezolvare;
}

double Comanda::GetValoareFaraLivrare() const {
    return valoareFaraLivrare;
}

double Comanda::GetValoareTotalaCuLivrare() const {
    return valoareTotalaCuLivrare;
}

vector<pair<int,int>> Comanda::GetProduseComandate() const {
    return produseComandate;
}

int Comanda::GetIdOperator() const {
    return idOperatorCareProceseaza;
}

void Comanda::AdaugaProdus(int codProdus, int cantitate) {
    produseComandate.push_back({codProdus, cantitate});
}

void Comanda::SetValoareFaraLivrare(double val) {
    valoareFaraLivrare = val;
}

void Comanda::SetValoareTotalaCuLivrare(double val) {
    valoareTotalaCuLivrare = val;
}

void Comanda::SetIdOperator(int idOp) {
    idOperatorCareProceseaza = idOp;
}

void Comanda::MarcheazaProcesata(bool b) {
    procesata = b;
}

void Comanda::MarcheazaFinalizata(bool b) {
    finalizata = b;
}

void Comanda::MarcheazaInvalida(bool b) {
    invalida = b;
}
