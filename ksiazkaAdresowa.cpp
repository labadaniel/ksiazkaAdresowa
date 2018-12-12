#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <cstdlib>

using namespace std;


struct Osoba
{
    int id;
    string imie, nazwisko, nrTelefonu, email, adres;
};

bool sortowanieKsiazki (Osoba lhs, Osoba rhs){
    return lhs.id < rhs.id;
}

void wyswietl (vector <Osoba> &ksiazkaAdresowa, int i)
{
    cout << "ID: " << ksiazkaAdresowa[i].id << endl;
    cout << "imie: " << ksiazkaAdresowa[i].imie << endl;
    cout << "nazwisko: " << ksiazkaAdresowa[i].nazwisko << endl;
    cout << "tel.: " << ksiazkaAdresowa[i].nrTelefonu << endl;
    cout << "e-mail: " << ksiazkaAdresowa[i].email << endl;
    cout << "adres: " << ksiazkaAdresowa[i].adres << endl;
    cout << endl;
}

int nadajID (vector <Osoba> &ksiazkaAdresowa){
    int ID = 1;

    if(ksiazkaAdresowa.empty())
        return 1;
    else if(ksiazkaAdresowa[ksiazkaAdresowa.size()-1].id == ksiazkaAdresowa.size())
        return ksiazkaAdresowa[ksiazkaAdresowa.size()-1].id + 1;
    else
        for (int i = 0; i<ksiazkaAdresowa.size(); i++){
            if (ksiazkaAdresowa[i].id > ID)

                return ID;
            else
                ID++;
        }
}


void nadpiszPlikTekstowy(vector <Osoba> &ksiazkaAdresowa){
    int iloscOsob = ksiazkaAdresowa.size();
    fstream plik;
    plik.open("ksiazka_adresowa.txt", ios::out);

    if(!plik)
        cout << "Nie udalo sie otworzyc pliku";

    for(int i=0; i<iloscOsob; i++){
        plik<<ksiazkaAdresowa[i].id<< "|" << ksiazkaAdresowa[i].imie <<
         "|" << ksiazkaAdresowa[i].nazwisko << "|" << ksiazkaAdresowa[i].nrTelefonu <<
         "|" << ksiazkaAdresowa[i].email << "|" << ksiazkaAdresowa[i].adres << "|" << endl;
    }
    plik.close();
}

int dodajOsobe (vector <Osoba> &ksiazkaAdresowa){
    string imie, nazwisko, email, adres;
    string nrTelefonu;
    int iloscOsob = ksiazkaAdresowa.size();

    int id = nadajID (ksiazkaAdresowa);
    ksiazkaAdresowa.push_back(Osoba());

    cout<<"Podaj imie: "; cin.ignore(); getline(cin, imie);
    cout<<"Podaj nazwisko: "; cin.sync(); getline(cin, nazwisko);
    cout<<"Podaj numer telefonu: "; cin.sync(); getline(cin, nrTelefonu);
    cout<<"Podaj adres e-mail: "; cin.sync(); getline(cin, email);
    cout<<"Podaj adres zamieszkania: "; cin.sync(); getline(cin, adres);

    ksiazkaAdresowa[iloscOsob].id = id;
    ksiazkaAdresowa[iloscOsob].imie = imie;
    ksiazkaAdresowa[iloscOsob].nazwisko = nazwisko;
    ksiazkaAdresowa[iloscOsob].nrTelefonu = nrTelefonu;
    ksiazkaAdresowa[iloscOsob].email = email;
    ksiazkaAdresowa[iloscOsob].adres = adres;

    sort(ksiazkaAdresowa.begin(), ksiazkaAdresowa.end(), sortowanieKsiazki);
    nadpiszPlikTekstowy(ksiazkaAdresowa);
    //dodajDoPlikuTekstowego(ksiazkaAdresowa);
    cout<<endl<<"Osoba zostala dodana."<<endl;
    Sleep(1500);

    return iloscOsob + 1;
}

void wyszukajOsobePoImieniu (vector <Osoba> &ksiazkaAdresowa)
{
    string imie;
    string wypisz;

    cout<<"Podaj imie: ";
    cin>>imie;
    cout<<endl;

    for(int i=0; i<ksiazkaAdresowa.size(); i++)
    {
        if(ksiazkaAdresowa[i].imie==imie)
        {
            wyswietl(ksiazkaAdresowa, i);
        }
    }system("pause");
}

void wyszukajOsobePoNazwisku (vector <Osoba> &ksiazkaAdresowa)
{
    string nazwisko;
    cout<<"Podaj nazwisko: ";
    cin>>nazwisko;
    cout<<endl;
    for(int i=0; i<ksiazkaAdresowa.size(); i++)
    {
        if(ksiazkaAdresowa[i].nazwisko==nazwisko)
        {
            wyswietl(ksiazkaAdresowa, i);
        }
    }
    system("pause");
}

void wyswietlWszystkich (vector <Osoba> &ksiazkaAdresowa)
{

    if(ksiazkaAdresowa.size() == 0){
        cout<<"Twoja lista jest pusta.";
        Sleep(2000);
    }else{
        for(int i=0; i<ksiazkaAdresowa.size(); i++){
            wyswietl(ksiazkaAdresowa, i);
        }
        system("pause");
    }
}

string wyciagnijStringa(string uzytkownik ){
    string tmp="";
    for(int i = 0; i<uzytkownik.length(); i++){
        if(uzytkownik[i]!='|'){
            tmp += uzytkownik[i];
        }else if(uzytkownik[i]=='|'){
            uzytkownik.erase(0,i+1);
            return tmp;
        }
    }
}

string potnijUzytkownika(string uzytkownik){
    for(int i = 0; i<uzytkownik.length(); i++){
        if(uzytkownik[i]=='|'){
            uzytkownik.erase(0,i+1);
            return uzytkownik;
        }
    }
}

int wczytajOsobyZKsiazkiAdresowej (vector <Osoba> &ksiazkaAdresowa){

    ifstream plik("ksiazka_adresowa.txt");
    string uzytkownik;

    int iloscOsob = 0;
    int i = 0;
    while(getline(plik>>ws,uzytkownik)){

        ksiazkaAdresowa.push_back(Osoba());

        ksiazkaAdresowa[i].id = atoi(wyciagnijStringa(uzytkownik).c_str());
        uzytkownik = potnijUzytkownika(uzytkownik);

        ksiazkaAdresowa[i].imie = wyciagnijStringa(uzytkownik);
        uzytkownik = potnijUzytkownika(uzytkownik);

        ksiazkaAdresowa[i].nazwisko = wyciagnijStringa(uzytkownik);
        uzytkownik = potnijUzytkownika(uzytkownik);

        ksiazkaAdresowa[i].nrTelefonu = wyciagnijStringa(uzytkownik);
        uzytkownik = potnijUzytkownika(uzytkownik);

        ksiazkaAdresowa[i].email = wyciagnijStringa(uzytkownik);
        uzytkownik = potnijUzytkownika(uzytkownik);

        ksiazkaAdresowa[i].adres = wyciagnijStringa(uzytkownik);
        i++;
    }
    plik.close();
    return iloscOsob;
}

void zmienImie (vector <Osoba> &ksiazkaAdresowa, int idOsoby){
    string noweImie;
    vector <Osoba>::iterator it;

    cout << "Podaj nowe imie: ";
    getline(cin >> ws, noweImie);

    for(it = ksiazkaAdresowa.begin(); it!=ksiazkaAdresowa.end(); ++it){
        if((*it).id == idOsoby){
            (*it).imie = noweImie;
            nadpiszPlikTekstowy(ksiazkaAdresowa);
            cout << "Imie zostalo zmienione." << endl;
            Sleep(1500);
        }
    }
}

void zmienNazwisko (vector <Osoba> &ksiazkaAdresowa, int idOsoby){
    string noweNazwisko;
    vector <Osoba>::iterator it;

    cout << "Podaj nowe nazwisko: ";
    getline(cin >> ws, noweNazwisko);

    for(it = ksiazkaAdresowa.begin(); it!=ksiazkaAdresowa.end(); ++it){
        if((*it).id == idOsoby){
            (*it).nazwisko = noweNazwisko;
            nadpiszPlikTekstowy(ksiazkaAdresowa);
            cout << "Nazwisko zostalo zmienione." << endl;
            Sleep(1500);
        }
    }
}

void zmienNrTelefonu (vector <Osoba> &ksiazkaAdresowa, int idOsoby){
    string nowyNrTelefonu;
    vector <Osoba>::iterator it;

    cout << "Podaj nowy numer telefonu: ";
    getline(cin >> ws, nowyNrTelefonu);

    for(it = ksiazkaAdresowa.begin(); it!=ksiazkaAdresowa.end(); ++it){
        if((*it).id == idOsoby){
            (*it).nrTelefonu = nowyNrTelefonu;
            nadpiszPlikTekstowy(ksiazkaAdresowa);
            cout << "Numer telefonu zostal zmieniony." << endl;
            Sleep(1500);
        }
    }
}

void zmienEmail (vector <Osoba> &ksiazkaAdresowa, int idOsoby){
    string nowyEmail;
    vector <Osoba>::iterator it;

    cout << "Podaj nowy adres email: ";
    getline(cin >> ws, nowyEmail);

    for(it = ksiazkaAdresowa.begin(); it!=ksiazkaAdresowa.end(); ++it){
        if((*it).id == idOsoby){
            (*it).email = nowyEmail;
            nadpiszPlikTekstowy(ksiazkaAdresowa);
            cout << "Adres email zostal zmieniony." << endl;
            Sleep(1500);
        }
    }
}

void zmienAdres (vector <Osoba> &ksiazkaAdresowa, int idOsoby){
    string nowyAdres;
    vector <Osoba>::iterator it;

    cout << "Podaj nowy adres: ";
    getline(cin >> ws, nowyAdres);

    for(it = ksiazkaAdresowa.begin(); it!=ksiazkaAdresowa.end(); ++it){
        if((*it).id == idOsoby){
            (*it).adres = nowyAdres;
            nadpiszPlikTekstowy(ksiazkaAdresowa);
            cout << "Adres zostal zmieniony." << endl;
            Sleep(1500);
        }
    }
}

int usunOsobeZKsiazkiAdresowej (vector <Osoba> &ksiazkaAdresowa, int idOsoby){

    vector <Osoba>::iterator it;
    int iloscOsob = ksiazkaAdresowa.size();
    char potwierdzenie;

    for(it = ksiazkaAdresowa.begin(); it!=ksiazkaAdresowa.end(); ++it){
        if((*it).id == idOsoby){
                cout << "Napewno usunac osobe z ksiazki adresowej? [t]";
                cin >> potwierdzenie;
                if (potwierdzenie == 't'){

                    ksiazkaAdresowa.erase (it);

                    cout << "Osoba zostala usunieta.";
                    system("pause");
                    nadpiszPlikTekstowy(ksiazkaAdresowa);
                    return iloscOsob - 1;
                }else
                    return 0;
        }
    }
}

int main()
{
    vector<Osoba> ksiazkaAdresowa;
    int iloscOsob = 0;
    int idOsoby = 0;
    char wybor;

    iloscOsob = wczytajOsobyZKsiazkiAdresowej ( ksiazkaAdresowa );

    while(true)
    {
        system("cls");
        cout << "1. Dodaj osobe" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkie osoby" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zakoncz program" << endl;
        cin >> wybor;

        switch (wybor)
        {
            case '1':
                iloscOsob = dodajOsobe (ksiazkaAdresowa);
                break;
            case '2':
                wyszukajOsobePoImieniu (ksiazkaAdresowa);
                break;
            case '3':
                wyszukajOsobePoNazwisku (ksiazkaAdresowa);
                break;
            case '4':
                wyswietlWszystkich (ksiazkaAdresowa);
                break;
            case '5':
                cout << "Podaj ID osoby: ";
                cin >> idOsoby;
                usunOsobeZKsiazkiAdresowej (ksiazkaAdresowa, idOsoby);
                break;
            case '6':
                cout << "Podaj ID osoby: ";
                cin >> idOsoby;

                if (idOsoby > 0){

                    system("cls");
                    cout << "1 - imie" << endl;
                    cout << "2 - nazwisko" << endl;
                    cout << "3 - numer telefonu" << endl;
                    cout << "4 - email" << endl;
                    cout << "5 - adres" << endl;
                    cout << "6 - powrot do menu" << endl;
                    cin >> wybor;

                    switch (wybor){
                        case '1':
                            zmienImie (ksiazkaAdresowa, idOsoby);
                            break;
                        case '2':
                            zmienNazwisko (ksiazkaAdresowa, idOsoby);
                            break;
                        case '3':
                            zmienNrTelefonu (ksiazkaAdresowa, idOsoby);
                            break;
                        case '4':
                            zmienEmail (ksiazkaAdresowa, idOsoby);
                            break;
                        case '5':
                            zmienAdres (ksiazkaAdresowa, idOsoby);
                            break;
                        case '6':
                            ;
                            break;
                    }
                }
                break;
            case '9':
                exit (0);
                break;
        }
    }
    return 0;
}





