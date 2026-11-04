
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <emscripten/bind.h>

using namespace std;

struct dane {
    string id;
    string data;
    double temperatura;
    double wiatr;
};

class pomiary {
    vector<dane> Dane;

public:

    // Wczytywanie danych z tekstu
    void wczytywanieTekstu(const string& tekst)
    {
        Dane.clear();

        stringstream plik(tekst);
        string napis;

        while (getline(plik, napis))
        {
            if (napis.empty())
                continue;

            try
            {
                stringstream linia(napis);
                vector<string> pola;
                string pole;

                while (getline(linia, pole, ';'))
                {
                    pola.push_back(pole);
                }

                if (pola.size() < 4)
                    continue;

                dane pomiar;

                pomiar.id = pola[0];
                pomiar.data = pola[1];
                pomiar.temperatura = stod(pola[2]);
                pomiar.wiatr = stod(pola[3]);

                Dane.push_back(pomiar);
            }
            catch (...)
            {
                continue;
            }
        }
    }

    // Pobieranie wszystkich pomiarów
    vector<dane> pobierzWszystkie()
    {
        return Dane;
    }

    // Sprawdzenie, czy są dane
    bool czySaDane()
    {
        return !Dane.empty();
    }

    // Znalezienie minimalnej temperatury
    dane minimalnaTemperatura()
    {
        if (Dane.empty())
            throw runtime_error("Brak danych");

        dane najzimniejszy = Dane[0];

        for (int i = 1; i < Dane.size(); i++)
        {
            if (Dane[i].temperatura < najzimniejszy.temperatura)
            {
                najzimniejszy = Dane[i];
            }
        }

        return najzimniejszy;
    }

    // Wyszukiwanie pomiarów powyżej progu
    vector<dane> szukajPowyzejProgu(double progTemperatury)
    {
        vector<dane> znalezione;

        for (int i = 0; i < Dane.size(); i++)
        {
            if (Dane[i].temperatura > progTemperatury)
            {
                znalezione.push_back(Dane[i]);
            }
        }

        return znalezione;
    }
};


// Obiekt klasy
pomiary Pomiar;


// Funkcje dla JavaScript

void wczytajDane(string tekst)
{
    Pomiar.wczytywanieTekstu(tekst);
}

vector<dane> pobierzDane()
{
    return Pomiar.pobierzWszystkie();
}

bool czySaDane()
{
    return Pomiar.czySaDane();
}

dane pobierzMinimum()
{
    return Pomiar.minimalnaTemperatura();
}

vector<dane> szukaj(double prog)
{
    return Pomiar.szukajPowyzejProgu(prog);
}


// Główna funkcja programu
int main()
{
    cout << "Stacja pogodowa uruchomiona!" << endl;
    return 0;
}


// Udostępnienie funkcji dla JavaScript
EMSCRIPTEN_BINDINGS(pogoda)
{
    emscripten::value_object<dane>("dane")
        .field("id", &dane::id)
        .field("data", &dane::data)
        .field("temperatura", &dane::temperatura)
        .field("wiatr", &dane::wiatr);

    emscripten::register_vector<dane>("VectorDane");

    emscripten::function("wczytajDane", &wczytajDane);
    emscripten::function("pobierzDane", &pobierzDane);
    emscripten::function("czySaDane", &czySaDane);
    emscripten::function("pobierzMinimum", &pobierzMinimum);
    emscripten::function("szukaj", &szukaj);
}
