#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
struct dane{
    string id;
    string data;
    double temperatura;
    double wiatr;
};
class pomiary{
    vector<dane> Dane;

    public:

    void wczytywanie()
    {
        try
        {
            fstream plik;
            string napis;
            plik.open("a.txt", ios::in);
            if(!plik.is_open())
            {
                throw runtime_error("Blad otwarcia pliku");
            }
            while(getline(plik, napis))
            {
                dane pomiar;
                int poz1=napis.find(';');
                pomiar.id=napis.substr(0, poz1);

                int poz2=napis.find(';', poz1+1);
                pomiar.data=napis.substr(poz1+1, poz2-poz1-1);

                int poz3=napis.find(';', poz2+1);
                pomiar.temperatura=stod(napis.substr(poz2+1, poz3-poz2-1));
                pomiar.wiatr=stod(napis.substr(poz3+1));
                Dane.push_back(pomiar);
            }
            plik.close();
        }
        catch(const exception& e)
        {
            cout<<"Blad: "<<e.what()<<endl;
        }
    }
    void wypisz()
    {
        for(int i=0; i<Dane.size(); i++)
        {
            cout<<"ID: "<<Dane[i].id<<" ";
            cout<<"Data: "<<Dane[i].data<<" ";
            cout<<"Temperatura: "<<Dane[i].temperatura<<" ";
            cout<<"Wiatr: "<<Dane[i].wiatr<<" ";
            cout<<endl;
        }
    }
    void minimalnaTemperatura()
    {
        if(Dane.empty())
        {
            cout<<"Brak danych w bazie, nie mozna wyznaczyc minimum."<<endl;
            return;
        }
        dane najzimniejszy=Dane[0];
        for (int i=1; i<Dane.size(); i++)
        {
            if(Dane[i].temperatura<najzimniejszy.temperatura)
            {
                najzimniejszy=Dane[i];
            }
        }
        cout<<"ID: "<<najzimniejszy.id<<" ";
        cout<<"Data: "<<najzimniejszy.data<<" ";
        cout<<"Temperatura: "<<najzimniejszy.temperatura<<" ";
        cout<<"Wiatr: "<<najzimniejszy.wiatr<<endl;
    }
    vector<dane> szukajPowyzejProgu(double progTemperatury)
    {
        vector<dane> znalezione;
        for(int i=0; i<Dane.size(); i++)
        {
            if(Dane[i].temperatura>progTemperatury)
            {
                znalezione.push_back(Dane[i]);
            }
        }
        return znalezione;
    }
};
int main()
{
    pomiary Pomiar;
    Pomiar.wczytywanie();
    Pomiar.wypisz();
    cout<<endl;
    cout<<"Temperatura minimalna: "<<endl;
    Pomiar.minimalnaTemperatura();
    cout<<endl;
    double prog;
    cout<<"Podaj prog temperatury: ";
    if(!(cin>>prog))
    {
        cout<<"Blad: Wprowadzono niepoprawna liczbe!"<<endl;
        return 1;
    }
    vector<dane> wynikiWyszukiwania=Pomiar.szukajPowyzejProgu(prog);
    if(wynikiWyszukiwania.empty())
    {
        cout<<"Brak pomiarow spelniajacych kryterium"<<endl;
    }
    else
    {
        for(int i=0; i<wynikiWyszukiwania.size(); i++)
        {
            cout<<"ID: "<<wynikiWyszukiwania[i].id<<" "
                 <<"Data: "<<wynikiWyszukiwania[i].data<<" "
                 <<"Temperatura: "<<wynikiWyszukiwania[i].temperatura<<" "
                 <<"Wiatr: "<<wynikiWyszukiwania[i].wiatr<<endl;
        }
    }
    return 0;
}
//napisz klase pomiary do obslugi stacji pogodowej z metodami
//1. wcztaj z pliku(wczytuje do structury) id:string, data, temperatura pomiaru, wiatr, moga byc to liczby double
//2.znalezienie rekordu temperatury minimalnej (kolejny rekord)
//3.przeszukiwanie bazy pod katem pomiarow wiekszych niz zadany prog temperatury, pomiary nalezy przechowywac w vectorze lub w kolejce
