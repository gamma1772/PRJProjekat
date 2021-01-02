//Marko Dujović, NRT-85/19

/*O programu:
 * Program predstavlja jedan koncept kako bi izgledao upis i zaštita podatake neke firme. Podaci se prvobitno upisuju u strukture koje se kasnije prepisuju u fajl, i na
 * kraju se šifruju pomoću jedne od tri metode: Cezarovo šifrovanje, Vižnerovo šifrovanje i Hilovo sifrovanje. Prva dva tipa šifrovanja su jednostavni, tako da se 
 * ne preporučuju za šifrovanje nekih važnih podataka, zato što mogu veoma lako da se dešifruju uz pomoć frekventne analize teksta.
 */

#include<iostream>
#include<fstream>
#include<string>
#include<stdio.h>
#include<ctype.h>

#define MAX 100
#define BROJ 50;

using namespace std;


//Struktura osoba sadrži podatke za zaposlenog.
struct osoba
{
	int idZaposlenog; //idZaposlenog se automatski inkrementira za 1.
	char* ime, * prezime;
	char poruka[MAX + 1];
	char *adresaStanovanja;
	char* tel;
};

void info(char* imeF);

void proveraFajla(char *imeFajla);

void sifrovanje(char *imeF);
void desifrovanje(char *f);

void cezar(char *imeF, int odstup);
void vizner(char *imeF, int odstup, char * sifra);
void hill(char *imeF, char *sifra);

void unosPodataka(osoba *o, char *imeF, int n);


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

	baza = new osoba[n];
	if (baza == NULL) { cerr << "\nGreska u dodeli memorije!"; exit(1); }

	//Pocetak unosenja podataka
	unosPodataka(baza, imeFajla, n);

	cout << "Unos podataka je uspesno zavrsen. Da li zelite da sifrujete unete podatke (D/N): ";
	cin >> c;

	delete [] baza;

	switch (toupper(c))
	{
	case 'D':
		sifrovanje(imeFajla);
	case 'N':
		cout << "Izlaz iz programa..." << endl;
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
	f.open(imeFajla, ios::in | ios::_Nocreate);
	if (f.is_open())
	{
		do
		{
			cout << "\n\nUPOZORENJE: Fajl vec postoji! Da li zelite da desifrujete (D), izmenite (I) sadrzaj u koliko nije sifrovan, ili da obrisete (O) fajl?\nUnos: ";
			cin >> c; toupper(c);
		} while (c != 'D' && c != 'O' && c != 'I');
		switch (c)
		{
		case 'D':
			desifrovanje(imeFajla);
		case 'I':

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

/*
 * Upis podataka u datoteku.
 * 
 * osoba o - Struktura tipa osoba, u nju se prvo unose podaci.
 * char *imeF - Ime fajla.
 * int n - broj struktura koji je korisnik naveo.
 */
void unosPodataka(osoba *o, char *imeF, int n)
{

}

/*
 * Upit za korisnika na koji način želi da šifruje podatke, ili da izbaci informacije o dostupnim vrstana šifrovanja.
 *
 * char *imeF - Ime datoteke koje se prosleđuje drugim funkcijama koje pozivaju ovu funkciju.
 */
void sifrovanje(char* imeF)
{
	int broj;
	int odstup;

	cout << "Na koji nacin zelite da sifrujete fajl?\n\n1. Cezarovo sifrovanje\n2. Viznerovo sifrovanje\n3. Hilovo sifrovanje\n\nUnesite redni broj, ili '?' ako zelite da vidite primere sifrovanja: ";
	cin >> broj;
	switch (broj)
	{
	case 1:
		cout << "Unesite koliko karaktera ce biti odstup u tekstu: "; cin >> odstup;
		cezar(imeF, odstup);
	case 2:
	case 3:
	case '?':
		info(imeF);
	default:
		break;
	}
}

/*
 * Izbacuje primere šifrovanja u konzolu i vraća program u sifrovanje().
 * 
 * imeF - Ime fajla. Služi samo za vraćanje u funkciju sifrovanje()
 */
void info( char *imeF)
{
	cout << "Cezarovo sifrovanje"
		 << "\nSvako slovo teksta koji se sifruje vraca se za n karaktera unazad. Primer:"
		 << "\n\n'The quick brown fox jumps over the lazy dog', sa pomerajem od 3 bice:"
		 <<   "\n'Wkh txlfn eurzq ira mxpsv ryhu wkh odcb grj'";

	cout << "\n\nViznerovo sifrovanje" 
		 << "\nSvako slovo teksta se zamenjuje za sumu odgovarajucih slova iz teksta i sifre. Primer" 
		 << "\n\n'Almost before we knew it, he had left the ground' sa sifrom 'lemon':" 
		 <<   "\n'Lpycfe fqtbci is xyii wg, hi toq wirh gsi sfbfrp'";

	cout << "\n\nHilovo sifrovanje"
		<< "\nSvako slovo teksta i sifre se pretvara u svoju numericku vrednost i postavlja u zasebnu matricu, i zatim se matrice pomnoze. Primer"
		<< "\nTekst 'ACT' i sifra 'GYBNQKURP':"
		<<   "\nkljuc GYBNQKURP ce biti:\t\ttekst ACT ce biti:"
		<< "\n\n|G Y B|   | 6 24  1|" << "    \t\t |A|   | 0|"
		<<   "\n|N Q K| = |13 16 10|" << "    \t\t |C| = | 2|"
		<<   "\n|U R P|   |20 17 15|" << "    \t\t |T|   |19|"
		<< "\n\nKad se ove dve matrice pomnoze dobije se rezultujuca matrica, koja kad se pretvori nazad u tekst dobije se 'POH':"
		<< "\n\n|15|   |P|"
		<<   "\n|14| = |O|"
		<<   "\n| 7|   |H|";
	sifrovanje(imeF);
}


/*
 * Cezaova šifra je vrsta šifrovanja prostog teksta. Tekst se šifruje tako što se svako 
 * slovo teksta menja odgovarajućim znakom koji je pomeren za odgovarajući broj mesta u levo.
 * 
 * imeF - Ime datoteke u kojoj se nalaze podaci
 * odstup - Broj karaktera za koji se vrši odstupanje unazad u tekstu.
 */
void cezar(char *imeF, int odstup)
{
	int i;
	char identifikator = 'A';
	int duzina;
	char *tekst, *temp;
	fstream f;
	
	//Otvaranje fajla u rezimu citanja, trazenje duzine ukupnog teksta i dodela memorije
	f.open(imeF, ios::in);
	f.seekg(0, ios::end);
	duzina = f.tellg();

	tekst = new char[duzina];
	temp = new char[duzina];

	//Vracanje na pocetak fajla i upis u bafer 'tekst'
	f.seekg(0, ios::beg);
	f.read(tekst, duzina);

	//Sifrovanje se deli u tri klase: za velika slova, mala slova i pomoćne znakove, koji se ne menjaju.
	for (i = 0; i < duzina; i++)
	{
		//Sifrovanje velikih slova:
		//Formula E(x) = (x + n) mod 26. 65 i 97 se dodaju zato što se koristi ASCII format, a mod 26 znači da je formula ograničena na 26 karaktera.
		//Dešifrovanje se vrši na sličan način: D(x) = (x - n) mod 26.
		if (isupper(tekst[i]))
		{
			temp += char(int(tekst[i] + odstup - 65) % 26 + 65); 
		}
		
		//Sifrovanje malih slova
		else if (islower(tekst[i]))
		{
			temp += char(int(tekst[i] + odstup - 97) % 26 + 97);
		}

		//preskakanje sifrovanja znakova koji nisu slova
		else { temp += tekst[i]; }
	}

	f.close();

	//Upis u fajl
	f.open(imeF, ios::out | ios::trunc);

	f.seekg(0, ios::beg);
	f.write(temp, duzina);

	

	f.close();

	delete [] tekst;
	delete [] temp;
}

/*
 * Vižnerova šifra je modifikacija Cezarove šifre.
 */
void vizner(char *imeF, int odstup, char* sifra)
{
	char identifikator = 'B';
	char tempchar;
	int i, j = 0, duzina;
	char* tekst, * temp, *kljuc;
	fstream f;

	f.open(imeF, ios::in);
	f.seekg(0, ios::end);
	duzina = f.tellg();

	tekst = new char[duzina];
	temp = new char[duzina];
	kljuc = new char[duzina];

	f.seekg(0, ios::beg);
	f.read(tekst, duzina);

	//Generisanje kljuca uz pomoc sifre
	for (i = 0; i < sizeof(kljuc) - 1; i++)
	{
		kljuc[i] = sifra[j];
		if (j == strlen(sifra) - 1)
		{
			j = -1;
		}
		j++;
	}

	for (i = 0; i < duzina; i++)
	{
		if (isupper(tekst[i]))
		{
			if (islower(kljuc[i]))
			{
				kljuc[i] = toupper(kljuc[i]);
			}
			temp += char(int(tekst[i] + kljuc[i] - 65) % 26 + 65);
		}
		else if (islower(tekst[i]))
		{
			if (isupper(kljuc[i]))
			{
				kljuc[i] = tolower(kljuc[i]);
			}
			temp += char(int(tekst[i] + kljuc[i] - 97) % 26 + 97);
		}
		else if (isalnum(kljuc[i]))
		{
			temp += int(tekst[i] + kljuc[i] - 48) % 10 + 48;
		}
		else
		{
			temp += tekst[i];
		}
	}

	f.open(imeF, ios::in);
}

/*
 * Hilovo šifrovanje je zasnovano na matricama. Slova teksta i šifre se pretvaraju u svoje redne brojeve (od 0 do 25 za alfabet), 
 * šifra se ubacuje u n* n matricu, dok se tekst ubacuje u vektorsku matricu(n * 1), gde je n broj clanova vektorske matrice. 
 * Te dve matrice se pomnože i dobije se rezultujuća matrica koja je šifrovan tekst kada se članovi ove matrice pretvore u tekst.
 *
 * imeF - Funkcija dobija ime fajla u kom se nalaze podaci. Ti podaci se šifruju i upisuju u novi fajl.
 * sifra - šifra za šifrovanje podataka.
 */
void hill(char *imeF, char* sifra)
{
	char identifikator = 'C';
}

void desifrovanje(char* imeF)
{
	fstream f;
	char id;


	//Otvara fajl u rezimu za citanje i cita poslednji karakter u fajlu da bi odredio vrstu sifrovanja.
	f.open(imeF, ios::in);
	f.seekg(0, ios::end);
	f.get(id);
}