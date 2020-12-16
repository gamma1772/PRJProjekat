//Marko Dujović, NRT-85/19

#include<iostream>
#include<fstream>
#include<string>

#define MAX 80
#define BROJ 50;

void sifrovanje();
void desifrovanje();

void cezar(std::fstream f, int odstup);
void vizner(std::fstream f, int odstup, char * sifra);
void hill(std::fstream f, int broj);

struct osoba
{
	int id;
	char* ime, *prezime, poruka[MAX + 1];
	char* tel;
};

int main()
{
	char c;
	int n;
	osoba* baza;
	do{
	std::cout << "Do koliko clanova ce sadrzati baza?\nNAPOMENA: baza moze da sadrzi do 50 clanova: ";
	std::cin >> n;
	} while (n < 0 || n > 50);


	std::cout << "Unos podataka je uspesno zavrsen. Da li zelite da sifrujete unete podatke (D/N): ";
	std::cin >> c;

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


/*
* Cezaova šifra je vrsta šifrovanja prostog teksta. Tekst se šifruje tako što se svako slovo teksta menja
* odgovarajućim znakom koji je pomeren za odgovarajući broj mesta u levo. Na primer uzmemo pomeraj od 3 mesta, 
* tad slovo D postaje slovo A, E postaje slovo B itd. Slova A, B i C postaju X, Y i Z. Ako primenimo ovo šifrovanje
* na ASCII tabeli, imamo na raspolaganju 128 znakova, u poređenju sa 26 iz abecede.
*/
void cezar(std::fstream f, int odstup)
{

}

/*
* Vižnerova šifra je modifikacija Cezarove šifre. Ovde se koristi ključna reč kao maska.
* Poruka se šifruje uz pomoć te maske na sledeći način:
* uzmeno rečenicu 'Almost before we knew it, we had left the ground' i ključnu reč 'MACHINE':
* 
* ALMOST BEFORE WE KNEW IT WE HAD LEFT THE GROUND
* MACHIN EMACHI NE MACH IN EM ACH INEM ACH INEMAC
* 
* Rezultujući tekst je sledeći:
* MLOVAG FQFQYM JI WNGD QG AQ HCK TRJF TJL OESGNF
*/
void vizner(std::fstream f, int odstup, char* sifra)
{

}
/*
* Hilovo šifrovanje je zasnovano na linearnoj algebri. Svako slovo se promeni u svoj redni broj
* i ubaci se u n*n matricu, i pomnoži se sa željenim brojem. Rezultujuća matrica je šifrovan podatak.
*/
void hill(std::fstream f, int broj)
{

}