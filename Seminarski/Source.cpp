//Marko Dujović, NRT-85/19

/*O programu:
 * Program predstavlja jedan koncept kako bi izgledao upis i zaštita podatake neke firme. Podaci se prvobitno upisuju u strukture koje se kasnije prepisuju u fajl, i na
 * kraju se šifruju pomoću jedne od tri metode: Cezarovo šifrovanje, Vižnerovo šifrovanje i Hilova enkripcija. Prva dva tipa šifrovanja su jednostavni, tako da se 
 * ne preporučuju za šifrovanje nekih važnih podataka, zato što mogu veoma lako da se dešifruju uz pomoć frekventne analize teksta.
 * 
 * @param u komentarima koda nema veliku ulogu, skraćeno je od parametar i služi samo za dokumentaciju funkcija. Visual Studio ne koristi ovu anotaciju, ali neka druga
 * razvojna okruženja, kao što su 'Eclipse IDE For C++' ili 'IntelliJ CLion' koriste ovu anotaciju.
 */

#include<iostream>
#include<fstream>
#include<string>
#include<stdio.h>

#define MAX 80
#define BROJ 50;

using namespace std;

/*
 * Struktura osoba: sadrži podatke za zaposlenog.
 *		@param idZaposlenog - Identifikacioni broj zaposlenog. U slučaju ovog programa, ovaj parametar se automatski inkrementira za 1.
 *		@param poruka - Poruka ili napomena za nekog zaposlenog, može da sadrži do 80 karaktera.
 */
struct osoba
{
	int idZaposlenog;
	char* ime, * prezime;
	char poruka[MAX + 1];
	char* tel, * adresaStanovanja;
};

void proveraFajla(char *imeFajla);

void sifrovanje();
void desifrovanje(char *f);

void cezar(fstream f, int odstup);
void vizner(fstream f, int odstup, char * sifra);
void hill(fstream f, int broj);

void upis(osoba *o, char *imeF, int n);
void stampa(osoba o);

int main()
{
	char c, imeFajla[MAX + 1];
	int i, n;
	osoba* baza;

	//Imenovanje i kreiranje baze
	cout << "Unesite ime fajla: ";
	cin >> imeFajla;

	proveraFajla(imeFajla);

	//Upit za korisnika da unese broj osoba
	do
	{
	cout << "Do koliko clanova ce sadrzati baza?\nNAPOMENA: baza moze da sadrzi do 50 clanova: ";
	cin >> n;
	if (n > 50)
		cout << "Uneli ste prevelik broj!";
	else if (n < 1)
		cout << "Uneli ste premali broj!";
	} 
	while (n < 0 || n > 50);

	//Pocetak unosenja podataka
	upis(baza, imeFajla, n);

	cout << "Unos podataka je uspesno zavrsen. Da li zelite da sifrujete unete podatke (D/N): ";
	cin >> c;
	toupper(c);

	switch (c)
	{
	case 'D':
		sifrovanje();
	case 'N':
		exit(0);
	default:
		break;
	}
	return 0;
}

void proveraFajla(char *imeFajla)
{
	fstream f;
	char c;
	f.open(imeFajla, ios::in | ios::out);
	if (f.is_open())
	{
		do
		{
			cout << "\n\nUPOZORENJE: Fajl vec postoji! Da li zelite da desifrujete (D) i izmenite sadrzaj, ili da obrisete (O) fajl?\nUnos: ";
			cin >> c; toupper(c);
		} while (c != 'D' || c != 'O');
		switch (c)
		{
		case 'D':
			desifrovanje(imeFajla);
		case 'O':
			remove(imeFajla);
		default:
			break;
		}
	}
	else
	{
		f.clear();
	}
}

void sifrovanje()
{
}

void desifrovanje(char *f)
{

}

/*Upis podataka.
 *		@param osoba *o - Struktura tipa osoba, u nju se prvo unose podaci;
 *		@param char *imeF - Ime fajla u koji će se unositi podaci
 *		@param int n - broj struktura koji je korisnik naveo
 */

void upis(osoba *o, char *imeF, int n)
{

}

void stampa(osoba o)
{

}

/*
* Cezaova šifra je vrsta šifrovanja prostog teksta. Tekst se šifruje tako što se svako slovo teksta menja
* odgovarajućim znakom koji je pomeren za odgovarajući broj mesta u levo
*/
void cezar(fstream f, int odstup)
{
}

/*
* Vižnerova šifra je modifikacija Cezarove šifre. Ovde se koristi ključna reč kao maska.
*/
void vizner(fstream f, int odstup, char* sifra)
{

}
/*
* Hilovo šifrovanje je zasnovano na linearnoj algebri. Svako slovo se promeni u svoj redni broj
* i ubaci se u n*n matricu, i pomnoži se sa željenim brojem. Rezultujuća matrica je šifrovan podatak.
*/
void hill(fstream f, int broj)
{

}