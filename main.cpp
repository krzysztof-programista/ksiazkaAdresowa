#include <iostream>
#include <sstream>
#include <string>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <vector>
using namespace std;

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
    int id = 0;
    string imie = "", nazwisko = "", numerTelefonu = "", email = "", adres = "";
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

    liniaTekstu = konwersjaIntNaString(daneOsoby.id) + przerywnik + daneOsoby.imie + przerywnik + daneOsoby.nazwisko + przerywnik + daneOsoby.numerTelefonu + przerywnik + daneOsoby.email + przerywnik + daneOsoby.adres + przerywnik;

    return liniaTekstu;
}

void wczytajAdresatowZPliku(vector <Adresat> &adresaci)
{
    Adresat danePojedynczejOsoby;
    vector <string> daneDotyczaceJednejOsoby;
    string liniaTekstu;
    string linia;
    int numerLinii = 1;

    fstream plik;
    plik.open("ksiazkaAdresowa.txt", ios::in);

    if(plik.good() == false)
    {
        cout << "Brak pliku bazowego!" << endl;
        Sleep(1000);
    }
    else
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

            danePojedynczejOsoby.id = stoi(daneDotyczaceJednejOsoby[0]);
            danePojedynczejOsoby.imie = daneDotyczaceJednejOsoby[1];
            danePojedynczejOsoby.nazwisko = daneDotyczaceJednejOsoby[2];
            danePojedynczejOsoby.numerTelefonu = daneDotyczaceJednejOsoby[3];
            danePojedynczejOsoby.email = daneDotyczaceJednejOsoby[4];
            danePojedynczejOsoby.adres = daneDotyczaceJednejOsoby[5];

            adresaci.push_back(danePojedynczejOsoby);
        }
        plik.close();
    }

}

void wyswietlWszystkichAdresatow(vector <Adresat> &adresaci)
{
    system("cls");

    cout << ">>> LISTA WSZYSKICH ADRESATOW <<<" << endl << endl;
    unsigned int i = 0;
    while (i < adresaci.size())
    {
        cout <<"ID:                      " << adresaci[i].id << endl;
        cout <<"Imie:                    " << adresaci[i].imie << endl;
        cout <<"Nazwisko:                " << adresaci[i].nazwisko << endl;
        cout <<"Numer telefonu:          " << adresaci[i].numerTelefonu << endl;
        cout <<"Email:                   " << adresaci[i].email << endl;
        cout <<"Adres:                   " << adresaci[i].adres << endl;
        cout << endl;

        i++;
    }

    cout << endl << "Nacisnij dowolny klawisz, aby przejsc dalej..." << endl;
    getchar();
}

void dodajAdresata(vector <Adresat> &adresaci)
{
    fstream plik;
    int idDodawanegoAdresata;
    Adresat daneOstatniejOsoby, daneNowejOsoby;
    string imie, nazwisko, numerTelefonu, email, adres, liniaTekstu;

    plik.open("ksiazkaAdresowa.txt", ios::in);

    if(plik.good() == false)
    {
        idDodawanegoAdresata = 1;
    }
    else
    {
        daneOstatniejOsoby = adresaci[adresaci.size() - 1];
        idDodawanegoAdresata = daneOstatniejOsoby.id + 1;
    }

    plik.close();

    system("cls");

    cout << ">>> DODAWANIE NOWEJ OSOBY <<<" << endl << endl;

    cout << "Podaj imie: ";
    imie = wczytajLinie();
    cout << "Podaj nazwisko: ";
    nazwisko = wczytajLinie();
    cout << "Podaj numer telefonu: ";
    numerTelefonu = wczytajLinie();
    cout << "Podaj email: ";
    email = wczytajLinie();
    cout << "Podaj adres: ";
    adres = wczytajLinie();


    daneNowejOsoby.id = idDodawanegoAdresata;
    daneNowejOsoby.imie = imie;
    daneNowejOsoby.nazwisko = nazwisko;
    daneNowejOsoby.numerTelefonu = numerTelefonu;
    daneNowejOsoby.email = email;
    daneNowejOsoby.adres = adres;

    adresaci.push_back(daneNowejOsoby);

    liniaTekstu = laczeniePojedynczychDanychWCiagZnakow(daneNowejOsoby);


    plik.open("ksiazkaAdresowa.txt", ios::out | ios::app);

    plik << liniaTekstu << endl;

    plik.close();

    cout << endl << "Osoba zostala dodana" << endl << endl;

    cout << "Nacisnij dowolny klawisz, aby przejsc dalej..." << endl;
    getchar();
}

void zapiszAdresatowDoPliku(vector <Adresat> &adresaci)
{
    string liniaTekstu;
    fstream plik;
    plik.open("ksiazkaAdresowa.txt", ios::out | ios:: trunc);

    for (vector <Adresat> ::iterator itr = adresaci.begin(); itr != adresaci.end(); ++itr)
    {
        liniaTekstu = laczeniePojedynczychDanychWCiagZnakow(*itr);
        plik << liniaTekstu << endl;
    }

    plik.close();
}

void wyszukajAdresatowPoImieniu(vector <Adresat> &adresaci)
{
    string imie;

    system("cls");

    cout << ">>> WYSZUKIWANIE PO IMIENIU <<<" << endl << endl;
    cout << "Podaj imie osoby, jaka mamy wyszukac: ";
    imie = wczytajLinie();
    cout << endl;

    unsigned int i = 0;
    int licznik = 0;
    while (i < adresaci.size())
    {
        if (imie == adresaci[i].imie)
        {
            cout <<"ID:                      " << adresaci[i].id << endl;
            cout <<"Imie:                    " << adresaci[i].imie << endl;
            cout <<"Nazwisko:                " << adresaci[i].nazwisko << endl;
            cout <<"Numer telefonu:          " << adresaci[i].numerTelefonu << endl;
            cout <<"Email:                   " << adresaci[i].email << endl;
            cout <<"Adres:                   " << adresaci[i].adres << endl;
            cout << endl;
            licznik++;
        }
        i++;
    }
    if (licznik == 0)
    {
        cout << "Brak w ksiazce adresowej osob z podanym imieniem !" << endl << endl << endl;
    }

    cout << "Nacisnij dowolny klawisz, aby przejsc dalej..." << endl;
    getchar();
}

void wyszukajAdresatowPoNazwisku(vector <Adresat> &adresaci)
{
    string nazwisko;

    system("cls");

    cout << ">>> WYSZUKIWANIE PO NAZWISKU <<<" << endl << endl;
    cout << "Podaj nazwisko osoby, jaka mamy wyszukac: ";
    nazwisko = wczytajLinie();
    cout << endl;

    unsigned int i = 0;
    int licznik = 0;
    while (i < adresaci.size())
    {
        if (nazwisko == adresaci[i].nazwisko)
        {
            cout <<"ID:                      " << adresaci[i].id << endl;
            cout <<"Imie:                    " << adresaci[i].imie << endl;
            cout <<"Nazwisko:                " << adresaci[i].nazwisko << endl;
            cout <<"Numer telefonu:          " << adresaci[i].numerTelefonu << endl;
            cout <<"Email:                   " << adresaci[i].email << endl;
            cout <<"Adres:                   " << adresaci[i].adres << endl;
            cout << endl;
            licznik++;
        }
        i++;
    }
    if (licznik == 0)
    {
        cout << "Brak w ksiazce adresowej osob z podanym nazwiskiem !" << endl << endl << endl;
    }

    cout << "Nacisnij dowolny klawisz, aby przejsc dalej..." << endl;
    getchar();
}

void usunAdresata(vector <Adresat> &adresaci)
{
    char potwierdzenieWyboru;
    Adresat daneUsuwanejOsoby;
    int idUsuwanegoAdresata, zmiennaPomocnicza = 0;

    system("cls");
    cin.sync();
    cout << ">>> USUWANIE WYBRANEJ OSOBY <<<" << endl << endl;
    cout << "Podaj numer ID adresata, ktrego chcesz USUNAC: ";

    idUsuwanegoAdresata = wczytajLiczbeCalkowita();

    cout << endl;

    for (vector <Adresat> ::iterator itr = adresaci.begin(); itr != adresaci.end(); ++itr)
    {
        if (itr -> id == idUsuwanegoAdresata)
        {
            cout << "Potwierdz naciskajac klawisz 't':  ";
            potwierdzenieWyboru = wczytajZnak();
            zmiennaPomocnicza++;

            if (potwierdzenieWyboru == 't')
            {
                adresaci.erase(itr);

                zapiszAdresatowDoPliku(adresaci);

                cout << endl << "Szukany adresat zostal USUNIETY!"  << endl << endl;
            }
            else
            {
                cout << endl << "Wpisano nieporawny znak! Nastapi powrot do menu glownego "  << endl << endl;
            }
            break;
        }
    }

    if (zmiennaPomocnicza == 0)
    {
        cout << "Brak adresata o podanym id!"<< endl << endl;
    }


    cout << endl << "Nacisnij dowolny klawisz, aby przejsc dalej..." << endl;
    getchar();
}

void edytujAdresata(vector <Adresat> &adresaci)
{
    char wybor;
    int idEdytowanegoAdresata, zmiennaPomocnicza = 0;
    string imie = "", nazwisko = "", numerTelefonu = "", email = "", adres = "";

    system("cls");
    cin.sync();
    cout << ">>> EDYTOWANIE WYBRANEJ OSOBY <<<" << endl << endl;
    cout << "Wprowadz id wybranego adresata: " ;
    idEdytowanegoAdresata = wczytajLiczbeCalkowita();

    for (vector <Adresat> ::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
    {
        if (itr -> id == idEdytowanegoAdresata)
        {
            zmiennaPomocnicza++;

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
                imie = wczytajLinie();
                itr -> imie = imie;

                zapiszAdresatowDoPliku(adresaci);

                cout << endl << "Edycja zostala zakonczona!" << endl << endl;
                break;

            case '2':
                cout << endl << "Podaj nowe nazwisko: " ;
                nazwisko = wczytajLinie();
                itr -> nazwisko = nazwisko;

                zapiszAdresatowDoPliku(adresaci);

                cout << endl << "Edycja zostala zakonczona!" << endl << endl;
                break;

            case '3':
                cout << endl << "Podaj nowy numer telefonu: " ;
                numerTelefonu = wczytajLinie();
                itr -> numerTelefonu = numerTelefonu;

                zapiszAdresatowDoPliku(adresaci);

                cout << endl << "Edycja zostala zakonczona!" << endl << endl;
                break;

            case '4':
                cout << endl << "Podaj nowy email: " ;
                email = wczytajLinie();
                itr -> email = email;

                zapiszAdresatowDoPliku(adresaci);

                cout << endl << "Edycja zostala zakonczona!" << endl << endl;
                break;

            case '5':
                cout << endl << "Podaj nowy adres: " ;
                adres = wczytajLinie();
                itr -> adres = adres;

                zapiszAdresatowDoPliku(adresaci);

                cout << endl << "Edycja zostala zakonczona!" << endl << endl;
                break;

            case '6':
                break;

            }
            break;
        }
    }

    if (zmiennaPomocnicza == 0)
    {
        cout << endl<< "Brak adresata o podanym id!"<< endl << endl;
    }

    cout << endl << "Nacisnij dowolny klawisz, aby przejsc dalej..." << endl;
    getchar();
}

int main()
{
    vector <Adresat> adresaci;
    char wybor;

    wczytajAdresatowZPliku(adresaci);

    while(true)
    {
        system("cls");
        cin.sync();
        cout << ">>> KSIAZKA ADRESOWA <<<" << endl << endl;
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zakoncz program" << endl;
        cout << endl << "Twoj wybor: ";
        wybor = wczytajZnak();

        switch(wybor)
        {
        case '1':
            dodajAdresata(adresaci);
            zapiszAdresatowDoPliku(adresaci);
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
            usunAdresata(adresaci);
            break;
        case '6':
            edytujAdresata(adresaci);
            break;
        case '9':
            exit(0);
            break;
        }
    }
    return 0;
}
