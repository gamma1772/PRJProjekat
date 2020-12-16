//Marko Dujović, NRT-85/19

#include<iostream>
#include<fstream>
#include<string>

#define MAX 80
#define BROJ 50;

using namespace std;

struct osoba
{
	int idZaposlenog;
	char* ime, * prezime;
	char poruka[MAX + 1];
	char* tel, * adresaStanovanja;
};

void sifrovanje();
void desifrovanje();


void cezar(fstream f, int odstup);
void vizner(fstream f, int odstup, char * sifra);
void hill(fstream f, int broj);

void upis(osoba o, fstream f);
void stampa(osoba o);

int main()
{
	char c, imeBaze[MAX + 1];
	int i, n;
	osoba* baza;

	cout << "Unesite ime baze: ";
	cin >> imeBaze;

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
	for (i = 0; i < n; i++)
	{

	}

	cout << "Unos podataka je uspesno zavrsen. Da li zelite da sifrujete unete podatke (D/N): ";
	cin >> c;

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

void sifrovanje()
{
}

void desifrovanje()
{

}

void upis(osoba o, fstream f)
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