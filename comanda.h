#pragma once
#include <vector>
#include <utility>
#include <chrono>
using namespace std;

class Comanda
{
private:
    int idComanda;
    chrono::system_clock::time_point dataPrimire;
    int durataRezolvare;

    vector<pair<int,int>> produseComandate; // pereche cod produs + cantitate

    double valoareFaraLivrare;
    double valoareTotalaCuLivrare;
    bool procesata;
    bool finalizata;
    int idOperatorCareProceseaza;
    bool invalida;

public:
    Comanda(int idComanda, chrono::system_clock::time_point dataPrimire, int durataRezolvare);

    bool EsteProcesata() const;
    bool EsteFinalizata() const;
    bool EsteInvalida() const;

    int GetIdComanda() const;
    chrono::system_clock::time_point GetDataPrimire() const;
    int GetDurataRezolvare() const;
    double GetValoareFaraLivrare() const;
    double GetValoareTotalaCuLivrare() const;
    vector<pair<int,int>> GetProduseComandate() const;
    int  GetIdOperator() const;

    void AdaugaProdus(int codProdus, int cantitate);

    void SetValoareFaraLivrare(double val);
    void SetValoareTotalaCuLivrare(double val);
    void SetIdOperator(int idOp);

    void MarcheazaProcesata(bool flag);
    void MarcheazaFinalizata(bool flag);
    void MarcheazaInvalida(bool flag);
};
