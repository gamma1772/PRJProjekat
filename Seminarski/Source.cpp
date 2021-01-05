#define _CRT_SECURE_NO_WARNINGS

//Marko Dujović, NRT-85/19

#include<iostream>
#include<fstream>
#include<string>

#include<stdio.h>
#include<ctype.h>

#define MAX 80
#define BROJ 20

using namespace std;

//Struktura osoba sadrži podatke za zaposlenog.
//Redosled: ID, Ime, Prezime Telefon, Mesto Stanovanja.
struct zaposleni { int idZaposlenog; char ime[BROJ + 1], prezime[BROJ + 1], tel[14]; /*char poruka[100 + 1];*/ };
struct adresaStanovanja { char imeUlice[MAX + 1], broj[5], mesto[BROJ + 1], grad[BROJ + 1]; }; //Broj je char uzimajućji u obzir da broj kuće ili stana može da bude 1A, 2B, 3C itd.
struct kontakt { char* tel, * mail; };

fstream f;
char imeFajla[MAX + 1];
int brojZaposlenih = 0;

void info(char* imeF = imeFajla);

void proveraFajla(zaposleni* osoba, adresaStanovanja* adresa, char* imeF = imeFajla);

void sifrovanje(zaposleni* osoba, adresaStanovanja* adresa, char* imeF = imeFajla);
void desifrovanje(char *imeF = imeFajla);

void cezar(zaposleni *osoba, adresaStanovanja *adresa, int odstup, char* imeF = imeFajla);
char* cezarSifrovanje(char* tekst, int odstup);
void vizner(char * sifra, char* imeF = imeFajla);
void hill(char *sifra, char* imeF = imeFajla);

void D_cezar(int odstup, char* imeF = imeFajla);
void D_vizner(char * sifra, char* imeF = imeFajla);
void D_hill(char * sifra, char* imeF = imeFajla);

void unosPodataka(zaposleni *osoba, adresaStanovanja *adresa, int n, char* imeF = imeFajla);
void prikazPodataka(zaposleni* osoba, adresaStanovanja* adresa, int brZap = brojZaposlenih, char* imeF = imeFajla);
void izmenaPodataka(zaposleni* osoba, adresaStanovanja* adresa, char* imeF = imeFajla);


int main()
{
	int i, n;
	char c;
	zaposleni* bazaZaposlenih;
	adresaStanovanja* bazaMesta;

	cout << "Unesite ime fajla gde ce se cuvati podaci: "; cin.getline(imeFajla, MAX);

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

	cin.ignore();

	bazaZaposlenih = new zaposleni[n];
	if (bazaZaposlenih == NULL) { cerr << "Greska u dodeli memorije!"; exit(1); }
	bazaMesta = new adresaStanovanja[n];
	if (bazaMesta == NULL) { cerr << "Greska u dodeli memorije!"; exit(1); }
	
	for (i = 0; i < n; i++)
	{
		bazaZaposlenih[i].idZaposlenog = 0;
	}

	proveraFajla(bazaZaposlenih, bazaMesta);
	//Pocetak unosenja podataka
	unosPodataka(bazaZaposlenih, bazaMesta, n);

	delete[] bazaZaposlenih;
	delete[] bazaMesta;
	cout << "Unos podataka je uspesno zavrsen. Da li zelite da sifrujete unete podatke (D/N): "; cin >> c;
	cin.ignore();

	switch (toupper(c))
	{
	case 'D':
		sifrovanje(bazaZaposlenih, bazaMesta, imeFajla);
	case 'N':
		cout << "Izlaz iz programa..." << endl;	exit(0);
	default:
		break;
	}
	return 0;
}

void proveraFajla(zaposleni* osoba, adresaStanovanja* adresa, char *imeF)
{
	char c;
	f.open(imeFajla, ios::in | ios::binary | ios::_Nocreate);
	if (f.is_open())
	{
		cout << "\nUPOZORENJE: Fajl vec postoji!" << endl;
		f.close();
		do
		{
			cout << "\nDa li zelite da sifrujete (S)," << endl << "desifrujete (D)," << endl << "izmenite (I) sadrzaj u koliko nije sifrovan," << endl << "ili da obrisete (O) fajl?" << endl << "Unos: ";
			cin >> c;
			cin.ignore();
		} while (toupper(c) != 'D' && toupper(c) != 'O' && toupper(c) != 'I' && toupper(c) != 'S');
		switch (toupper(c))
		{
		case 'S':
			sifrovanje(osoba, adresa);
			break;
		case 'D':
			desifrovanje();
			break;
		case 'I':
			//izmenaPodataka();
			break;
		case 'O':
			if (remove(imeFajla) != 0)
			{
				cerr << "Greska! Neuspesno brisanje fajla.";
				exit(1);
			}
			else
			{
				cout << "Fajl uspesno obrisan." << endl;
			}
		default:
			break;
		}
		exit(0);
	}
	else
	{
		cout << endl << "Fajl ne postoji." << endl;
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
void unosPodataka(zaposleni* osoba, adresaStanovanja* adresa, int n, char* imeF)
{
	int i = 0, idZap = 1, brZap = 0;
	char brZapChar[50 + sizeof(char)];
	//Upis podataka u strukturu i fajl:
	f.open(imeF, ios::out | ios::binary | ios::trunc);
	if (!f) { cerr << "Greska! Neuspesno otvaranje datoteke"; }
	f.seekp(0, ios::beg);
	do
	{
		osoba[i].idZaposlenog = idZap; //idZap se automatski inkrementira
		cout << "Unos podataka za zaposlenog ciji je ID: " << osoba[i].idZaposlenog << endl;
		cout << "Unesite ime zaposlenog: "; cin.getline(osoba[i].ime, BROJ);
		cout << "Unesite prezime zaposlenog: "; cin.getline(osoba[i].prezime, BROJ);
		cout << "Unesite broj telefona: "; cin.getline(osoba[i].tel, 13);

		f.write((char*)&osoba[i], sizeof(zaposleni));

		//Unos mesta stanovanja:
		cout << endl << "Unos adrese za zaposlenog ciji je ID: " << osoba[i].idZaposlenog << endl;
		cout << "Unesite ime ulice: "; cin.getline(adresa[i].imeUlice, MAX);
		cout << "Unesite broj objekta: "; cin.getline(adresa[i].broj, BROJ);
		cout << "Unesite grad: "; cin.getline(adresa[i].grad, BROJ);
		cout << "Unesite mesto: "; cin.getline(adresa[i].mesto, BROJ);

		f.write((char*)&adresa[i], sizeof(adresaStanovanja));
		idZap++;
		brojZaposlenih++;
		i++;
	} while (i < n);

	f.seekp(0, ios::end);
	f.write((char *)(brojZaposlenih), sizeof(brojZaposlenih));
	f.close();

	prikazPodataka(osoba, adresa);

}
void prikazPodataka(zaposleni* osoba, adresaStanovanja* adresa, int brZap, char* imeF)
{
	int i;

	f.open(imeF, ios::in || ios::binary);
	if (!f) { cerr << "Greska! Neuspesno otvaranje datoteke"; }

	f.seekg(0);

	for (i = 0; i < brojZaposlenih; i++)
	{
		f.read((char*)&osoba[i], sizeof(zaposleni));
		f.read((char*)&adresa[i], sizeof(adresaStanovanja));

		cout << "ID: " << osoba[i].idZaposlenog << endl
			<< "Ime: " << osoba[i].ime << endl
			<< "Prezime: " << osoba[i].prezime << endl
			<< "Telefon" << osoba[i].tel << endl;
		cout << "Adresa stanovanja: " << adresa[i].imeUlice << ' ' << adresa[i].broj << ' ' << adresa[i].grad << ' ' << adresa[i].mesto << endl << endl;
	}
	f.close();
}
void izmenaPodataka(zaposleni* osoba, adresaStanovanja* adresa, char* imeF)
{
	//TODO
}

/*
 * Upit za korisnika na koji način želi da šifruje podatke, ili da izbaci informacije o dostupnim vrstana šifrovanja.
 *
 * char *imeF - Ime datoteke koje se prosleđuje drugim funkcijama koje pozivaju ovu funkciju.
 */
void sifrovanje(zaposleni* osoba, adresaStanovanja* adresa, char* imeF)
{
	char unos;
	int odstup;
	char sifra[MAX];
	do
	{
		cout << endl << "Na koji nacin zelite da sifrujete fajl?" << endl
			<< "1. Cezarovo sifrovanje" << endl
			<< "2. Viznerovo sifrovanje" << endl
			<< "3. Hilovo sifrovanje" << endl
			<< "Unesite redni broj, ili '?' ako zelite da vidite primere sifrovanja: " << endl;
		cin >> unos;
		cin.ignore();

		switch (unos)
		{
		case '1':
			cout << "Unesite koliko karaktera ce biti odstup u tekstu: "; cin >> odstup;
			cin.ignore();

			cezar(osoba, adresa, odstup);
			break;
		case '2':
			cout << "Unesite sifru (Jedna rec): "; cin >> sifra;
			cin.ignore();

			vizner(sifra);
			break;
		case '3':
			cout << "Unesite sifru (Jedna rec): "; cin >> sifra;
			cin.ignore();

			//hill(sifra);
			break;
		case '?':
			info();
			break;
		default:
			break;
		}
	} while (unos != '1' && unos != '2' && unos != '3');
}

/*
 * Izbacuje primere šifrovanja u konzolu i vraća program u sifrovanje().
 * 
 * imeF - Ime fajla. Služi samo za vraćanje u funkciju sifrovanje()
 */
void info( char *imeF)
{
	cout << endl;
	cout << "Cezarovo sifrovanje" << endl
		 << "Svako slovo teksta koji se sifruje vraca se za n karaktera unazad. Primer:" << endl
		 << "\n'The quick brown fox jumps over the lazy dog', sa pomerajem od 3 bice:" << endl
		 <<   "'Wkh txlfn eurzq ira mxpsv ryhu wkh odcb grj'" << endl;

	cout << "\nViznerovo sifrovanje" << endl
		<< "Svako slovo teksta se zamenjuje za sumu odgovarajucih slova iz teksta i sifre. Primer" << endl
		<< "\n'Almost before we knew it, he had left the ground' sa sifrom 'lemon':" << endl
		<< "'Lpycfe fqtbci is xyii wg, hi toq wirh gsi sfbfrp'" << endl;

	cout << "\nHilovo sifrovanje" << endl
		<< "Svako slovo teksta i sifre se pretvara u svoju numericku vrednost i postavlja u zasebnu matricu, i zatim se matrice pomnoze. Primer" << endl
		<< "Tekst 'ACT' i sifra 'GYBNQKURP':" << endl
		<< "kljuc GYBNQKURP ce biti:\t\ttekst ACT ce biti:" << endl
		<< "\n|G Y B|   | 6 24  1|" << "    \t\t |A|   | 0|" << endl
		<<   "|N Q K| = |13 16 10|" << "    \t\t |C| = | 2|" << endl
		<<   "|U R P|   |20 17 15|" << "    \t\t |T|   |19|" << endl
		<< "\nKad se ove dve matrice pomnoze dobije se rezultujuca matrica, koja kad se pretvori nazad u tekst dobije se 'POH':" << endl
		<< "\n|15|   |P|" << endl
		<<   "|14| = |O|" << endl
		<<   "| 7|   |H|" << endl;
}


/*
 * Cezaova šifra je vrsta šifrovanja prostog teksta. Tekst se šifruje tako što se svako 
 * slovo teksta menja odgovarajućim znakom koji je pomeren za odgovarajući broj mesta u desno.
 * 
 * imeF - Ime datoteke u kojoj se nalaze podaci
 * odstup - Broj karaktera za koji se vrši odstupanje unazad u tekstu.
 */
void cezar(zaposleni *osoba, adresaStanovanja *adresa, int odstup, char* imeF)
{
	int i;
	char identifikator = '1';
	char *tempTekst;

	tempTekst = new char[MAX + 1];
	//strcpy(tempTekst, '\0');

	f.open(imeF, ios::in | ios::binary);
	if (!f) { cerr << "Greska! Neuspesno otvaranje datoteke"; }
	f.seekg(0, ios::end);
	//f.read((char *)brZap, sizeof(int));
	for (i = 0; i < brojZaposlenih; i++)
	{
		f.read((char*)&osoba[i], sizeof(zaposleni));
		f.read((char*)&adresa[i], sizeof(adresaStanovanja));

		//Pocetak sifrovanja
		cezarSifrovanje(osoba[i].ime, odstup);
		cout << "Novo ime: " << osoba[i].ime;
		cezarSifrovanje(osoba[i].prezime, odstup);
		cezarSifrovanje(osoba[i].tel, odstup);
		
		cezarSifrovanje(adresa[i].imeUlice, odstup);
		cezarSifrovanje(adresa[i].broj, odstup);
		cezarSifrovanje(adresa[i].grad, odstup);
		cezarSifrovanje(adresa[i].mesto, odstup);
	}
	f.close();

	delete[] tempTekst;
	//int duzina;
	//char *tekst;
	//
	////Otvaranje fajla u rezimu citanja, trazenje duzine ukupnog teksta i dodela memorije
	//f.open(imeF, ios::in | ios::binary);
	//if (!f) { cerr << "Greska! Neuspesno otvaranje datoteke"; }
	//f.seekg(0, ios::end);
	//duzina = int(f.tellg());

	//tekst = new char[duzina];
	//for (i = 0; i < duzina; i++)
	//{
	//	tekst[0] = '\0';
	//}

	////Vracanje na pocetak fajla i upis u bafer 'tekst'
	//f.seekg(0, ios::beg);
	//f.read(tekst, duzina);
	//f.close();

	////Sifrovanje se deli u tri klase: za velika slova, mala slova i pomoćne znakove, koji se ne menjaju.
	//for (i = 0; i < duzina; i++)
	//{
	//	//Sifrovanje velikih slova:
	//	//Formula E(x) = (x + n) mod 26. 65 i 97 se dodaju zato što se koristi ASCII format, a mod 26 znači da je formula ograničena na 26 karaktera.
	//	//Dešifrovanje se vrši na sličan način: D(x) = (x - n) mod 26.
	//	if (int(tekst[i]) < 0)
	//	{
	//		tekst[i] = ' ';
	//	}

	//	else if (isupper(tekst[i]))
	//	{
	//		tekst[i] = char(int(tekst[i] + odstup - 65) % 26 + 65); 
	//	}

	//	//Sifrovanje malih slova
	//	else if (islower(tekst[i]))
	//	{
	//		tekst[i] = char(int(tekst[i] + odstup - 97) % 26 + 97);
	//	}
	//}
	////Upis u fajl
	//f.open(imeF, ios::out | ios::binary | ios::trunc);
	//if (!f) { cerr << "Greska! Neuspesno otvaranje datoteke"; }

	//f.put(identifikator);
	//f.write(tekst, duzina);

	//f.close();

	//delete [] tekst;
}
char* cezarSifrovanje(char *tekst, int odstup)
{
	int i;
	for (i = 0; i < strlen(tekst); i++)
	{
		//sifrovanje velikih slova:
		//formula e(x) = (x + n) mod 26. 65 i 97 se dodaju zato što se koristi ascii format, a mod 26 znači da je formula ograničena na 26 karaktera.

		if (isupper(tekst[i]))
		{
			tekst[i] = char(int(tekst[i] + odstup - 65) % 26 + 65);
		}

		//sifrovanje malih slova
		else if (islower(tekst[i]))
		{
			tekst[i] = char(int(tekst[i] + odstup - 97) % 26 + 97);
		}
	}

	return tekst;
}
/*
 * Vižnerova šifra je modifikacija Cezarove šifre.
 */
void vizner(char* sifra, char* imeF)
{
	char identifikator = '2';
	//char tempchar;
	int i, j = 0, duzina;
	char* tekst, *kljuc;

	f.open(imeF, ios::in | ios::binary);
	if (!f) { cerr << "Greska! Neuspesno otvaranje datoteke" << endl; }
	f.seekg(0, ios::end);
	duzina = int(f.tellg());

	tekst = new char[duzina];
	kljuc = new char[duzina];

	f.seekg(0, ios::beg);
	f.read(tekst, duzina);

	f.close();
	//Generisanje kljuca uz pomoc sifre
	for (i = 0; i < duzina; i++)
	{
		kljuc[i] = char(sifra[j]);
		if (j == strlen(sifra) - 1)
		{
			j = -1;
		}
		j++;
	}

	for (i = 0; i < duzina; i++)
	{
		if ( int(tekst[i]) < 0 )
		{
			tekst[i] = '\0';
		}
		if (isupper(tekst[i]))
		{
			if (islower(kljuc[i]))
			{
				kljuc[i] = toupper(kljuc[i]);
			}
			tekst[i] = char(int(tekst[i] + kljuc[i] - 65) % 26 + 65);
		}
		else if (islower(tekst[i]))
		{
			if (isupper(kljuc[i]))
			{
				kljuc[i] = tolower(kljuc[i]);
			}
			tekst[i] = char(int(tekst[i] + kljuc[i] - 97) % 26 + 97);
		}
		else if (isalnum(tekst[i]))
		{
			tekst[i] = int(tekst[i] + kljuc[i] - 48) % 10 + 48;
		}
	}

	//Brisanje sadržaja fajla, upis šifrovanog sadržaja i upis identifikatora
	f.open(imeF, ios::out | ios::binary | ios::trunc);
	if (!f) { cerr << "Greska! Neuspesno otvaranje datoteke" << endl; }

	f.put(identifikator);
	f.write(tekst, duzina); 

	f.close();

	//Oslobađanje memorije
	delete[] tekst;
	delete[] kljuc;
}

/*
 * Hilovo šifrovanje je zasnovano na matricama. Slova teksta i šifre se pretvaraju u svoje redne brojeve (od 0 do 25 za alfabet), 
 * šifra se ubacuje u n* n matricu, dok se tekst ubacuje u vektorsku matricu(n * 1), gde je n broj clanova vektorske matrice. 
 * Te dve matrice se pomnože i dobije se rezultujuća matrica koja je šifrovan tekst kada se članovi ove matrice pretvore u tekst.
 *
 * imeF - Funkcija dobija ime fajla u kom se nalaze podaci. Ti podaci se šifruju i upisuju u novi fajl.
 * sifra - šifra za šifrovanje podataka.
 */
void hill(char* sifra, char* imeF)
{
	char identifikator = '3';
}

void desifrovanje(char* imeF)
{
	char id, sifra[MAX];
	int odstup;

	//Otvara fajl u rezimu za citanje i cita prvi karakter u fajlu da bi odredio vrstu sifrovanja.
	f.open(imeF, ios::in | ios::binary);
	if (!f) { cerr << "Greska! Neuspesno otvaranje datoteke" << endl; }
	f.seekg(0, ios::beg);
	f.get(id);
	f.close();

	switch (id)
	{
	case '1':
		cout << "Cezarovo sifrovanje..." << endl;
		cout << "Unesite odstup: "; cin >> odstup;
		D_cezar(odstup);

		break;
	case '2':
		cout << "Viznerovo sifrovanje..." << endl;
		cout << "Unesite sifru: "; cin >> sifra;
		D_vizner(imeF, sifra);

		break;
	case '3':
		cout << "Hilovo sifrovanje..." << endl;
		cout << "Unesite sifru: "; cin >> sifra;
		D_hill(imeF, sifra);

		break;
	default:
		cout << "Fajl nije sifrovan!" << endl;
		break;
	}
}

void D_cezar(int odstup, char* imeF)
{
	fstream f_d;

	char* tekst;
	char nF[] = "cezar_desifrovano.txt";
	int i, duzina;
	f.open(imeF, ios::in | ios::binary);
	f_d.open(nF, ios::out | ios::binary | ios::trunc);
	if (!f || !f_d) { cerr << "Greska! Neuspesno otvaranje datoteke" << endl; }

	f.seekg(0, ios::end);
	duzina = int(f.tellg());
	tekst = new char[duzina];

	for (i = 0; i < duzina; i++)
	{
		tekst[0] = '\0';
	}

	f.seekg(1, ios::beg);
	f.read(tekst, duzina - 1);
	f.close();

	//Dešifrovanje se vrši na sličan način kao šifrovanje: D(x) = (x - n) mod 26.
	for (i = 0; i < duzina; i++)
	{
		if (int(tekst[i]) < 0)
		{
			tekst[i] = '\0';
		}

		//Dešifrovanje velikih slova
		else if (isupper(tekst[i]))
		{
			tekst[i] = char(int(tekst[i] - (odstup - 26) - 65) % 26 + 65);
		}

		//Dešifrovanje malih slova
		else if (islower(tekst[i]))
		{
			tekst[i] = char(int(tekst[i] - (odstup - 26) - 97) % 26 + 97);
		}
	}

	f_d.write(tekst, duzina - 1);
	f_d.close();

	delete[] tekst;
}

void D_vizner(char* sifra, char* imeF)
{

}

void D_hill(char* sifra, char* imeF)
{

}
