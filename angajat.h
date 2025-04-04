#pragma once
#include<string>
#include<chrono>
using namespace std;

class Angajat {
protected:

    int id;
    string nume;
    string prenume;
    string cnp;

    int ziNastere;
    int lunaNastere;
    int anNastere;

    chrono::system_clock::time_point dataAngajare;

    static constexpr double SALARIU_BAZA = 3500.0;

    bool ValidareCNP(const string cnp) const;
    bool ExtrageDataNastereDinCNP(string cnp, int &zi, int &luna, int &an) const;
    bool VerificaMajorLaDataAngajarii() const;

public:
    Angajat(int id, string nume, string prenume, string cnp, chrono::system_clock::time_point dataAngajare);
    virtual ~Angajat() = default;

    int GetId() const;
    string GetNume() const;
    string GetPrenume() const;
    string GetCNP() const;
    chrono::system_clock::time_point GetDataAngajare() const;

    void SetNume(string numeNou);
    void SetPrenume(string prenumeNou);

    int CalculeazaVechimeInAni() const;

    virtual double CalculeazaSalariuLunaCurenta() const = 0;
    virtual void AfiseazaInformatii() const;
    virtual bool EsteZiuaDeNastere() const;

};
