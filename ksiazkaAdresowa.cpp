#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <cstdlib>

using namespace std;

struct Uzytkownik {
    int idUzytkownika;
    string nazwa, haslo;
};

struct Osoba {
    int id, idUzytkownika;
    string imie, nazwisko, nrTelefonu, email, adres;
};

bool sortowanieKsiazki (Osoba lhs, Osoba rhs) {
    return lhs.id < rhs.id;
}

string wyciagnijStringa(string uzytkownik ) {
    string tmp="";
    int dlugoscLinii = uzytkownik.length();
    for(int i = 0; i<dlugoscLinii; i++) {
        if(uzytkownik[i]!='|') {
            tmp += uzytkownik[i];
        } else if(uzytkownik[i]=='|') {
            uzytkownik.erase(0,i+1);
            return tmp;
        }
    }
    return 0;
}

string potnijUzytkownika(string uzytkownik) {
    int dlugoscLinii = uzytkownik.length();
    for(int i = 0; i<dlugoscLinii; i++) {
        if(uzytkownik[i]=='|') {
            uzytkownik.erase(0,i+1);
            return uzytkownik;
        }
    }
    return 0;
}

void dodajUzytkonikaDoPliku(vector<Uzytkownik> &uzytkownicy) {
    int iloscUzytkownikow = uzytkownicy.size();
    ofstream plik;
    plik.open("Uzytkownicy.txt");

    if(!plik)
        cout << "Nie udalo sie otworzyc pliku Uzytkownicy";

    for(int i=0; i<iloscUzytkownikow; i++) {
        plik<<uzytkownicy[i].idUzytkownika<< "|" << uzytkownicy[i].nazwa <<
            "|" << uzytkownicy[i].haslo << "|" << endl;
    }
    plik.close();
}

int wczytajUzytkownikow (vector<Uzytkownik> &uzytkownicy) {

    ifstream plik;
    plik.open("Uzytkownicy.txt");
    string uzytkownik;

    if(!plik)
        cout << "Nie udalo sie otworzyc pliku Uzytkownicy";

    int iloscUzytkownikow = 0;
    int i = 0;
    while(getline(plik>>ws,uzytkownik)) {

        uzytkownicy.push_back(Uzytkownik());
        uzytkownicy[i].idUzytkownika = atoi(wyciagnijStringa(uzytkownik).c_str());
        uzytkownik = potnijUzytkownika(uzytkownik);
        uzytkownicy[i].nazwa = wyciagnijStringa(uzytkownik);
        uzytkownik = potnijUzytkownika(uzytkownik);
        uzytkownicy[i].haslo = wyciagnijStringa(uzytkownik);
        uzytkownik = potnijUzytkownika(uzytkownik);
        i++;
        iloscUzytkownikow++;
    }
    plik.close();
    return iloscUzytkownikow;
}

int rejestracja(vector<Uzytkownik> &uzytkownicy, int iloscUzytkownikow) {
    string nazwa, haslo;
    cout<<"Podaj nazwe uzytkownika: ";
    getline(cin >> ws, nazwa);
    int i = 0;
    while(i<iloscUzytkownikow) {
        if(uzytkownicy[i].nazwa == nazwa) {
            cout<<"Taki uzytkownik juz istnieje. Wpisz inna nazwe uzytkownika: ";
            cin>>nazwa;
            i=0;
        } else {
            i++;
        }
    }
    cout<<"Podaj haslo: ";
    getline(cin >> ws, haslo);
    uzytkownicy.push_back(Uzytkownik());
    uzytkownicy[iloscUzytkownikow].nazwa = nazwa;
    uzytkownicy[iloscUzytkownikow].haslo = haslo;
    uzytkownicy[iloscUzytkownikow].idUzytkownika = iloscUzytkownikow + 1;
    dodajUzytkonikaDoPliku(uzytkownicy);
    cout<<"Konto zalozone."<<endl;
    Sleep(1000);
    return iloscUzytkownikow + 1;
}

int logowanie(vector<Uzytkownik> &uzytkownicy, int iloscUzytkownikow) {
    string nazwa, haslo;
    cout<<"Podaj login: ";
    getline(cin >> ws, nazwa);
    int i = 0;
    while(i<iloscUzytkownikow) {
        if(uzytkownicy[i].nazwa == nazwa) {
            for(int proba=0; proba<3; proba++) {
                cout<<"Podaj haslo. Pozostalo prob "<<3 - proba <<": ";
                getline(cin >> ws,haslo);
                if(uzytkownicy[i].haslo == haslo) {
                    cout<<"Zalogowales sie."<<endl;
                    Sleep(1000);
                    return uzytkownicy[i].idUzytkownika;
                }
            }
            cout<<"Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba."<<endl;
            Sleep(3000);
            return 0;
        }
        i++;
    }
    cout<<"Nie ma uzytkownika z takim loginem."<<endl;
    Sleep(2000);
    return 0;
}

void zmianaHasla(vector<Uzytkownik> &uzytkownicy, int iloscUzytkownikow, int idZalogowanegoUzytkownika) {
    string haslo;
    cout<<"Podaj nowe haslo: ";
    cin>>haslo;

    for(int i=0; i<iloscUzytkownikow; i++) {
        if(uzytkownicy[i].idUzytkownika == idZalogowanegoUzytkownika) {
            uzytkownicy[i].haslo=haslo;
            cout<<"Haslo zostalo zmienione."<<endl;
            Sleep(2000);
        }
    }
}

void wyswietl (vector <Osoba> &ksiazkaAdresowa, int i) {
    cout << "ID: " << ksiazkaAdresowa[i].id << endl;
    cout << "imie: " << ksiazkaAdresowa[i].imie << endl;
    cout << "nazwisko: " << ksiazkaAdresowa[i].nazwisko << endl;
    cout << "tel.: " << ksiazkaAdresowa[i].nrTelefonu << endl;
    cout << "e-mail: " << ksiazkaAdresowa[i].email << endl;
    cout << "adres: " << ksiazkaAdresowa[i].adres << endl;
    cout << endl;
}

void wczytajJednaOsobeZKsiazkiAdresowej (vector <Osoba> &ksiazkaAdresowa, int numerLinii) {

    fstream plik;
    plik.open("ksiazka_adresowa.txt", ios::in);
    string uzytkownik;

    if(!plik)
        cout << "Nie udalo sie otworzyc pliku";

    for(int i=0; i<numerLinii-1; i++) {
        getline(plik,uzytkownik);
    }
    getline(plik, uzytkownik);

    ksiazkaAdresowa.push_back(Osoba());

    ksiazkaAdresowa[0].id = atoi(wyciagnijStringa(uzytkownik).c_str());
    uzytkownik = potnijUzytkownika(uzytkownik);

    ksiazkaAdresowa[0].idUzytkownika = atoi(wyciagnijStringa(uzytkownik).c_str());
    uzytkownik = potnijUzytkownika(uzytkownik);

    ksiazkaAdresowa[0].imie = wyciagnijStringa(uzytkownik);
    uzytkownik = potnijUzytkownika(uzytkownik);

    ksiazkaAdresowa[0].nazwisko = wyciagnijStringa(uzytkownik);
    uzytkownik = potnijUzytkownika(uzytkownik);

    ksiazkaAdresowa[0].nrTelefonu = wyciagnijStringa(uzytkownik);
    uzytkownik = potnijUzytkownika(uzytkownik);

    ksiazkaAdresowa[0].email = wyciagnijStringa(uzytkownik);
    uzytkownik = potnijUzytkownika(uzytkownik);

    ksiazkaAdresowa[0].adres = wyciagnijStringa(uzytkownik);

   plik.close();
}

int nadajID (vector <Osoba> &ksiazkaAdresowa) {

    int ID = 1;
    int index = ksiazkaAdresowa.size();

    if(ksiazkaAdresowa.empty())
        return 1;
    else if(ksiazkaAdresowa[index-1].id == index) {

        return ksiazkaAdresowa[index-1].id + 1;
    } else
        for (int i = 0; i<index; i++) {
            if (ksiazkaAdresowa[i].id > ID) {

                return ID;
            } else
                ID++;
        }
    return 0;
}
void dodajOsobeDoPlikuGlownego(vector <Osoba> &ksiazkaAdresowa) {
    fstream plik;
    plik.open("ksiazka_adresowa.txt", ios::out);
    int ileWszystkichOsobWKsiazce = ksiazkaAdresowa.size();

    if(!plik)
        cout << "Nie udalo sie otworzyc pliku";



    for (int i=0; i<ileWszystkichOsobWKsiazce; i++) {
        plik<<ksiazkaAdresowa[i].id<< "|" << ksiazkaAdresowa[i].idUzytkownika<< "|"<< ksiazkaAdresowa[i].imie <<
            "|" << ksiazkaAdresowa[i].nazwisko << "|" << ksiazkaAdresowa[i].nrTelefonu <<
            "|" << ksiazkaAdresowa[i].email << "|" << ksiazkaAdresowa[i].adres << "|" << endl;
    }
    plik.close();

}

void nadpiszPlikTekstowy(vector <Osoba> &tymczasowaKsiazkaAdresowa, int idOsoby) {
    int iloscOsob = tymczasowaKsiazkaAdresowa.size();
    int numerLinii = 1;
    int index;
    vector <Osoba> pelnaKsiazkaAdresowa;
    ifstream plikOryginalny;
    fstream plikTymczasowy;
    plikOryginalny.open("ksiazka_adresowa.txt");
    plikTymczasowy.open("tymczasowa_ksiazka_adresowa.txt", ios::out);

    if(!plikOryginalny && !plikTymczasowy)
        cout << "Nie udalo sie otworzyc pliku";

     for(int i=0; i<iloscOsob; i++)
        if (tymczasowaKsiazkaAdresowa[i].id == idOsoby)
            index = i;

    string tmp;
    while(getline(plikOryginalny, tmp)){

        wczytajJednaOsobeZKsiazkiAdresowej(pelnaKsiazkaAdresowa, numerLinii);

        if(pelnaKsiazkaAdresowa[0].id == idOsoby) {
            plikTymczasowy<<tymczasowaKsiazkaAdresowa[index].id<< "|" << tymczasowaKsiazkaAdresowa[index].idUzytkownika<< "|"<< tymczasowaKsiazkaAdresowa[index].imie <<
            "|" << tymczasowaKsiazkaAdresowa[index].nazwisko << "|" << tymczasowaKsiazkaAdresowa[index].nrTelefonu <<
            "|" << tymczasowaKsiazkaAdresowa[index].email << "|" << tymczasowaKsiazkaAdresowa[index].adres << "|" << endl;

        } else {
            plikTymczasowy<<pelnaKsiazkaAdresowa[0].id<< "|" << pelnaKsiazkaAdresowa[0].idUzytkownika<< "|"<< pelnaKsiazkaAdresowa[0].imie <<
            "|" << pelnaKsiazkaAdresowa[0].nazwisko << "|" << pelnaKsiazkaAdresowa[0].nrTelefonu <<
            "|" << pelnaKsiazkaAdresowa[0].email << "|" << pelnaKsiazkaAdresowa[0].adres << "|" << endl;

        }
        pelnaKsiazkaAdresowa.erase(pelnaKsiazkaAdresowa.begin(), pelnaKsiazkaAdresowa.end());
        numerLinii++;
    }
    plikTymczasowy.close();
    plikOryginalny.close();
    remove("ksiazka_adresowa.txt");
    rename("tymczasowa_ksiazka_adresowa.txt", "ksiazka_adresowa.txt");

}

void dodajOsobe (int idZalogowanegoUzytkownika) {
    string imie, nazwisko, email, adres;
    string nrTelefonu;
    vector <Osoba> ksiazkaAdresowa;
    //wczytajWszystkieOsobyZKsiazkiAdresowej(ksiazkaAdresowa);
    int iloscOsob = ksiazkaAdresowa.size();

    int id = nadajID (ksiazkaAdresowa);
    system("pause");
    ksiazkaAdresowa.push_back(Osoba());

    cout<<"Podaj imie: ";
    getline(cin>>ws, imie);
    cout<<"Podaj nazwisko: ";
    cin.sync();
    getline(cin, nazwisko);
    cout<<"Podaj numer telefonu: ";
    cin.sync();
    getline(cin, nrTelefonu);
    cout<<"Podaj adres e-mail: ";
    cin.sync();
    getline(cin, email);
    cout<<"Podaj adres zamieszkania: ";
    cin.sync();
    getline(cin, adres);

    ksiazkaAdresowa[iloscOsob].id = id;
    ksiazkaAdresowa[iloscOsob].idUzytkownika = idZalogowanegoUzytkownika;
    ksiazkaAdresowa[iloscOsob].imie = imie;
    ksiazkaAdresowa[iloscOsob].nazwisko = nazwisko;
    ksiazkaAdresowa[iloscOsob].nrTelefonu = nrTelefonu;
    ksiazkaAdresowa[iloscOsob].email = email;
    ksiazkaAdresowa[iloscOsob].adres = adres;

    sort(ksiazkaAdresowa.begin(), ksiazkaAdresowa.end(), sortowanieKsiazki);

    dodajOsobeDoPlikuGlownego(ksiazkaAdresowa);
    ksiazkaAdresowa.erase(ksiazkaAdresowa.begin(), ksiazkaAdresowa.end());
    cout<<endl<<"Osoba zostala dodana."<<endl;
    Sleep(1500);


}

void wyszukajOsobePoImieniu (vector <Osoba> &ksiazkaAdresowa) {
    string imie;
    string wypisz;
    int ileOsob = ksiazkaAdresowa.size();

    cout<<"Podaj imie: ";
    cin>>imie;
    cout<<endl;

    for(int i=0; i<ileOsob; i++) {
        if(ksiazkaAdresowa[i].imie==imie) {
            wyswietl(ksiazkaAdresowa, i);
        }
    }
    system("pause");
}

void wyszukajOsobePoNazwisku (vector <Osoba> &ksiazkaAdresowa) {
    int ileOsob = ksiazkaAdresowa.size();
    string nazwisko;
    cout<<"Podaj nazwisko: ";
    cin>>nazwisko;
    cout<<endl;
    for(int i=0; i<ileOsob; i++) {
        if(ksiazkaAdresowa[i].nazwisko==nazwisko) {
            wyswietl(ksiazkaAdresowa, i);
        }
    }
    system("pause");
}

void wyswietlWszystkich (vector <Osoba> &ksiazkaAdresowa) {
    int ileOsob = ksiazkaAdresowa.size();
    if(ksiazkaAdresowa.size() == 0) {
        cout<<"Twoja lista jest pusta.";
        Sleep(2000);
    } else {
        for(int i=0; i<ileOsob; i++) {
            wyswietl(ksiazkaAdresowa, i);
        }
        system("pause");
    }
}

void wczytajOsobyZKsiazkiAdresowej (vector <Osoba> &ksiazkaAdresowa, int idZalogowanegoUzytkownika) {

    ifstream plik("ksiazka_adresowa.txt");
    string uzytkownik;

    int tempIdZalogowanegoUzytkownika;

    int i = 0;
    while(getline(plik,uzytkownik)) {
        string tempUzytkownik = uzytkownik;
        tempUzytkownik = potnijUzytkownika(tempUzytkownik);
        tempIdZalogowanegoUzytkownika = atoi(wyciagnijStringa(tempUzytkownik).c_str());

        if(tempIdZalogowanegoUzytkownika == idZalogowanegoUzytkownika) {

            ksiazkaAdresowa.push_back(Osoba());

            ksiazkaAdresowa[i].id = atoi(wyciagnijStringa(uzytkownik).c_str());
            uzytkownik = potnijUzytkownika(uzytkownik);

            ksiazkaAdresowa[i].idUzytkownika = atoi(wyciagnijStringa(uzytkownik).c_str());
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
    }
    plik.close();
}

void zmienImie (vector <Osoba> &ksiazkaAdresowa, int idOsoby) {
    string noweImie;
    vector <Osoba>::iterator it;

    cout << "Podaj nowe imie: ";
    getline(cin >> ws, noweImie);

    for(it = ksiazkaAdresowa.begin(); it!=ksiazkaAdresowa.end(); ++it) {
        if((*it).id == idOsoby) {
            (*it).imie = noweImie;
            nadpiszPlikTekstowy(ksiazkaAdresowa, idOsoby);
            cout << "Imie zostalo zmienione." << endl;
            Sleep(1500);
        }
    }
}

void zmienNazwisko (vector <Osoba> &ksiazkaAdresowa, int idOsoby) {
    string noweNazwisko;
    vector <Osoba>::iterator it;

    cout << "Podaj nowe nazwisko: ";
    getline(cin >> ws, noweNazwisko);

    for(it = ksiazkaAdresowa.begin(); it!=ksiazkaAdresowa.end(); ++it) {
        if((*it).id == idOsoby) {
            (*it).nazwisko = noweNazwisko;
            nadpiszPlikTekstowy(ksiazkaAdresowa, idOsoby);
            cout << "Nazwisko zostalo zmienione." << endl;
            Sleep(1500);
        }
    }
}

void zmienNrTelefonu (vector <Osoba> &ksiazkaAdresowa, int idOsoby) {
    string nowyNrTelefonu;
    vector <Osoba>::iterator it;

    cout << "Podaj nowy numer telefonu: ";
    getline(cin >> ws, nowyNrTelefonu);

    for(it = ksiazkaAdresowa.begin(); it!=ksiazkaAdresowa.end(); ++it) {
        if((*it).id == idOsoby) {
            (*it).nrTelefonu = nowyNrTelefonu;
            nadpiszPlikTekstowy(ksiazkaAdresowa, idOsoby);
            cout << "Numer telefonu zostal zmieniony." << endl;
            Sleep(1500);
        }
    }
}

void zmienEmail (vector <Osoba> &ksiazkaAdresowa, int idOsoby) {
    string nowyEmail;
    vector <Osoba>::iterator it;

    cout << "Podaj nowy adres email: ";
    getline(cin >> ws, nowyEmail);

    for(it = ksiazkaAdresowa.begin(); it!=ksiazkaAdresowa.end(); ++it) {
        if((*it).id == idOsoby) {
            (*it).email = nowyEmail;
            nadpiszPlikTekstowy(ksiazkaAdresowa, idOsoby);
            cout << "Adres email zostal zmieniony." << endl;
            Sleep(1500);
        }
    }
}

void zmienAdres (vector <Osoba> &ksiazkaAdresowa, int idOsoby) {
    string nowyAdres;
    vector <Osoba>::iterator it;

    cout << "Podaj nowy adres: ";
    getline(cin >> ws, nowyAdres);

    for(it = ksiazkaAdresowa.begin(); it!=ksiazkaAdresowa.end(); ++it) {
        if((*it).id == idOsoby) {
            (*it).adres = nowyAdres;
            nadpiszPlikTekstowy(ksiazkaAdresowa, idOsoby);
            cout << "Adres zostal zmieniony." << endl;
            Sleep(1500);
        }
    }
}

int usunOsobeZKsiazkiAdresowej (vector <Osoba> &ksiazkaAdresowa, int idOsoby) {

    vector <Osoba>::iterator it;
    int iloscOsob = ksiazkaAdresowa.size();
    char potwierdzenie;

    for(it = ksiazkaAdresowa.begin(); it!=ksiazkaAdresowa.end(); ++it) {
        if((*it).id == idOsoby) {
            cout << "Napewno usunac osobe z ksiazki adresowej? [t]";
            cin >> potwierdzenie;
            if (potwierdzenie == 't') {

                ksiazkaAdresowa.erase (it);

                cout << "Osoba zostala usunieta.";
                system("pause");
                nadpiszPlikTekstowy(ksiazkaAdresowa, idOsoby);
                return iloscOsob - 1;
            } else
                return 0;
        }
    }
    return 0;
}

int main() {
    vector<Osoba> ksiazkaAdresowa;
    vector<Uzytkownik>uzytkownicy;

    // int iloscOsob = 0;
    int idOsoby = 0;
    int idZalogowanegoUzytkownika = 0;
    int iloscUzytkownikow = 0;
    char wybor;

    iloscUzytkownikow = wczytajUzytkownikow(uzytkownicy);
    //wczytajOsobyZKsiazkiAdresowej ( ksiazkaAdresowa);

    while(true) {
        if(idZalogowanegoUzytkownika == 0) {
            system("cls");
            cout<<"1. Rejestracja"<<endl;
            cout<<"2. Logowanie"<<endl;
            cout<<"9. Zamknij program"<<endl;
            cin>>wybor;

            if(wybor=='1') {
                iloscUzytkownikow = rejestracja(uzytkownicy, iloscUzytkownikow);
            } else if(wybor=='2') {
                idZalogowanegoUzytkownika = logowanie(uzytkownicy, iloscUzytkownikow);
                wczytajOsobyZKsiazkiAdresowej ( ksiazkaAdresowa, idZalogowanegoUzytkownika);
            } else if(wybor=='9') {
                exit(0);
            }
        } else {

            system("cls");

            cout << "1. Dodaj adresata" << endl;
            cout << "2. Wyszukaj po imieniu" << endl;
            cout << "3. Wyszukaj po nazwisku" << endl;
            cout << "4. Wyswietl wszystkich adresatow" << endl;
            cout << "5. Usun adresata" << endl;
            cout << "6. Edytuj adresata" << endl;
            cout << "7. Zmien haslo" << endl;
            cout << "9. Wyloguj sie" << endl;
            cin >> wybor;




            switch (wybor) {
            case '1':
                dodajOsobe (idZalogowanegoUzytkownika);
                ksiazkaAdresowa.erase(ksiazkaAdresowa.begin(), ksiazkaAdresowa.end());
                wczytajOsobyZKsiazkiAdresowej ( ksiazkaAdresowa, idZalogowanegoUzytkownika);
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

                if (idOsoby > 0) {

                    system("cls");
                    cout << "1 - imie" << endl;
                    cout << "2 - nazwisko" << endl;
                    cout << "3 - numer telefonu" << endl;
                    cout << "4 - email" << endl;
                    cout << "5 - adres" << endl;
                    cout << "6 - powrot do menu" << endl;
                    cin >> wybor;

                    switch (wybor) {
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
            case '7':
                zmianaHasla(uzytkownicy, iloscUzytkownikow, idZalogowanegoUzytkownika);
                break;

            case '9':
                idZalogowanegoUzytkownika = 0;
                ksiazkaAdresowa.erase(ksiazkaAdresowa.begin(), ksiazkaAdresowa.end());
                break;
            }
        }
    }

    return 0;
}










