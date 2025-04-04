#pragma once
#include <iostream>
#include <limits>
#include <chrono>
using namespace std;


inline int CitesteInt(string mesaj) {
    while (true) {
        cout << mesaj;
        int val;
        cin >> val;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Valoare invalida, te rog introdu un numar intreg.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        }
    }
}

inline double CitesteDouble(string mesaj) {
    while (true) {
        cout << mesaj;
        double val;
        cin >> val;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Valoare invalida, te rog introdu un numar real.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        }
    }
}


inline chrono::year_month_day CitesteDataCalendaristica(string tipData) {
    while(true) {
        cout << "Introdu " << tipData << " (format: an luna zi, separate prin spatiu): ";
        int an, luna, zi;
        cin >> an >> luna >> zi;

        if(cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Valori invalide. Reincearca.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        chrono::year y{an};
        chrono::month m{static_cast<unsigned>(luna)};
        chrono::day d{static_cast<unsigned>(zi)};

        chrono::year_month_day ymd{y, m, d};
        if(!ymd.ok()) {
            cerr << "Data invalida (ex: 30 februarie). Reincearca.\n";
            continue;
        }
        if(an < 1900 || an > 2026) {
            cerr << "Anul introdus (" << an << ") nu este valid. Reincearca.\n";
            continue;
        }
        return ymd;
    }
}

inline chrono::system_clock::time_point ToSysTime(chrono::year_month_day ymd) {

    chrono::sys_days sd{ymd};
    return chrono::system_clock::time_point(sd);
}

