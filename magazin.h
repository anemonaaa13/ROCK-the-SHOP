#pragma once
#include <vector>
#include <memory>
#include "angajat.h"
#include "manager.h"
#include "operator_comenzi.h"
#include "asistent.h"
#include "produs.h"
#include "articol_vestimentar.h"
#include "disc.h"
#include "disc_vintage.h"
#include "comanda.h"
using namespace std;

class Magazin {
private:
    vector<unique_ptr<Angajat>> angajati;
    vector<unique_ptr<Produs>> produse;
    vector<unique_ptr<Comanda>> comenzi;

    int nextAngajatId;
    int nextProdusId;
    int nextComandaId;

public:
    Magazin();
    ~Magazin();
    Magazin(const Magazin&) = delete;
    Magazin& operator=(const Magazin&) = delete;

    // Angajati
    int GetNextAngajatId() const;
    void IncrementNextAngajatId();
    void SetNextAngajatId(int val);
    void AdaugaAngajat(unique_ptr<Angajat> angajat);
    bool StergeAngajat(int idAngajat);
    Angajat* GasesteAngajat(int idAngajat) const;
    void AfiseazaTotiAngajatii() const;
    void ModificaNumeAngajat(int idAngajat, string numeNou);
    void AfiseazaAngajat(int idAngajat) const;
    bool ArePersonalMinimal() const;
    vector<Angajat*> GetListaAngajati() const;

    // Produse
    int GetNextProdusId();
    void SetNextProdusId(int val);
    void AdaugaProdus(unique_ptr<Produs> produs);
    bool StergeProdus(int codProdus);
    Produs* GasesteProdus(int codProdus) const;
    void AfiseazaToateProdusele() const;
    void ModificaStocProdus(int codProdus, int stocNou);
    void AfiseazaProdus(int codProdus) const;
    bool AreStocMinimal() const;
    vector<Produs*> GetListaProduse() const;

    // Comenzi
    int GetNextComandaId();
    void SetNextComandaId(int val);
    void AdaugaComanda(unique_ptr<Comanda> comanda);
    void ProceseazaComenzi();
    void SimulareTimp(int unitati);
    void AfiseazaComanda(int idComanda) const;
    void AfiseazaToateComenzile_sumar() const;
    void AfiseazaToateComenzile_detaliu() const;
    const vector<unique_ptr<Comanda>>& GetListaComenzi() const;

    // Rapoarte
    void RaportAngajatCeleMaiMulteComenzi() const;
    void RaportTop3ValoareComenzi() const;
    void RaportTop3Salariu() const;
};
