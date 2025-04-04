#include "angajat.h"
#include<stdexcept>
#include<iostream>
#include<cctype>
#include<ctime>
#include<chrono>

using namespace std;
using namespace std::chrono;

Angajat::Angajat(int id, string nume, string prenume, string cnp, chrono::system_clock::time_point dataAngajare): id(id), dataAngajare(dataAngajare)
{
    if(nume.size() < 3 || nume.size() > 30) {
        throw invalid_argument("Numele trebuie sa aiba intre 3 si 30 de caractere.\n");
    }
    if(prenume.size() < 3 || prenume.size() > 30) {
        throw invalid_argument("Prenumele trebuie sa aiba intre 3 si 30 de caractere.\n");
    }

    if(!ValidareCNP(cnp)) {
        throw invalid_argument("CNP invalid!\n");
    }

    int ziN, lunaN, anN;
    if(!ExtrageDataNastereDinCNP(cnp, ziN, lunaN, anN)) {
        throw invalid_argument("Data nasterii din CNP este invalida!\n");
    }

    ziNastere = ziN;
    lunaNastere = lunaN;
    anNastere = anN;

    if(!VerificaMajorLaDataAngajarii()) {
        throw invalid_argument("Angajat minor.\n");
    }

    this->nume = nume;
    this->prenume = prenume;
    this->cnp = cnp;
}

bool Angajat::ValidareCNP(const string cnp) const {
    if(cnp.size() != 13) {
        return false;
    }
    for(char c : cnp) {
        if(!isdigit(c)) {
            return false;
        }
    }

    static int coef[12] = {2,7,9,1,4,6,3,5,8,2,7,9};
    int suma = 0;
    for(int i = 0; i < 12; i++){
        suma += (cnp[i] - '0') * coef[i];
    }
    int rest = suma % 11;
    int cifraControl = (rest == 10) ? 1 : rest;

    if((cnp[12] - '0') != cifraControl) {
        return false;
    }
    return true;
}

bool Angajat::ExtrageDataNastereDinCNP(string cnp, int &zi, int &luna, int &an) const {

    int s = cnp[0] - '0';
    int aa = stoi(cnp.substr(1,2));
    int ll = stoi(cnp.substr(3,2));
    int zz = stoi(cnp.substr(5,2));

    int secol = 1900;
    if(s == 1 || s == 2) {
        secol = 1900;
    } else if(s == 3 || s == 4) {
        secol = 1800;
    } else if(s == 5 || s == 6) {
        secol = 2000;
    }
    an = secol + aa;
    luna = ll;
    zi = zz;

    if(luna < 1 || luna > 12) return false;
    if(zi < 1 || zi > 31) return false;

    bool ziValida = false;
    switch(luna) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            ziValida = (zi >=1 && zi <=31);
            break;
        case 4: case 6: case 9: case 11:
            ziValida = (zi >=1 && zi <=30);
            break;
        case 2:
            if((an % 400 == 0) || ((an % 4 == 0) && (an % 100 != 0))) {
                ziValida = (zi >=1 && zi <=29);
            } else {
                ziValida = (zi >=1 && zi <=28);
            }
            break;
        default:
            ziValida = false;
    }
    return ziValida;
}

bool Angajat::VerificaMajorLaDataAngajarii() const {

    year_month_day dataNastere{year(this->anNastere),month(this->lunaNastere),day(this->ziNastere)};
    year_month_day dataAng{ floor<days>(dataAngajare) };

    int diffYears = (int)( (int) dataAng.year() - (int) dataNastere.year() );

    if(diffYears > 18) {
        return true;
    }
    else if(diffYears < 18) {
        return false;
    }
    else {
        if(dataAng.month() > dataNastere.month()) {
            return true;
        }
        else if(dataAng.month() < dataNastere.month()) {
            return false;
        }
        else {
            return (dataAng.day() >= dataNastere.day());
        }
    }
}

int Angajat::GetId() const {
    return id;
}

string Angajat::GetNume() const {
    return nume;
}

string Angajat::GetPrenume() const {
    return prenume;
}

string Angajat::GetCNP() const {
    return cnp;
}

chrono::system_clock::time_point Angajat::GetDataAngajare() const {
        return dataAngajare;
    }

void Angajat::SetNume(string numeNou) {
    if(numeNou.size() < 3 || numeNou.size() > 30) {
        throw invalid_argument("Numele trebuie sa aiba intre 3 si 30 caractere.");
    }
    nume = numeNou;
}

void Angajat::SetPrenume(string prenumeNou) {
    if(prenumeNou.size() < 3 || prenumeNou.size() > 30) {
        throw invalid_argument("Prenumele trebuie sa aiba intre 3 si 30 caractere.");
    }
    prenume = prenumeNou;
}

int Angajat::CalculeazaVechimeInAni() const {

    year_month_day dataAngajarii = year_month_day(floor<days>(dataAngajare));
    year_month_day dataCurenta = year_month_day(floor<days>(system_clock::now()));

    years diferentaAni = dataCurenta.year() - dataAngajarii.year();

    if ( dataCurenta.month() < dataAngajarii.month() || (dataCurenta.month() == dataAngajarii.month() && dataCurenta.day() < dataAngajarii.day()) )
                diferentaAni -= years{1};

    return static_cast<int>(diferentaAni.count());
}

void Angajat::AfiseazaInformatii() const {
    cout << "ID: " << id << ", Nume: " << nume << ", Prenume: " << prenume << ", CNP: " << cnp << "\n";
}

bool Angajat::EsteZiuaDeNastere() const {

    time_t t = time(nullptr);
    tm *ptm = localtime(&t);
    int ziCurenta = ptm->tm_mday;
    int lunaCurenta = ptm->tm_mon + 1;

    return (ziNastere == ziCurenta && lunaNastere == lunaCurenta);
}

