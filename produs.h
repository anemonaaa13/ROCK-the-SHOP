#pragma once
#include <string>
using namespace std;

class Produs {
protected:
    int codUnic;
    string denumire;
    int stoc;
    double pretBaza;

public:
    Produs(int codUnic, string denumire, int stoc, double pretBaza);
    virtual ~Produs() = default;

    int GetCodUnic() const;
    string GetDenumire() const;
    int GetStoc() const;
    double GetPretBaza() const;

    void SetDenumire(string denumireNoua);
    void SetStoc(int stocNou);
    void SetPretBaza(double pretNou);

    virtual double CalculeazaPretFinal() const = 0;
    virtual void AfiseazaInformatii() const = 0;
    virtual bool IsIdenticCu(const Produs &) const = 0;
};
