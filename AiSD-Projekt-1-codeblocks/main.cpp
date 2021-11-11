// Projekt na "Algorytmy i Struktury Danych"
// 166642 Stefan Domaradzki
// Temat: Dla zadanej tablicy liczb ca³kowitych o rozmiarze n zawieraj¹cej wartoœæi z przedzia³u [1,n]
//		  znajdŸ element powtarzaj¹cy siê.

#include <iostream>
#include <time.h>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <chrono>

using namespace std;

void wypelnij(int tab[], int rozmiar);
void wypisz(int tab[], int rozmiar, double czas, string algorytm);


void brute_force(int tab[], int rozmiar);
void counting(int tab[], int rozmiar);
void counting2(int tab[], int rozmiar);

int main(){

	int rozmiar;
	int *tablica;
	clock_t start, stop;
	double czas;

	//cout << "Podaj rozmiar tablicy: "; cin >> rozmiar;



	rozmiar = 10;

	for (int i = 1; i < 8; i++)
	{
		rozmiar = 10 * rozmiar;
		tablica = new int [rozmiar];
		wypelnij(tablica, rozmiar);

		start = clock();

		brute_force(tablica, rozmiar);

		stop = clock();
		czas = ((stop - start)*1000) / (CLOCKS_PER_SEC);

		wypisz(tablica, rozmiar, czas, "brute");
	}

	cout << endl << "Algorytm zaj¹³: " << czas;
    cout << "ms. Przy rozmiarze tablicy: " << rozmiar << "." << endl;


	system("Pause");
	return 0;



}

void wypelnij(int tab[], int rozmiar)
{
	srand(time(NULL));
	for (int i = 0; i < rozmiar; i++)
	{
		tab[i] = rand()% rozmiar;
		if (tab[i] == 0) {
			while (true)
			{
				tab[i] = rand() % rozmiar;
				if (tab[i]) break;
			}
		}

	}
}

void wypisz(int tab[], int rozmiar, double czas, string algorytm)
{
	/*for (int i = 0; i < rozmiar; i++)
	{
		cout << tab[i] << setw(5);
		if (i % 30 == 0) cout << endl;
	}*/

	ofstream dane;
	dane.open("dane.txt", ios::app);
	dane << algorytm << ", " << rozmiar << "," << czas << endl;
	//txt bêdzie w formacie csv ³atwy w konwersji do excel do wykresów.
	dane.close();
}

void brute_force(int tab[], int rozmiar)
{
	int szukaj;
	int porownaj;

	int powtarzajaca;

	bool flaga=false;

	for (int i = 0; i < rozmiar; i++)
	{
		szukaj = tab[i];
		porownaj = 0;

		for (int j = 0; j < rozmiar; j++)
		{
			if (tab[j] == szukaj) porownaj++;

			if (porownaj == 2)
			{
				//cout << "liczba która sie powtarza to: " << szukaj << ". \n";
				flaga = true;
				powtarzajaca = szukaj;
				break;
			}

		}


	}
		if (!flaga) cout << "\n Nie znaleziono liczby powtarzaj¹cej sie. \n";
		else cout << "\n Powtarza sie: " << powtarzajaca << ". \n";
}

void counting_sort(int tab[], int rozmiar)
{
	//z za³o¿enia ¿e liczby s¹ z przedzia³u 1 do n (rozmiar)
	//tablica wymagana do sortowania kube³kowego powinna byæ rozmiaru n
	//pozycja zerowa nowej tablicy zawsze pozostanie pusta i bêdzie ignorowana

	int powtarzajaca;

	int* buckets = new int[rozmiar];

	for(int i = 0; i < rozmiar; i++)
	{
		buckets[i] = 0;
	}



	bool flaga = false;

	for(int i = 0; i < rozmiar; i++)
	{
		buckets[tab[i]]++;

		if (buckets[tab[i]] == 2)
		{
			flaga = true;
			powtarzajaca = tab[i];
			break;
		}

	}

	if (!flaga) cout << "\n Nie znaleziono liczby powtarzajacej sie. \n";
	else cout << "\n Powtarza sie: " << powtarzajaca << ". \n";

}

void counting2(int tab[], int rozmiar)
{
	int* buckets = new int[rozmiar];

	for (int i = 0; i < rozmiar; i++)
	{
		//cout << "ok ";
		buckets[i] = 0;
	}

	int porownaj=0;
	int poz = 0;


	bool flaga = false;

	cout << "ok\n";

	for (int i = 0; i < rozmiar; i++)
	{
		poz = tab[i];
		buckets[poz]++;
	}

	//cout << "najwieksza\n";
	for (int i = 0; i < rozmiar; i++)
	{
		if (buckets[i] >= 2)
		{
			flaga = true;

			//cout << "Liczba " << i << " wystapila: " << buckets[i] << " razy. \n";

			if (buckets[i] > buckets[porownaj])
				porownaj = i;
		}

	}

	cout << "\n \n Najwiecej razy wystapila liczba: ";
	cout << porownaj << ": " << buckets[porownaj] << " razy. \n \n";

	if (flaga == false) cout << "\n Nie znaleziono liczby powtarzajacej sie. \n";
}
