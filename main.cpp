#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <string.h>
#include "magazin.h"
#include "utils.h"
using namespace std;
using namespace chrono;

void IncarcaAngajatiDinFisier(Magazin &mag, string numeFisier)
{
    ifstream fin(numeFisier);
    if(!fin)
    {
        cerr << "Nu s-a putut deschide fisierul " << numeFisier << " pentru citire.\n";
        return;
    }

    string line;
    while(getline(fin, line))
    {
        if(line.empty()) continue;

        // ID|TipAngajat|Nume|Prenume|CNP|YYYY|MM|DD
        stringstream ss(line);
        string aux, tipAngajat, nume, prenume, cnp;
        int id, yy, mm, dd;

        if(!getline(ss, aux, '|')) continue;
        id = stoi(aux);

        if(!getline(ss, tipAngajat, '|')) continue;
        if(!getline(ss, nume, '|')) continue;
        if(!getline(ss, prenume, '|')) continue;
        if(!getline(ss, cnp, '|')) continue;

        if(!getline(ss, aux, '|')) continue;
        yy = stoi(aux);
        if(!getline(ss, aux, '|')) continue;
        mm = stoi(aux);
        if(!getline(ss, aux, '|')) continue;
        dd = stoi(aux);

        year_month_day dataAngajare{ year(yy), month(mm), day(dd)};
        auto tpAng = ToSysTime(dataAngajare);

        try
        {
            unique_ptr<Angajat> ptr;

            if(tipAngajat == "Manager")
            {
                ptr = make_unique<Manager>(id, nume, prenume, cnp, tpAng);
            }
            else if(tipAngajat == "OperatorComenzi")
            {
                ptr = make_unique<OperatorComenzi>(id, nume, prenume, cnp, tpAng);
            }
            else if(tipAngajat == "Asistent")
            {
                ptr = make_unique<Asistent>(id, nume, prenume, cnp, tpAng);
            }
            else
            {

                cerr << "[Eroare] Tip de angajat necunoscut: " << tipAngajat << " (linia: " << line << ")\n";
                continue;
            }

            mag.AdaugaAngajat(move(ptr));
            if (id >= mag.GetNextAngajatId()) {
                mag.SetNextAngajatId(id + 1);
}

        }
        catch(const exception &ex)
        {
            cerr << "Eroare la crearea angajatului (linia: " << line << ")\n" << ex.what() << "\n";
        }
    }
    fin.close();
}

void IncarcaProduseDinFisier(Magazin &mag, string numeFisier)
{

    // IDProdus|TipProdus|Denumire|Stoc|PretBaza|(apoi campuri specifice)

    ifstream fin(numeFisier);
    if(!fin)
    {
        cerr << "Nu s-a putut deschide fisierul " << numeFisier << " pentru citire.\n";
        return;
    }

    string line;
    while(getline(fin, line))
    {
        if(line.empty()) continue;
        stringstream ss(line);
        string aux;

        int idProd, stoc;
        string tip, denumire;
        double pretBaza;

        if(!getline(ss, aux, '|')) continue;
        idProd = stoi(aux);

        if(!getline(ss, tip, '|')) continue;
        if(!getline(ss, denumire, '|')) continue;

        if(!getline(ss, aux, '|')) continue;
        stoc = stoi(aux);

        if(!getline(ss, aux, '|')) continue;
        pretBaza = stod(aux);

        try
        {
            if(tip == "ArticolVestimentar")
            {

                string culoare, marca;
                if(!getline(ss, culoare, '|')) continue;
                if(!getline(ss, marca, '|')) continue;

                auto ptr = make_unique<ArticolVestimentar>(idProd, denumire, stoc, pretBaza, culoare, marca);
                mag.AdaugaProdus(move(ptr));
            }
            else if(tip == "Disc")
            {
                // CasaDeDiscuri|YYYY|MM|DD|Trupa|Album|CD/VINIL
                string casa, trupa, album, tipDiscStr;
                int yy, mm, dd;

                if(!getline(ss, casa, '|')) continue;
                if(!getline(ss, aux, '|')) continue;
                yy = stoi(aux);
                if(!getline(ss, aux, '|')) continue;
                mm = stoi(aux);
                if(!getline(ss, aux, '|')) continue;
                dd = stoi(aux);

                if(!getline(ss, trupa, '|')) continue;
                if(!getline(ss, album, '|')) continue;
                if(!getline(ss, tipDiscStr, '|')) continue;

                year_month_day dataLansare{year(yy),month(mm),day(dd)};
                system_clock::time_point tp = ToSysTime(dataLansare);

                TipDisc tipDiscVal = (tipDiscStr == "CD") ? TipDisc::CD : TipDisc::VINIL;

                auto ptr = make_unique<Disc>(idProd, denumire, stoc, pretBaza, casa, tp, trupa, album, tipDiscVal);
                mag.AdaugaProdus(move(ptr));
            }
            else if(tip == "DiscVintage")
            {
                // Casa|YYYY|MM|DD|Trupa|Album|CD/VINIL|mint(0/1)|coefRaritate
                string casa, trupa, album, tipDiscStr;
                int yy, mm, dd, mintInt, coefRar;

                if(!getline(ss, casa, '|')) continue;
                if(!getline(ss, aux, '|')) continue;
                yy = stoi(aux);
                if(!getline(ss, aux, '|')) continue;
                mm = stoi(aux);
                if(!getline(ss, aux, '|')) continue;
                dd = stoi(aux);

                if(!getline(ss, trupa, '|')) continue;
                if(!getline(ss, album, '|')) continue;
                if(!getline(ss, tipDiscStr, '|')) continue;

                if(!getline(ss, aux, '|')) continue;
                mintInt = stoi(aux);
                if(!getline(ss, aux, '|')) continue;
                coefRar = stoi(aux);

                year_month_day dataLansare{year(yy),month(mm),day(dd)};
                system_clock::time_point tp = ToSysTime(dataLansare);

                TipDisc tipDiscVal = (tipDiscStr == "CD") ? TipDisc::CD : TipDisc::VINIL;
                bool eMint = (mintInt == 1);

                auto ptr = make_unique<DiscVintage>(idProd, denumire, stoc, pretBaza,casa, tp, trupa, album, tipDiscVal, eMint, coefRar);
                mag.AdaugaProdus(move(ptr));
            }
            else
            {
                cerr << "[Eroare] Tip produs necunoscut: " << tip << "\n";
                continue;
            }

            if(idProd >= mag.GetNextProdusId())
            {
                mag.SetNextProdusId(idProd + 1);
            }

        }
        catch(const exception &ex)
        {
            cerr << "Eroare la crearea produsului din linia:\n" << line << "\n" << ex.what() << "\n";
        }
    }
    fin.close();
}

void IncarcaComenziDinFisier(Magazin &mag, string numeFisier)
{

    ifstream fin(numeFisier);
    if(!fin)
    {
        cerr << "Nu s-a putut deschide fisierul " << numeFisier << " pentru citire.\n";
        return;
    }

    string line;
    while(getline(fin, line))
    {
        if(line.empty()) continue;

        // Format: IDComanda|YYYY|MM|DD|durataRezolvare|(cod1,cant1) (cod2,cant2) ...
        stringstream ss(line);
        string aux;

        if(!getline(ss, aux, '|')) continue;
        int idC = stoi(aux);

        if(!getline(ss, aux, '|')) continue;
        int yy = stoi(aux);

        if(!getline(ss, aux, '|')) continue;
        int mm = stoi(aux);

        if(!getline(ss, aux, '|')) continue;
        int dd = stoi(aux);

        year_month_day dataPrimire{ year(yy), month(mm), day(dd)};
        system_clock::time_point tp = ToSysTime(dataPrimire);

        if(!getline(ss, aux, '|')) continue;
        int durata = stoi(aux);

        string produseStr;
        if(!getline(ss, produseStr)) {}

        Comanda c(idC, tp, durata);

        // format: (cod1,cant1) (cod2,cant2)
        stringstream ssp(produseStr);
        while(getline(ssp, aux, ' '))
        {
            if(aux.empty()) continue;

            if(aux.front() == '(')
            {
                aux.erase(0,1); // elimin parantezele
            }
            if(!aux.empty() && aux.back() == ')')
            {
                aux.pop_back();
            }

            // aux = "cod,cant"
            auto p = aux.find(',');
            if(p == string::npos) continue;
            int cod = stoi(aux.substr(0, p));
            int cant = stoi(aux.substr(p+1));

            c.AdaugaProdus(cod, cant);
        }

        auto ptrComanda = make_unique<Comanda>(move(c));
        mag.AdaugaComanda(move(ptrComanda));

        if(idC >= mag.GetNextComandaId())
        {
            mag.SetNextComandaId(idC + 1);
        }

    }
    fin.close();
}

void MeniuGestiuneAngajati(Magazin &m)
{
    bool gata = false;
    while(!gata)
    {
        cout << "\n--- Meniu Gestiune Angajati ---\n";
        cout << "1. Adauga angajat\n";
        cout << "2. Sterge angajat\n";
        cout << "3. Modifica nume\n";
        cout << "4. Afiseaza angajat\n";
        cout << "5. Afiseaza toti angajatii\n";
        cout << "0. Inapoi\n";
        int opt = CitesteInt("Alege: ");

        switch(opt)
        {
        case 1:
        {
            cout << "Tip (1-Manager, 2-Operator, 3-Asistent): ";
            int tip;
            cin >> tip;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Nume: ";
            string nume;
            getline(cin, nume);

            cout << "Prenume: ";
            string prenume;
            getline(cin, prenume);

            cout << "CNP: ";
            string cnp;
            getline(cin, cnp);

            cout << "Data angajarii: \n";
            year_month_day ymdAng = CitesteDataCalendaristica("data angajarii");
            system_clock::time_point tpAng = ToSysTime(ymdAng);

            int ID_curent = m.GetNextAngajatId();
            try
            {
                unique_ptr<Angajat> ptr;
                if(tip == 1)
                {
                    ptr = make_unique<Manager>(ID_curent, nume, prenume, cnp, tpAng);
                }
                else if(tip == 2)
                {
                    ptr = make_unique<OperatorComenzi>(ID_curent, nume, prenume, cnp, tpAng);
                }
                else if(tip == 3)
                {
                    ptr = make_unique<Asistent>(ID_curent, nume, prenume, cnp, tpAng);
                }
                else
                {
                    cerr << "Tip invalid!\n";
                    break;
                }
                m.AdaugaAngajat(move(ptr));
                m.IncrementNextAngajatId();
                cout << "Angajat adaugat cu succes, ID=" << ID_curent << "\n";
            }
            catch(const exception &ex)
            {
                cerr << "Eroare: " << ex.what() << "\n";
            }
        }
        break;
        case 2:
        {
            int ID_de_sters = CitesteInt("ID angajat de sters: ");
            if(m.StergeAngajat(ID_de_sters))
            {
                cout << "Angajat sters cu succes.\n";
            }
            else
            {
                cout << "Nu s-a gasit angajatul.\n";
            }
        }
        break;
        case 3:
        {
            int ID_modif = CitesteInt("ID angajat: ");
            cout << "Nume nou: ";
            string nn;
            cin >> nn;

            m.ModificaNumeAngajat(ID_modif, nn);
        }
        break;
        case 4:
        {
            int ID_afisare = CitesteInt("ID angajat: ");
            m.AfiseazaAngajat(ID_afisare);
        }
        break;
        case 5:
        {
            m.AfiseazaTotiAngajatii();
        }
        break;
        case 0:
            gata = true;
            break;
        default:
            cerr << "Optiune invalida!\n";
        }
    }
}

void MeniuGestiuneStoc(Magazin &m)
{
    bool gata = false;
    while(!gata)
    {
        cout << "\n--- Meniu Gestiune Stoc ---\n";
        cout << "1. Adauga produs\n";
        cout << "2. Sterge produs\n";
        cout << "3. Modifica stoc\n";
        cout << "4. Afiseaza produs\n";
        cout << "5. Afiseaza toate produsele\n";
        cout << "0. Inapoi\n";
        int opt = CitesteInt("Alege: ");

        switch(opt)
        {
        case 1:
        {
            cout << "Tip produs (1 - Articol Vest, 2 - Disc, 3 - DiscVintage): ";
            int tip;
            cin >> tip;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Denumire: ";
            string den;
            getline(cin, den);

            int stoc = CitesteInt("Stoc: ");
            double pretBaza = CitesteDouble("PretBaza: ");

            int newId = m.GetNextProdusId();
            if(tip == 1)
            {
                cout << "Culoare: ";
                string cul;
                cin >> cul;
                cout << "Marca: ";
                string mar;
                cin >> mar;
                m.AdaugaProdus(make_unique<ArticolVestimentar>(newId, den, stoc, pretBaza, cul, mar));
                cout << "Produs adaugat.\n";
            }
            else if(tip == 2)
            {
                cout << "Data lansare (YYYY MM DD)\n";
                year_month_day ymd = CitesteDataCalendaristica("data lansarii");
                system_clock::time_point tp = ToSysTime(ymd);

                cout << "Casa de discuri: ";
                string casa;
                cin >> casa;

                cout << "Trupa: ";
                string tr;
                cin >> tr;

                cout << "Album: ";
                string alb;
                cin >> alb;

                cout << "Tip disc (1 - CD, 2 - VINIL): ";
                int tdisc;
                cin >> tdisc;
                TipDisc td = (tdisc == 1 ? TipDisc::CD : TipDisc::VINIL);

                m.AdaugaProdus(make_unique<Disc>(newId, den, stoc, pretBaza, casa, tp, tr, alb, td));
                cout << "Disc adaugat.\n";
            }
            else if(tip == 3)
            {
                cout << "Data lansare (YYYY MM DD)\n";
                year_month_day ymd = CitesteDataCalendaristica("data lansarii");
                system_clock::time_point tp = ToSysTime(ymd);

                cout << "Casa de discuri: ";
                string casa;
                cin >> casa;

                cout << "Trupa: ";
                string tr;
                cin >> tr;

                cout << "Album: ";
                string alb;
                cin >> alb;

                cout << "Tip disc (1 - CD, 2 - VINIL): ";
                int tdisc;
                cin >> tdisc;
                TipDisc td = (tdisc == 1 ? TipDisc::CD : TipDisc::VINIL);

                cout << "Mint? (1-da,0-nu): ";
                int mm;
                cin >> mm;
                bool eMint = (mm == 1);

                int cr = CitesteInt("Coef raritate [1..5]: ");

                m.AdaugaProdus(make_unique<DiscVintage>( newId, den, stoc, pretBaza, casa, tp, tr, alb, td, eMint, cr));
                cout << "DiscVintage adaugat.\n";
            }
            else
            {
                cerr << "Tip invalid!\n";
            }
        }
        break;
        case 2:
        {
            int cod = CitesteInt("Cod produs: ");
            if(m.StergeProdus(cod))
            {
                cout << "Produs sters.\n";
            }
            else
            {
                cout << "Nu exista produs cu acest cod.\n";
            }
        }
        break;
        case 3:
        {
            int cod = CitesteInt("Cod produs: ");
            int stocN = CitesteInt("Stoc nou: ");
            m.ModificaStocProdus(cod, stocN);
        }
        break;
        case 4:
        {
            int cod = CitesteInt("Cod produs: ");
            m.AfiseazaProdus(cod);
        }
        break;
        case 5:
        {
            m.AfiseazaToateProdusele();
        }
        break;
        case 0:
            gata = true;
            break;
        default:
            cerr << "Optiune invalida!\n";
        }
    }
}

void MeniuComenzi(Magazin &m)
{
    bool gata = false;
    while(!gata)
    {
        cout << "\n--- Meniu Comenzi ---\n";
        cout << "1. Adauga comanda\n";
        cout << "2. Proceseaza comenzi\n";
        cout << "3. Simulare timp (finalizare)\n";
        cout << "4. Afiseaza comanda\n";
        cout << "5. Afiseaza lista comenzi\n";
        cout << "6. Afiseaza detalii comenzi\n";
        cout << "0. Inapoi\n";
        int opt = CitesteInt("Alege: ");
        switch(opt)
        {
        case 1:
        {
            int idC = m.GetNextComandaId();
            cout << "Data primire comanda (YYYY MM DD) ---\n";
            year_month_day ymd = CitesteDataCalendaristica("data primire");
            system_clock::time_point tp = ToSysTime(ymd);

            int durata = CitesteInt("Durata de rezolvare (unitati de timp): ");
            Comanda c(idC, tp, durata);

            int nr = CitesteInt("Cate produse in comanda? ");
            for(int i=0; i<nr; i++)
            {
                int cod = CitesteInt("Cod produs: ");
                int cant = CitesteInt("Cantitate: ");
                c.AdaugaProdus(cod, cant);
            }
            auto ptrComanda = make_unique<Comanda>(move(c));
            m.AdaugaComanda(move(ptrComanda));

            cout << "Comanda adaugata, ID=" << idC << "\n";
        }
        break;
        case 2:
            m.ProceseazaComenzi();
            break;
        case 3:
        {
            int u = CitesteInt("Cate unitati de timp avansezi? ");
            m.SimulareTimp(u);
        }
        break;
        case 4:
        {
            int idc = CitesteInt("ID comanda: ");
            m.AfiseazaComanda(idc);
        }
        break;
        case 5:
        {
            m.AfiseazaToateComenzile_sumar();
        }
        break;
        case 6:
        {
             m.AfiseazaToateComenzile_detaliu();
        }
        case 0:
            gata = true;
            break;
        default:
            cerr << "Optiune invalida!\n";
        }
    }
}

void MeniuRaportari(Magazin &m)
{
    bool gata = false;
    while(!gata)
    {
        cout << "\n--- Meniu Raportari ---\n";
        cout << "1. Angajatul cu cele mai multe comenzi procesate\n";
        cout << "2. Top 3 angajati cu cele mai valoroase comenzi\n";
        cout << "3. Top 3 angajati dupa salariu\n";
        cout << "0. Inapoi\n";
        int opt = CitesteInt("Alege: ");

        switch(opt)
        {
        case 1:
            m.RaportAngajatCeleMaiMulteComenzi();
            break;
        case 2:
            m.RaportTop3ValoareComenzi();
            break;
        case 3:
            m.RaportTop3Salariu();
            break;
        case 0:
            gata = true;
            break;
        default:
            cerr << "Optiune invalida!\n";
        }
    }
}

int main()
{
    Magazin magazin;

    IncarcaAngajatiDinFisier(magazin, "angajati.txt");
    IncarcaProduseDinFisier(magazin, "produse.txt");
    IncarcaComenziDinFisier(magazin, "comenzi.txt");

    bool gata = false;
    while(!gata)
    {
        cout << "\n===== MENIU PRINCIPAL ROCK the SHOP =====\n";
        cout << "1. Gestiune Angajati\n";
        cout << "2. Gestiune Stoc\n";
        cout << "3. Procesare Comenzi\n";
        cout << "4. Raportari\n";
        cout << "5. Verifica stare magazin (personal/stoc minimal)\n";
        cout << "0. Iesire\n";
        int opt = CitesteInt("Alege optiunea: ");

        switch(opt)
        {
        case 1:
            MeniuGestiuneAngajati(magazin);
            break;
        case 2:
            MeniuGestiuneStoc(magazin);
            break;
        case 3:
            MeniuComenzi(magazin);
            break;
        case 4:
            MeniuRaportari(magazin);
            break;
        case 5:
        {
            bool okPers = magazin.ArePersonalMinimal();
            bool okStoc = magazin.AreStocMinimal();
            if(!okPers)
            {
                cout << "Magazinul NU poate functiona: personal insuficient.\n";
            }
            else
            {
                cout << "Personalul este suficient.\n";
            }
            if(!okStoc)
            {
                cout << "Magazinul NU poate functiona: stoc insuficient.\n";
            }
            else
            {
                cout << "Stocul este suficient.\n";
            }
        }
        break;
        case 0:
            gata = true;
            break;
        default:
            cerr << "Optiune invalida!\n";
        }
    }

    cout << "Program terminat.\n";
    return 0;
}

