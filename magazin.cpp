#include "magazin.h"
#include <iostream>
#include <algorithm>
#include <map>
#include <fstream>


using namespace std;
using namespace chrono;

Magazin::Magazin(): nextAngajatId(1), nextProdusId(1), nextComandaId(1) {}

Magazin::~Magazin() {}

// Angajati
int Magazin::GetNextAngajatId() const
{
    return nextAngajatId;
}

void Magazin::IncrementNextAngajatId()
{
    nextAngajatId++;
}

void Magazin::SetNextAngajatId(int val)
{
    nextAngajatId = val;
}

void Magazin::AdaugaAngajat(unique_ptr<Angajat> angajat)
{
    angajati.push_back(move(angajat));
}

bool Magazin::StergeAngajat(int idAngajat)
{
    for(auto it = angajati.begin(); it != angajati.end(); ++it)
    {
        if((*it)->GetId() == idAngajat)
        {
            angajati.erase(it);
            return true;
        }
    }
    return false;
}

Angajat* Magazin::GasesteAngajat(int idAngajat) const
{
    for(auto &a : angajati)
    {
        if(a->GetId() == idAngajat)
        {
            return a.get();
        }
    }
    return nullptr;
}

void Magazin::AfiseazaTotiAngajatii() const
{
    cout << "=== Lista angajati ===\n";
    for(auto &a : angajati)
    {
        a->AfiseazaInformatii();
        cout << "Salariu curent: " << a->CalculeazaSalariuLunaCurenta() << " RON\n";
        cout << "--------------------\n";
    }
}

void Magazin::ModificaNumeAngajat(int idAngajat, string numeNou)
{
    Angajat *a = GasesteAngajat(idAngajat);
    if(!a)
    {
        cout << "Nu s-a gasit angajatul cu ID " << idAngajat << "\n";
        return;
    }
    try
    {
        a->SetNume(numeNou);
        cout << "Nume modificat cu succes.\n";
    }
    catch(const exception &ex)
    {
        cerr << "Eroare la modificare: " << ex.what() << "\n";
    }
}

void Magazin::AfiseazaAngajat(int idAngajat) const
{
    Angajat *a = GasesteAngajat(idAngajat);
    if(!a)
    {
        cout << "Angajatul cu ID " << idAngajat << " nu exista.\n";
        return;
    }
    a->AfiseazaInformatii();
    cout << "Salariu curent: " << a->CalculeazaSalariuLunaCurenta() << "\n";
}

bool Magazin::ArePersonalMinimal() const
{
    int nrManageri = 0, nrOperatori = 0, nrAsistenti = 0;
    for(auto &ang : angajati)
    {
        if(dynamic_cast<Manager*>(ang.get())) nrManageri++;
        else if(dynamic_cast<OperatorComenzi*>(ang.get())) nrOperatori++;
        else if(dynamic_cast<Asistent*>(ang.get())) nrAsistenti++;
    }

    bool ok = true;
    if(nrManageri < 1)
    {
        cout << "[Atentie] Lipseste manager (avem " << nrManageri << ").\n";
        ok = false;
    }
    if(nrOperatori < 3)
    {
        cout << "[Atentie] Avem doar " << nrOperatori << " operator(i), dar trebuie minim 3.\n";
        ok = false;
    }
    if(nrAsistenti < 1)
    {
        cout << "[Atentie] Lipseste asistent (avem " << nrAsistenti << ").\n";
        ok = false;
    }
    return ok;
}

vector<Angajat*> Magazin::GetListaAngajati() const
{
    vector<Angajat*> rezultat;
    for (auto &a : angajati)
    {
        rezultat.push_back(a.get());
    }
    return rezultat;
}

// Produse
int Magazin::GetNextProdusId()
{
    return nextProdusId++;
}

void Magazin::SetNextProdusId(int val)
{
    nextProdusId = val;
}

void Magazin::AdaugaProdus(unique_ptr<Produs> produs)
{

    for(auto &p : produse)
    {
        if(p->IsIdenticCu(*produs))
        {
            p->SetStoc(p->GetStoc() + produs->GetStoc());
            cout << "[Info] Produs identic gasit. A fost marit stocul.\n";
            return;
        }
    }

    produse.push_back(move(produs));
}

bool Magazin::StergeProdus(int codProdus)
{
    for(auto it = produse.begin(); it != produse.end(); ++it)
    {
        if((*it)->GetCodUnic() == codProdus)
        {
            produse.erase(it);
            return true;
        }
    }
    return false;
}

Produs* Magazin::GasesteProdus(int codProdus) const
{
    for(auto &p : produse)
    {
        if(p->GetCodUnic() == codProdus)
        {
            return p.get();
        }
    }
    return nullptr;
}

void Magazin::AfiseazaToateProdusele() const
{
    cout << "=== Lista produse in stoc ===\n";
    for(auto &p : produse)
    {
        p->AfiseazaInformatii();
        cout << "Pret final (cu livrare): " << p->CalculeazaPretFinal() << " RON\n";
        cout << "--------------------\n";
    }
}

void Magazin::ModificaStocProdus(int codProdus, int stocNou)
{
    Produs* p = GasesteProdus(codProdus);
    if(!p)
    {
        cout << "Nu exista produs cu codul " << codProdus << "\n";
        return;
    }
    p->SetStoc(stocNou);
    cout << "Stoc actualizat pentru produsul cu cod " << codProdus << "\n";
}

void Magazin::AfiseazaProdus(int codProdus) const
{
    Produs* p = GasesteProdus(codProdus);
    if(!p)
    {
        cout << "Produsul cu codul " << codProdus << " nu exista.\n";
        return;
    }
    p->AfiseazaInformatii();
    cout << "Pret final (cu livrare): " << p->CalculeazaPretFinal() << " RON\n";
}

bool Magazin::AreStocMinimal() const
{

    int nrVest = 0, nrDisc = 0, nrVintage = 0;
    for(auto &p : produse)
    {
        if(dynamic_cast<ArticolVestimentar*>(p.get())) nrVest++;
        else if(dynamic_cast<DiscVintage*>(p.get())) nrVintage++;
        else if(dynamic_cast<Disc*>(p.get())) nrDisc++;
    }

    bool ok = true;
    if(nrVest < 2)
    {
        cout << "[Atentie] Nu exista macar 2 articole vestimentare (avem " << nrVest << ").\n";
        ok = false;
    }
    if(nrDisc < 2)
    {
        cout << "[Atentie] Nu exista macar 2 discuri (normale) (avem " << nrDisc << ").\n";
        ok = false;
    }
    if(nrVintage < 2)
    {
        cout << "[Atentie] Nu exista macar 2 discuri vintage (avem " << nrVintage << ").\n";
        ok = false;
    }

    return ok;
}

vector<Produs*> Magazin::GetListaProduse() const
{
    vector<Produs*> rez;
    for (auto &p : produse)
    {
        rez.push_back(p.get());
    }
    return rez;
}

// Comenzi
int Magazin::GetNextComandaId()
{
    return nextComandaId++;
}

void Magazin::SetNextComandaId(int val)
{
    nextComandaId = val;
}

void Magazin::AdaugaComanda(unique_ptr<Comanda> comanda)
{
    comenzi.push_back(move(comanda));
}

void Magazin::ProceseazaComenzi()
{
    if(!ArePersonalMinimal())
    {
        cout << "=== Magazinul NU are personal minimal. Nu se pot procesa comenzi. ===\n";
        return;
    }
    if(!AreStocMinimal())
    {
        cout << "=== Magazinul NU are stoc minimal. Nu se pot procesa comenzi. ===\n";
        return;
    }

    vector<OperatorComenzi*> operatori;
    for(auto &ang : angajati)
    {
        if(auto op = dynamic_cast<OperatorComenzi*>(ang.get()))
        {
            operatori.push_back(op);
        }
    }

    // map pentru operator - nr comenzi asignate
    map<OperatorComenzi*, int> comenziInProces;
    for(auto op : operatori)
    {
        comenziInProces[op] = 0; // initial toti operatorii au 0 comenzi
    }

    for(auto &cmd : comenzi)
    {
        if(cmd->EsteProcesata() || cmd->EsteInvalida())
        {
            continue;
        }


        double valBaza = 0.0;
        int nrDiscuri = 0;
        int nrVest = 0;
        bool stocOk = true;

        for(auto &pc : cmd->GetProduseComandate())
        {
            int cod = pc.first;
            int cant = pc.second;
            Produs* pr = GasesteProdus(cod);
            if(!pr)
            {
                cout << "Comanda " << cmd->GetIdComanda() << " => Produs cod " << cod << " nu exista. Comanda INVALIDA.\n";
                cmd->MarcheazaInvalida(true);
                stocOk = false;
                break;
            }
            if(pr->GetStoc() < cant)
            {
                cout << "Comanda " << cmd->GetIdComanda() << " => stoc insuficient pt produs " << cod << ". INVALIDA.\n";
                cmd->MarcheazaInvalida(true);
                stocOk = false;
                break;
            }
            if(dynamic_cast<ArticolVestimentar*>(pr))
            {
                nrVest += cant;
            }
            else if(dynamic_cast<Disc*>(pr))
            {
                nrDiscuri += cant;
            }
            valBaza += pr->GetPretBaza() * cant;
        }

        cmd->SetValoareFaraLivrare(valBaza);

        if(!stocOk)
        {
            continue;
        }
        if(nrDiscuri > 5)
        {
            cout << "Comanda " << cmd->GetIdComanda() << ": mai mult de 5 tipuri de discuri => INVALIDA.\n";
            cmd->MarcheazaInvalida(true);
            continue;
        }
        if(nrVest > 3)
        {
            cout << "Comanda " << cmd->GetIdComanda() << ": mai mult de 3 tipuri de articole vest. => INVALIDA.\n";
            cmd->MarcheazaInvalida(true);
            continue;
        }
        if(valBaza < 100.0)
        {
            cout << "Comanda " << cmd->GetIdComanda() << ": valoare < 100 RON => INVALIDA.\n";
            cmd->MarcheazaInvalida(true);
            continue;
        }

        // stoc nou
        for(auto &pc : cmd->GetProduseComandate())
        {
            Produs *pr = GasesteProdus(pc.first);
            if(pr)
            {
                pr->SetStoc(pr->GetStoc() - pc.second);
            }
        }

        double valCuLivrare = 0.0;
        for(auto &pc : cmd->GetProduseComandate())
        {
            Produs *pr = GasesteProdus(pc.first);
            if(pr)
            {
                valCuLivrare += pr->CalculeazaPretFinal() * pc.second;
            }
        }

        cmd->SetValoareTotalaCuLivrare(valCuLivrare);

        // extragem un operator cu < 3 comenzi
        OperatorComenzi* opCelMaiLiber = nullptr;
        int minCom = 3;
        for(auto &opCount : comenziInProces)
        {
            if(opCount.second < minCom && opCount.second < 3)
            {
                opCelMaiLiber = opCount.first;
                minCom = opCount.second;
            }
        }
        if(!opCelMaiLiber)
        {
            cout << "Comanda " << cmd->GetIdComanda() << " => toti operatorii sunt ocupati => ramane in asteptare.\n";
            continue;
        }
        comenziInProces[opCelMaiLiber]++;
        cmd->MarcheazaProcesata(true);
        cmd->SetIdOperator(opCelMaiLiber->GetId());
        opCelMaiLiber->AdaugaValoareComanda(valCuLivrare);

        cout << "Comanda " << cmd->GetIdComanda() << " procesata de operatorul" << opCelMaiLiber->GetNume() << " " << opCelMaiLiber->GetPrenume() << " cu ID " << opCelMaiLiber->GetId() << " (valoare totala " << valCuLivrare << ")\n";
    }
}

void Magazin::SimulareTimp(int unitati) {

    for (auto& cmd : comenzi) {

        if (!cmd->EsteProcesata() || cmd->EsteInvalida()) {
            continue;
        }

        auto dataPrimire = cmd->GetDataPrimire();
        auto timpCurent = dataPrimire + hours(24 * unitati);

        auto durataRezolvare = cmd->GetDurataRezolvare();
        auto timpScurs = duration_cast<hours>(timpCurent - dataPrimire).count() / 24;

        if (timpScurs >= durataRezolvare && !cmd->EsteFinalizata()) {
            cmd->MarcheazaFinalizata(true);
            cout << "Comanda " << cmd->GetIdComanda() << " a fost finalizata.\n";
        }
    }
}


void Magazin::AfiseazaComanda(int idComanda) const
{
    for(auto &cmd : comenzi)
    {
        if(cmd->GetIdComanda() == idComanda)
        {
            cout << "=== Comanda ID " << cmd->GetIdComanda() << " ===\n";
            cout << "Procesata? " << (cmd->EsteProcesata() ? "DA" : "NU") << "\n";
            cout << "Finalizata? " << (cmd->EsteFinalizata() ? "DA" : "NU") << "\n";
            cout << "Invalida? " << (cmd->EsteInvalida() ? "DA" : "NU") << "\n";
            cout << "Valoare fara livrare: " << cmd->GetValoareFaraLivrare() << "\n";
            cout << "Valoare totala cu livrare: " << cmd->GetValoareTotalaCuLivrare() << "\n";
            cout << "ID operator: " <<cmd->GetIdOperator() << "\n";
            cout << "Produse comandate:\n";
            for(auto &pc : cmd->GetProduseComandate())
            {
                cout << "  CodProdus= " << pc.first << ", Cantitate=" << pc.second << "\n\n";
            }

            return;
        }
    }
    cout << "Nu exista comanda cu ID-ul " << idComanda << ".\n";
}

void Magazin::AfiseazaToateComenzile_sumar() const {
    cout << "=== Toate comenzile ===\n";
    for(auto &cmd : comenzi)
    {
        cout << "Comanda ID " << cmd->GetIdComanda() << (cmd->EsteInvalida() ? " [INVALIDA]" : "") << (cmd->EsteProcesata() ? " [PROCESATA]" : " [NEPROCESATA]") << (cmd->EsteFinalizata() ? " [FINALIZATA]" : "") << "\n";
    }
}

void Magazin::AfiseazaToateComenzile_detaliu() const
{
    cout << "=== Toate comenzile ===\n";
    for(auto &cmd : comenzi)
    {
        cout << "Comanda ID " << cmd->GetIdComanda() << (cmd->EsteInvalida() ? " [INVALIDA]" : "") << (cmd->EsteProcesata() ? " [PROCESATA]" : " [NEPROCESATA]") << (cmd->EsteFinalizata() ? " [FINALIZATA]" : "") << "\n";
        AfiseazaComanda(cmd->GetIdComanda());
    }
}

const vector<unique_ptr<Comanda>>& Magazin::GetListaComenzi() const {
    return comenzi;
}

// Rapoarte
void Magazin::RaportAngajatCeleMaiMulteComenzi() const
{
    // map id operator - nr comenzi
    map<int, int> comenziPerOperator;
    for (auto &cmd : comenzi)
    {
        if (cmd->EsteProcesata() && !cmd->EsteInvalida())
        {
            int idOp = cmd->GetIdOperator();
            if (idOp != -1)
            {
                comenziPerOperator[idOp]++;
            }
        }
    }

    int maxCom = 0;
    int idOpMax = -1;
    for (auto &k : comenziPerOperator)
    {
        if (k.second > maxCom)
        {
            maxCom = k.second;
            idOpMax = k.first;
        }
    }

    if (idOpMax == -1)
    {
        cout << "[Raport] Niciun operator nu a procesat comenzi.\n";
        return;
    }

    Angajat *a = GasesteAngajat(idOpMax);
    if (a)
    {
        cout << "[Raport] Angajatul cu cele mai multe comenzi procesate: " << a->GetNume() << " " << a->GetPrenume() << " (ID=" << a->GetId() << "), nr comenzi=" << maxCom << "\n";

        ofstream fout("Raport_CeleMaiMulteComenzi.csv");
        fout << "ID;Nume;Prenume;NumarComenzi\n";
        fout << a->GetId() << ";" << a->GetNume() << ";" << a->GetPrenume() << ";" << maxCom << "\n";
        fout.close();
        cout << "[Raport] Fisier generat: Raport_CeleMaiMulteComenzi.csv\n";
    }
}

void Magazin::RaportTop3ValoareComenzi() const {
    vector<OperatorComenzi*> opers;
    for (auto &ang : angajati) {
        if (auto op = dynamic_cast<OperatorComenzi*>(ang.get())) {
            opers.push_back(op);
        }
    }

    sort(opers.begin(), opers.end(), [](OperatorComenzi* a, OperatorComenzi* b) {
        return a->GetTotalValoareComenzi() > b->GetTotalValoareComenzi();
    });

    ofstream fout("Raport_Top3ValoareComenzi.csv");
    if (!fout) {
        cerr << "Eroare la deschiderea fisierului CSV pentru scriere!\n";
        return;
    }

    fout << "ID;Nume;Prenume;Valoare Totala Comenzi\n";

    for (int i = 0; i < 3 && i < (int)opers.size(); i++) {
        fout << opers[i]->GetId() << ";" << "\"" << opers[i]->GetNume() << "\"" << ";" << "\"" << opers[i]->GetPrenume() << "\"" << ";"  << opers[i]->GetTotalValoareComenzi() << "\n";
    }

    fout.close();
    cout << "[Raport] Fisierul Raport_Top3ValoareComenzi.csv a fost generat cu succes.\n";
}

void Magazin::RaportTop3Salariu() const
{
    vector<Angajat*> angajatt;

    for (auto &ang : angajati)
    {
        angajatt.push_back(ang.get());
    }

    sort(angajatt.begin(), angajatt.end(), [](Angajat *a, Angajat *b)
    {
        double sa = a->CalculeazaSalariuLunaCurenta();
        double sb = b->CalculeazaSalariuLunaCurenta();
        if (sa == sb)
        {
            string na = a->GetNume() + " " + a->GetPrenume();
            string nb = b->GetNume() + " " + b->GetPrenume();
            return na < nb;
        }
        return sa > sb;
    });

    cout << "[Raport] Top 3 angajati dupa salariu:\n";
    ofstream fout("Raport_Top3Salarii.csv");
    fout << "ID;Nume;Prenume;Salariu\n";

    for (int i = 0; i < 3 && i < (int)angajatt.size(); i++)
    {
        cout << (i + 1) << ". " << angajatt[i]->GetNume() << " " << angajatt[i]->GetPrenume() << " => " << angajatt[i]->CalculeazaSalariuLunaCurenta() << " RON\n";
        fout << angajatt[i]->GetId() << ";" << angajatt[i]->GetNume() << ";" << angajatt[i]->GetPrenume() << ";" << angajatt[i]->CalculeazaSalariuLunaCurenta() << "\n";
    }

    fout.close();
    cout << "[Raport] Fisier generat: Raport_Top3Salarii.csv\n";
}
