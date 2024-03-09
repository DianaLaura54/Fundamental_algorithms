//non uniform - when I generate an array of elements,they will have the tendacy to insert themself at the front
//of the table,so I am going to search the first 1500 elements I inserted,and for the non found I will generate
//an array with elements bigger than the size of the table,because they won't find a place anywhere 
//uniform - For the non found elements I do the exact same thing,but for the inserted elements,
// a frequency vector which will help me find the elements I inserted,
//I select randomly 1500 elements from those inserted and search for them

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <cstdlib>
#include "Profiler.h"
#define Nr 10008
using namespace std;

typedef struct {
	int id;
	char name[30];
} Entry;

Entry hashtable[Nr] = { 0 };
int  f(int j, int size, int i)
{
	int x = j % size + (i * i + i) % size;
	return x;
}

int insert(int size, int index, string name)
{
	int i = 0;
	do {
		int x = f(index, size, i);
		if (hashtable[x].id == 0)
		{
			strcpy_s(hashtable[x].name, name.c_str());
			hashtable[x].id = index;
			return x;
		}
		else { i++; }

	} while (i < size);
	return NULL;
}

int search(int size, int index)
{
	int i = 0;
	int e;
	do {
		e = f(index, size, i);
		if (hashtable[e].id == index)
		{
			return e;
		}
		i++;
	} while (hashtable[e].id != 0 && i != size);
	return NULL;
}
int search2(int size, int index, int& effort)
{
	int i = 0;
	int e;
	do {
		e = f(index, size, i);
		if (hashtable[e].id == index)
		{
			effort++;
			return e;
		}
		i++;
		effort++;
	} while (hashtable[e].id != 0 && i != size);
	return NULL;
}
void print(int size)
{
	for (int i = 0; i < size; i++)
	{
		if (hashtable[i].id != 0)
		{
			cout << " " << hashtable[i].name << " ";
		}
	}
	cout << endl;
}
void demo()
{
	for (int i = 0; i < 8; i++)
	{
		hashtable[i].id = 0;
	}
	int j = insert(7, 10, "Ana");
	j = insert(7, 6, "Teodora");
	j = insert(7, 3, "Ionut");
	print(7);
	j = search(7, 5);

	if (hashtable[j].id != 0)
	{
		cout << hashtable[j].name << " ";
	}
	else { cout << "not found"; }
}
void fillfactor(int x, int found[], int v[])
{
	x = (x * Nr) / 100;
	FillRandomArray(v, x, 1, Nr - 1);
	for (int i = 0; i < x; i++)
	{
		found[v[i]]++;
		int x = insert(Nr, v[i], "???");
	}
}
void nonuniform(int& F, int& NF, double& total, double& total2)
{
	int found[Nr] = { 0 };
	int notfound[1501] = { 0 };
	int v[Nr] = { 0 };
	int x = 80;
	fillfactor(x, found, v);
	int m = 3000;
	FillRandomArray(notfound, m / 2, 30000, 40000, true, UNSORTED);
	int effort = 0;
	int effort2 = 0;
	for (int i = 0; i < m / 2; i++)
	{
		effort = 0;
		effort2 = 0;
		int z = search2(Nr, v[i], effort);
		total = total + effort;
		if (effort > F)
		{
			F = effort;

		}
		int w = search2(Nr, notfound[i], effort2);
		total2 = total2 + effort2;
		if (effort2 > NF)
		{
			NF = effort2;
		}
	}
}

void uniform(int& F, int& NF, double& total, double& total2, int x)
{
	int found[Nr] = { 0 };
	int notfound[Nr] = { 0 };
	int v[Nr] = { 0 };
	fillfactor(x, found, v);
	int m = 3000;
	FillRandomArray(notfound, m / 2, 30000, 40000, true, UNSORTED);
	int count = 0;
	int f[Nr] = { 0 };
	while (count < 1500)
	{
		int y = rand() % (Nr - 1) + 1;
		if (found[y] != 0)
		{
			found[y]--;
			f[count] = y;
			count++;
		}
	}

	for (int i = 0; i < m / 2; i++)
	{
		int effort = 0;
		int effort2 = 0;
		int w = search2(Nr, f[i], effort);
		total = total + effort;
		if (effort > F)
		{
			F = effort;
		}
		int d = search2(Nr, notfound[i], effort2);
		total2 = total2 + effort2;
		if (effort2 > NF)
		{
			NF = effort2;
		}
	}
}

void demo2()
{
	int F = 0, NF = 0;
	double total = 0, total2 = 0;
	double total3 = 0, total4 = 0;
	for (int i = 0; i < 5; i++)
	{
		total = 0;
		total2 = 0;
		nonuniform(F, NF, total, total2);
		total3 = total3 + total / 1500;
		total4 = total4 + total2 / 1500;
		for (int j = 0; j < Nr; j++)
		{
			hashtable[j].id = 0;
		}
	}
	total3 = total3 / 5;
	total4 = total4 / 5;
	cout << "avg effort element found " << total3 << endl;
	cout << "avg effort element not found " << total4 << endl;
	cout << "max effort element found " << F << endl;
	cout << "max effort element not found " << NF << endl;

}
void analysis(int x)
{
	int F = 0, NF = 0;
	double total = 0, total2 = 0;
	double total3 = 0, total4 = 0;
	for (int j = 0; j < Nr; j++)
	{
		hashtable[j].id = 0;
	}
	for (int i = 0; i < 5; i++)
	{
		total = 0;
		total2 = 0;
		uniform(F, NF, total, total2, x);
		total3 = total3 + total / 1500;
		total4 = total4 + total2 / 1500;
		for (int j = 0; j < Nr; j++)
		{
			hashtable[j].id = 0;
		}
	}
	total3 = total3 / 5;
	total4 = total4 / 5;
	cout << "avg effort element found " << total3 << endl;
	cout << "avg effort element not found " << total4 << endl;
	cout << "max effort element found " << F << endl;
	cout << "max effort element not found " << NF << endl;
}

void functie()
{
	cout << "80%" << endl;
	analysis(80);
	cout << "85%" << endl;
	analysis(85);
	cout << "90%" << endl;
	analysis(90);
	cout << "95%" << endl;
	analysis(95);
	cout << "99%" << endl;
	analysis(99);
}

int main()
{
	demo();
	//demo2();
	//functie();

	return 0;
}