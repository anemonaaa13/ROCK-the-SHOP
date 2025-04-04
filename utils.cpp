#pragma once
#include <iostream>
#include <limits>
#include <chrono>
using namespace std;

/*
 * Funcții ajutătoare pentru citiri robuste de la tastatură
 */

inline int CitesteInt(const string &mesaj) {
    while (true) {
        cout << mesaj;
        int val;
        cin >> val;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cerr << "Valoare invalida, te rog introdu un numar intreg.\n";
        } else {
            // curatam eventuala linie
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return val;
        }
    }
}

inline double CitesteDouble(const string &mesaj) {
    while (true) {
        cout << mesaj;
        double val;
        cin >> val;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cerr << "Valoare invalida, te rog introdu un numar real.\n";
        } else {
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return val;
        }
    }
}

/*
 * Citirea unei date calendaristice (YYYY, MM, DD) sub forma year_month_day,
 * cu validare minimală.
 */
inline chrono::year_month_day CitesteDataCalendaristica(const string &tipData) {
    while(true) {
        cout << "Introdu " << tipData << " (format: an luna zi, separate prin spatiu): ";
        int an, luna, zi;
        cin >> an >> luna >> zi;

        if(cin.fail()) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cerr << "Valori invalide. Reincearca.\n";
            continue;
        }
        // Golim restul liniei
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Construim year_month_day
        chrono::year y{an};
        chrono::month m{static_cast<unsigned>(luna)};
        chrono::day d{static_cast<unsigned>(zi)};

        chrono::year_month_day ymd{y, m, d};
        if(!ymd.ok()) {
            cerr << "Data invalida (ex: 30 februarie). Reincearca.\n";
            continue;
        }
        // conditii minime, ex: an > 1900 si < 2100
        if(an < 1900 || an > 2100) {
            cerr << "Anul introdus (" << an << ") nu pare valid. Reincearca.\n";
            continue;
        }
        return ymd;
    }
}

/*
 * Transformă un chrono::year_month_day într-un time_point<system_clock>
 * la ora 00:00.
 */
inline chrono::system_clock::time_point ToSysTime(const chrono::year_month_day &ymd) {
    // sys_days e un alias pentru time_point<system_clock, days>
    chrono::sys_days sd{ymd};
    return chrono::system_clock::time_point(sd);
}

