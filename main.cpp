#include <iostream>
#include <sstream>
#include <string>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

string nazwaPliku = "Adresaci.txt";
string nazwaPliku2 = "Uzytkownicy.txt";
string nazwaPliku3 = "AdresaciTymczasowi.txt";

string konwersjaIntNaString (int liczba)
{
    ostringstream ss;
    ss << liczba;
    string str = ss.str();
    return str;
}

string wczytajLinie()
{
    string wejscie = "";
    cin.sync();
    getline(cin, wejscie);
    return wejscie;
}

char wczytajZnak()
{
    string wejscie = "";
    char znak = {0};

    while(true)
    {
        cin.sync();
        getline(cin, wejscie);

        if (wejscie.length() == 1)
        {
            znak = wejscie[0];
            break;
        }
        cout << "To nie jest pojedynczy znak. Wpisz ponownie." << endl;
    }
    return znak;
}

int wczytajLiczbeCalkowita()
{
    string wejscie = "";
    int liczba = 0;

    while (true)
    {
        getline(cin, wejscie);

        stringstream myStream(wejscie);
        if (myStream >> liczba)
        {
            break;
        }
        cout << "To nie jest liczba. Wpisz ponownie. " << endl;
    }
    return liczba;
}

struct Adresat
{
    int idAdresata = 0, idUzytkownika = 0;
    string imie = "", nazwisko = "", numerTelefonu = "", email = "", adres = "";
};

struct Uzytkownik
{
    int idUzytkownika = 0, haslo = 0;
    string login = "";
};

vector <string> dzielenieCiaguZnakowNaPojedynczeDane (string ciagZnakowDotyczacyJednejOsoby)
{
    vector <string> danePoPodziale;
    int dlugoscCiaguZnakow = ciagZnakowDotyczacyJednejOsoby.length();

    while (dlugoscCiaguZnakow > 0)
    {
        for (int i = 0; i < dlugoscCiaguZnakow; i++)
        {
            if (ciagZnakowDotyczacyJednejOsoby[i] == '|')
            {
                string tekstKopiowany = ciagZnakowDotyczacyJednejOsoby.substr(0, i);
                ciagZnakowDotyczacyJednejOsoby.erase(0, i + 1);
                danePoPodziale.push_back(tekstKopiowany);
                dlugoscCiaguZnakow = ciagZnakowDotyczacyJednejOsoby.length();
                i = 0;
            }
        }
    }

    return danePoPodziale;
}

string laczeniePojedynczychDanychWCiagZnakow (Adresat daneOsoby)
{
    string liniaTekstu = "";
    string przerywnik = "|";

    liniaTekstu = konwersjaIntNaString(daneOsoby.idAdresata) + przerywnik + konwersjaIntNaString(daneOsoby.idUzytkownika) + przerywnik + daneOsoby.imie + przerywnik + daneOsoby.nazwisko + przerywnik + daneOsoby.numerTelefonu + przerywnik + daneOsoby.email + przerywnik + daneOsoby.adres + przerywnik;

    return liniaTekstu;
}

int wczytajAdresatowZPliku(vector <Adresat> &adresaci, int &idZalogowanegoUzytkownika)
{
    Adresat danePojedynczejOsoby;
    vector <string> daneDotyczaceJednejOsoby;
    string liniaTekstu;
    string linia;
    int numerLinii = 1, idOstatniegoUzytkownika = 0;

    adresaci.clear();

    fstream plik;
    plik.open(nazwaPliku.c_str(), ios::in);

    if(plik.good() == true)
    {
        while(getline(plik, linia))
        {
            switch(numerLinii)
            {
            case 1:
                liniaTekstu = linia;
                break;
            }
            daneDotyczaceJednejOsoby = dzielenieCiaguZnakowNaPojedynczeDane(liniaTekstu);

            danePojedynczejOsoby.idAdresata = stoi(daneDotyczaceJednejOsoby[0]);
            danePojedynczejOsoby.idUzytkownika = stoi(daneDotyczaceJednejOsoby[1]);

            if (danePojedynczejOsoby.idUzytkownika == idZalogowanegoUzytkownika)
            {
                danePojedynczejOsoby.imie = daneDotyczaceJednejOsoby[2];
                danePojedynczejOsoby.nazwisko = daneDotyczaceJednejOsoby[3];
                danePojedynczejOsoby.numerTelefonu = daneDotyczaceJednejOsoby[4];
                danePojedynczejOsoby.email = daneDotyczaceJednejOsoby[5];
                danePojedynczejOsoby.adres = daneDotyczaceJednejOsoby[6];

                adresaci.push_back(danePojedynczejOsoby);
            }

            idOstatniegoUzytkownika = danePojedynczejOsoby.idAdresata;
        }
        plik.close();
    }
    return idOstatniegoUzytkownika;
}

void wczytajUzytkownikowZPliku(vector <Uzytkownik> &uzytkownicy)
{
    Uzytkownik danePojedynczegoUzytkownika;
    vector <string> daneDotyczaceJednegoUzytkownia;
    string liniaTekstu;
    string linia;
    int numerLinii = 1;

    fstream plik;
    plik.open(nazwaPliku2.c_str(), ios::in);

    if(plik.good() == true)
    {
        while(getline(plik, linia))
        {
            switch(numerLinii)
            {
            case 1:
                liniaTekstu = linia;
                break;
            }
            daneDotyczaceJednegoUzytkownia = dzielenieCiaguZnakowNaPojedynczeDane(liniaTekstu);

            danePojedynczegoUzytkownika.idUzytkownika = stoi(daneDotyczaceJednegoUzytkownia[0]);
            danePojedynczegoUzytkownika.login = daneDotyczaceJednegoUzytkownia[1];
            danePojedynczegoUzytkownika.haslo = stoi(daneDotyczaceJednegoUzytkownia[2]);

            uzytkownicy.push_back(danePojedynczegoUzytkownika);
        }
        plik.close();
    }
}

void wyswietlWszystkichAdresatow(vector <Adresat> &adresaci)
{
    system("cls");
    cout << ">>> LISTA WSZYSKICH ADRESATOW <<<" << endl << endl;

    if (!adresaci.empty())
    {
        for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            cout << "Id:                 " << itr->idAdresata << endl;
            cout << "Imie:               " << itr->imie << endl;
            cout << "Nazwisko:           " << itr->nazwisko << endl;
            cout << "Numer telefonu:     " << itr->numerTelefonu << endl;
            cout << "Email:              " << itr->email << endl;
            cout << "Adres:              " << itr->adres << endl << endl;
        }
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta." << endl << endl;
    }

    system("pause");
}

void wyswietlWszystkichUzytkownikow(vector <Uzytkownik> &uzytkownicy)
{
    system("cls");
    cout << ">>> LISTA WSZYSKICH UZYTKOWNIKOW <<<" << endl << endl;

    if (!uzytkownicy.empty())
    {
        for (vector<Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
        {
            cout << "Id Uzytkownika:      " << itr->idUzytkownika << endl;
            cout << "Nazwa:               " << itr->login << endl <<endl;
            //cout << "Haslo:               " << itr->haslo << endl << endl;
        }
    }
    else
    {
        cout << "Brak zapisanych uzytkownikow." << endl << endl;
    }

    system("pause");
}

void zapiszAdresatowDoPliku(vector <Adresat> &adresaci, int &idZalogowanegoUzytkownika)
{
    Adresat danePojedynczejOsoby;
    vector <string> daneDotyczaceJednejOsoby;
    string liniaTekstu;
    int numerLinii = 1;

    fstream plikOryginalny, plikTymczasowy;

    plikOryginalny.open(nazwaPliku.c_str(), ios::in);
    plikTymczasowy.open(nazwaPliku3.c_str(), ios::out);

    vector<Adresat>::iterator  itr = adresaci.begin();

    if(plikOryginalny.good() == true)
    {
        while(getline(plikOryginalny, liniaTekstu))
        {
            switch(numerLinii)
            {
            case 1:
                break;
            }

            daneDotyczaceJednejOsoby = dzielenieCiaguZnakowNaPojedynczeDane(liniaTekstu);

            danePojedynczejOsoby.idAdresata = stoi(daneDotyczaceJednejOsoby[0]);
            danePojedynczejOsoby.idUzytkownika = stoi(daneDotyczaceJednejOsoby[1]);


            if (danePojedynczejOsoby.idUzytkownika != idZalogowanegoUzytkownika)
            {
                plikTymczasowy << liniaTekstu << endl;
            }

            else if (danePojedynczejOsoby.idUzytkownika == idZalogowanegoUzytkownika && !adresaci.empty())
            {
                while (itr != adresaci.end())
                {
                    if (danePojedynczejOsoby.idAdresata == itr->idAdresata)
                    {
                        liniaTekstu = laczeniePojedynczychDanychWCiagZnakow(*itr);
                        plikTymczasowy << liniaTekstu << endl;
                        itr++;
                        break;
                    }
                    else if (danePojedynczejOsoby.idAdresata != itr->idAdresata)
                    {
                        break;
                    }
                }
            }
        }

        plikOryginalny.close();
        plikTymczasowy.close();

        remove (nazwaPliku.c_str());
        rename (nazwaPliku3.c_str(), nazwaPliku.c_str());
    }
}

void dopiszAdresataDoPliku (Adresat daneNowejOsoby)
{
    string  liniaTekstu;

    fstream plik;
    plik.open(nazwaPliku.c_str(), ios::out | ios::app);

    if (plik.good() == true)
    {
        liniaTekstu = laczeniePojedynczychDanychWCiagZnakow(daneNowejOsoby);
        plik << liniaTekstu << endl;
        plik.close();
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac w nim danych." << endl;
        system("pause");
    }
}

void dopiszUzytkownikaDoPliku (Uzytkownik daneNowegoUzytkownika)
{
    fstream plik;
    plik.open(nazwaPliku2.c_str(), ios::out | ios::app);

    if (plik.good() == true)
    {
        plik << daneNowegoUzytkownika.idUzytkownika << '|';
        plik << daneNowegoUzytkownika.login << '|';
        plik << daneNowegoUzytkownika.haslo << '|' << endl;
        plik.close();
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac w nim danych." << endl;
        system("pause");
    }
}

void dodajAdresata(vector <Adresat> &adresaci, int &idZalogowanegoUzytkownika, int &idOstatniegoUzytkownika)
{
    Adresat daneNowejOsoby;

    daneNowejOsoby.idAdresata = idOstatniegoUzytkownika + 1;
    daneNowejOsoby.idUzytkownika = idZalogowanegoUzytkownika;

    system("cls");
    cout << ">>> DODAWANIE NOWEJ OSOBY <<<" << endl << endl;

    cout << "Podaj imie: ";
    daneNowejOsoby.imie = wczytajLinie();
    cout << "Podaj nazwisko: ";
    daneNowejOsoby.nazwisko = wczytajLinie();
    cout << "Podaj numer telefonu: ";
    daneNowejOsoby.numerTelefonu = wczytajLinie();
    cout << "Podaj email: ";
    daneNowejOsoby.email = wczytajLinie();
    cout << "Podaj adres: ";
    daneNowejOsoby.adres = wczytajLinie();

    adresaci.push_back(daneNowejOsoby);

    dopiszAdresataDoPliku(daneNowejOsoby);

    cout << endl << "Adresat zostal dodany" << endl << endl;

    system ("pause");
}

void wyszukajAdresatowPoImieniu(vector <Adresat> &adresaci)
{
    string imiePoszukiwanegoAdresata;
    int iloscAdresatow = 0;

    system("cls");
    if (!adresaci.empty())
    {
        cout << ">>> WYSZUKIWANIE PO IMIENIU <<<" << endl << endl;

        cout << "Podaj imie osoby, jaka mamy wyszukac: ";
        imiePoszukiwanegoAdresata = wczytajLinie();

        for (vector<Adresat>::iterator  itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            if (itr->imie == imiePoszukiwanegoAdresata)
            {
                cout << endl;
                cout << "Id:                 " << itr->idAdresata << endl;
                cout << "Imie:               " << itr->imie << endl;
                cout << "Nazwisko:           " << itr->nazwisko << endl;
                cout << "Numer Telefonu:     " << itr->numerTelefonu << endl;
                cout << "Nr Email:           " << itr->email << endl;
                cout << "Adres:              " << itr->adres << endl;
                iloscAdresatow++;
            }
        }
        if (iloscAdresatow == 0)
        {
            cout << endl << "Nie ma adresatow z tym imieniem w ksiazce adresowej" << endl;
        }
        else
        {
            cout << endl << "Ilosc adresatow z imieniem: >>> " << imiePoszukiwanegoAdresata << " <<<";
            cout << " w ksiazce adresowej wynosi: " << iloscAdresatow << endl << endl;
        }
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta" << endl << endl;
    }
    cout << endl;
    system("pause");
}

void wyszukajAdresatowPoNazwisku(vector <Adresat> &adresaci)
{
    string nazwiskoPoszukiwanegoAdresata;
    int iloscAdresatow = 0;

    system("cls");
    if (!adresaci.empty())
    {
        cout << ">>> WYSZUKIWANIE PO IMIENIU <<<" << endl << endl;

        cout << "Podaj imie osoby, jaka mamy wyszukac: ";
        nazwiskoPoszukiwanegoAdresata = wczytajLinie();

        for (vector<Adresat>::iterator  itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            if (itr->nazwisko == nazwiskoPoszukiwanegoAdresata)
            {
                cout << endl;
                cout << "Id:                 " << itr->idAdresata << endl;
                cout << "Imie:               " << itr->imie << endl;
                cout << "Nazwisko:           " << itr->nazwisko << endl;
                cout << "Numer Telefonu:     " << itr->numerTelefonu << endl;
                cout << "Nr Email:           " << itr->email << endl;
                cout << "Adres:              " << itr->adres << endl;
                iloscAdresatow++;
            }
        }
        if (iloscAdresatow == 0)
        {
            cout << endl << "Nie ma adresatow z tym nazwiskiem w ksiazce adresowej" << endl;
        }
        else
        {
            cout << endl << "Ilosc adresatow z nazwiskiem: >>> " << nazwiskoPoszukiwanegoAdresata << " <<<";
            cout << " w ksiazce adresowej wynosi: " << iloscAdresatow << endl << endl;
        }
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta" << endl << endl;
    }
    cout << endl;
    system("pause");
}

void usunAdresata(vector <Adresat> &adresaci, int &idZalogowanegoUzytkownika)
{
    char znak;
    int idUsuwanegoAdresata = 0;
    bool czyIstniejeAdresat = false;

    system("cls");
    cin.sync();

    if (!adresaci.empty())
    {
        cout << ">>> USUWANIE WYBRANEJ OSOBY <<<" << endl << endl;
        cout << "Podaj numer ID adresata ktorego chcesz USUNAC: ";
        idUsuwanegoAdresata = wczytajLiczbeCalkowita();

        for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            if (itr->idAdresata == idUsuwanegoAdresata)
            {
                czyIstniejeAdresat = true;
                cout << endl << endl << "Potwierdz naciskajac klawisz 't': ";
                znak = wczytajZnak();
                if (znak == 't')
                {
                    adresaci.erase(itr);
                    cout << endl << endl << "Szukany adresat zostal USUNIETY" << endl << endl;
                    zapiszAdresatowDoPliku(adresaci, idZalogowanegoUzytkownika);
                    break;
                }
                else
                {
                    cout << endl << endl << "Wybrany adresat NIE zostal usuniety" << endl << endl;
                    break;
                }
            }
        }
        if (czyIstniejeAdresat == false)
        {
            cout << endl << "Nie ma takiego adresata w ksiazce adresowej" << endl << endl;
        }
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta" << endl << endl;
    }

    system("pause");
}

void edytujAdresata(vector <Adresat> &adresaci, int &idZalogowanegoUzytkownika)
{
    char wybor;
    int idEdytowanegoAdresata;
    bool czyIstniejeAdresat = false;

    system("cls");
    cin.sync();

    if (!adresaci.empty())
    {
        cout << ">>> EDYTOWANIE WYBRANEJ OSOBY <<<" << endl << endl;
        cout << "Wprowadz id wybranego adresata: " ;
        idEdytowanegoAdresata = wczytajLiczbeCalkowita();

        for (vector <Adresat> ::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
            {
                if (itr -> idAdresata == idEdytowanegoAdresata)
                {
                    czyIstniejeAdresat = true;

                    cout << endl << "Wybierz pole, ktore chcesz edytowac: " << endl << endl;
                    cout << "1 - imie" << endl;
                    cout << "2 - nazwisko" << endl;
                    cout << "3 - numer" << endl;
                    cout << "4 - email" << endl;
                    cout << "5 - adres" << endl;
                    cout << "6 - powrot do menu" << endl;
                    cout << endl << "Twoj wybor: ";
                    wybor = wczytajZnak();

                    switch(wybor)
                    {
                    case '1':
                        cout << endl << "Podaj nowe imie: " ;
                        itr -> imie = wczytajLinie();

                        zapiszAdresatowDoPliku(adresaci, idZalogowanegoUzytkownika);

                        cout << endl << "Edycja zostala zakonczona!" << endl << endl;
                        break;

                    case '2':
                        cout << endl << "Podaj nowe nazwisko: " ;
                        itr -> nazwisko = wczytajLinie();

                        zapiszAdresatowDoPliku(adresaci, idZalogowanegoUzytkownika);

                        cout << endl << "Edycja zostala zakonczona!" << endl << endl;
                        break;

                    case '3':
                        cout << endl << "Podaj nowy numer telefonu: " ;
                        itr -> numerTelefonu = wczytajLinie();

                        zapiszAdresatowDoPliku(adresaci, idZalogowanegoUzytkownika);

                        cout << endl << "Edycja zostala zakonczona!" << endl << endl;
                        break;

                    case '4':
                        cout << endl << "Podaj nowy email: " ;
                        itr -> email = wczytajLinie();

                        zapiszAdresatowDoPliku(adresaci, idZalogowanegoUzytkownika);

                        cout << endl << "Edycja zostala zakonczona!" << endl << endl;
                        break;

                    case '5':
                        cout << endl << "Podaj nowy adres: " ;
                        itr -> adres = wczytajLinie();

                        zapiszAdresatowDoPliku(adresaci, idZalogowanegoUzytkownika);

                        cout << endl << "Edycja zostala zakonczona!" << endl << endl;
                        break;

                    case '6':
                        cout << endl << "Powrot do menu glownego" << endl << endl;
                        break;
                    default:
                        cout << endl << "Nie ma takiej opcji w menu! Powrot do menu glownego." << endl << endl;
                        break;
                    }
                }
            }

            if (czyIstniejeAdresat == false)
            {
                cout << endl << "Nie ma takiego adresata w ksiazce adresowej." << endl << endl;
            }
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta." << endl << endl;
    }
    system("pause");
}

void zakonczProgram()
{
    cout << endl << "Koniec programu." << endl;
    exit(0);
}

void zapiszUzytkownikowDoPliku (vector <Uzytkownik> &uzytkownicy)
{
    string liniaZDanymiAdresata = "";
    fstream plik;

    plik.open(nazwaPliku2.c_str(), ios::out | ios:: trunc);

    if (plik.good())
    {
        for (vector <Uzytkownik> ::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); ++itr)
        {
            liniaZDanymiAdresata += konwersjaIntNaString(itr->idUzytkownika) + '|';
            liniaZDanymiAdresata += itr->login + '|';
            liniaZDanymiAdresata += konwersjaIntNaString(itr->haslo) + '|';

            plik << liniaZDanymiAdresata << endl;
            liniaZDanymiAdresata = "";
        }
        plik.close();
    }
    else
    {
        cout << "Nie mozna otworzyc pliku Uzytkownicy.txt" << endl;
    }
}

void zmienHaslo(vector <Uzytkownik> &uzytkownicy, int &idZalogowanegoUzytkownika)
{
    int noweHaslo = 0;

    cout <<"Podaj nowe haslo: ";
    noweHaslo = wczytajLiczbeCalkowita();

    for (vector<Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
        {
            if (itr->idUzytkownika == idZalogowanegoUzytkownika)
            {
                itr->haslo = noweHaslo;
                zapiszUzytkownikowDoPliku(uzytkownicy);
            }
        }

    cout <<"Haslo zostalo zmienione " << endl;
    system("pause");
}

void logowanie(vector <Uzytkownik> &uzytkownicy)
{
    vector <Adresat> adresaci;
    int idZalogowanegoUzytkownika = 0, haslo = 0, iloscProbLogowania = 0, idOstatniegoUzytkownika = 0;
    string login = "";
    char wybor = 'x';
    bool czyIstniejeUzytkownik = false;

    if (!uzytkownicy.empty())
    {
        cout << "Podaj login: ";
        login = wczytajLinie();

        for (vector<Uzytkownik>::iterator  itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
        {
            if (itr->login == login)
            {
                czyIstniejeUzytkownik = true;

                while (iloscProbLogowania <3)
                {
                    cout << "Podaj haslo: Pozostalo prob " << 3 - iloscProbLogowania <<": ";
                    haslo = wczytajLiczbeCalkowita();

                    if (itr->haslo == haslo)
                    {
                        idZalogowanegoUzytkownika = itr->idUzytkownika ;

                        cout << "Zalogowales sie." << endl;
                        system("pause");

                        while(wybor != '8')
                        {
                            idOstatniegoUzytkownika = wczytajAdresatowZPliku(adresaci, idZalogowanegoUzytkownika);

                            system("cls");
                            cin.sync();

                            cout << ">>> KSIAZKA ADRESOWA <<<" << endl;
                            cout << "-------------------------" << endl;
                            cout << "1. Dodaj adresata" << endl;
                            cout << "2. Wyszukaj adresatow po imieniu" << endl;
                            cout << "3. Wyszukaj adresatow po nazwisku" << endl;
                            cout << "4. Wyswietl wszystkich adresatow" << endl;
                            cout << "5. Usun adresata" << endl;
                            cout << "6. Edytuj adresata" << endl;
                            cout << "-------------------------" << endl;
                            cout << "7. Zmien haslo" << endl;
                            cout << "8. Wyloguj sie" << endl;
                            cout << "-------------------------" << endl;
                            cout << "9. Zakoncz program" << endl;
                            cout << "-------------------------" << endl;
                            cout << "Twoj wybor: ";
                            wybor = wczytajZnak();

                            switch(wybor)
                            {
                            case '1':
                                dodajAdresata(adresaci,idZalogowanegoUzytkownika, idOstatniegoUzytkownika);
                                break;
                            case '2':
                                wyszukajAdresatowPoImieniu(adresaci);
                                break;
                            case '3':
                                wyszukajAdresatowPoNazwisku(adresaci);
                                break;
                            case '4':
                                wyswietlWszystkichAdresatow(adresaci);
                                break;
                            case '5':
                                usunAdresata(adresaci, idZalogowanegoUzytkownika);
                                break;
                            case '6':
                                edytujAdresata(adresaci, idZalogowanegoUzytkownika);
                                break;
                            case '7':
                                zmienHaslo(uzytkownicy, idZalogowanegoUzytkownika);
                                break;
                            case '8':

                                break;
                            case '9':
                                zakonczProgram();
                                break;
                            }
                        }
                        break;
                    }
                    iloscProbLogowania++;
                }
                if (iloscProbLogowania == 3)
                {
                    cout  << "Wprowadzono nieprawidlowe haslo 3 razy. Nastapi powrot do menu glownego" << endl;
                    system("pause");
                    break;
                }
            }
        }
        if (czyIstniejeUzytkownik == false)
        {
            cout << "Wprowadzono nieprawidlowy login" << endl;
            system("pause");
        }
    }
    else
    {
        cout << "Brak uzytkownikow w bazie" << endl << endl;
        system("pause");
    }
}

void rejestracja (vector <Uzytkownik> &uzytkownicy)
{
    Uzytkownik daneNowegoUzytkownika;

    if (uzytkownicy.empty() == true)
    {
        daneNowegoUzytkownika.idUzytkownika = 1;
    }
    else
    {
        daneNowegoUzytkownika.idUzytkownika = uzytkownicy.back().idUzytkownika + 1;
    }

    cout << "Podaj login: ";
    daneNowegoUzytkownika.login = wczytajLinie();
    cout << "Podaj haslo: ";
    daneNowegoUzytkownika.haslo = wczytajLiczbeCalkowita();

    uzytkownicy.push_back(daneNowegoUzytkownika);

    dopiszUzytkownikaDoPliku(daneNowegoUzytkownika);

    cout << endl << "Konto zalozono pomyslnie" << endl << endl;

    system ("pause");
}

int main()
{
    vector <Uzytkownik> uzytkownicy;
    char wybor;

    wczytajUzytkownikowZPliku(uzytkownicy);

    while(true)
    {
        system("cls");
        cin.sync();
        cout << ">>> MENU GLOWNE <<<" << endl;
        cout << "-------------------------" << endl;
        cout << "1. Rejestracja" << endl;
        cout << "2. Logowanie" << endl;
        cout << "9. Zakoncz program" << endl;
        cout << "-------------------------" << endl;
        cout << "Twoj wybor: ";
        wybor = wczytajZnak();
        cout << endl;

        switch(wybor)
        {
        case '1':
            rejestracja(uzytkownicy);
            break;
        case '2':
            logowanie(uzytkownicy);
            break;
        case '9':
            zakonczProgram();
            break;
        }
    }
    return 0;
}
