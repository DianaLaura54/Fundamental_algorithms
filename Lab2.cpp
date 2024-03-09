//both bottom up and top down have a time complexity of o(nlgn),however bottom up is more efficient overall
// top down has an advantage for cases when we don't know every element in the array already 
//bottom up has all the elements in the array and uses heapify to sort them
//top down receives the element one by one,after it receives one element it sorts it in the heap
//bottom up uses heapify to go from (n/2)-1 to 0 because n/2 nodes are leafs in a complete BT,heapify 
// searches for the largest element between the parent and it's children,if one children is bigger than the parent, 
// the elements are swapped,it remember the index of the swapped element which is now the parent and it compares it 
// with it's children
//top down receives a new element which is added in an empty array which then sorts it accordingly 
//we check if the parent of the element added exists,we compare it and if the parent is smaller we swap them,then we
//compare the element with it's new parent and swap them again if needed until the element is sorted
//for the worst case,if the heap is sorted ascendingly at first it would take the most comparasions and attributions in both cases
//to sort it 
#include <iostream>
#include "Profiler.h"

#define MAX_SIZE 10000
#define STEP_SIZE 100
#define  NR_TESTS 5
using namespace std;
Profiler tema2("heap");

void heapify(int n, int v[], int i, Operation* opComp, Operation* opAttr)
{

	int aux = i;
	int aux2;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	opComp->count();
	if (v[l] > v[aux] && l < n) {
		aux = l;
	}
	opComp->count();
	if (v[r] > v[aux] && r < n) {
		aux = r;
	}
	if (aux != i) {
		opAttr->count(3);
		aux2 = v[i];
		v[i] = v[aux];
		v[aux] = aux2;
		heapify(n, v, aux, opComp, opAttr);
	}
}
void heapifysort(int n, int v[], int i)
{

	int aux = i;
	int aux2;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	if (v[l] > v[aux] && l < n) {
		aux = l;
	}
	if (v[r] > v[aux] && r < n) {
		aux = r;
	}
	if (aux != i) {
		aux2 = v[i];
		v[i] = v[aux];
		v[aux] = aux2;
		heapifysort(n, v, aux);
	}
}
void up(int n, int v[])
{

	Operation opComp = tema2.createOperation("compBP", n);
	Operation opAttr = tema2.createOperation("attrBP", n);
	for (int i = (n / 2) - 1; i >= 0; i--) {
		heapify(n, v, i, &opComp, &opAttr);
	}

}
void heapsort(int n, int v[])
{
	up(n, v);
	for (int i = n - 1; i > 0; i--) {
		int aux = v[0];
		v[0] = v[i];
		v[i] = aux;
		heapifysort(i, v, 0);
	}
}
void exchange(int n, int v[], int j, Operation* opComp, Operation* opAttr)
{
	int p = (j - 1) / 2;
	int aux;
	opComp->count();
	if (p >= 0) {
		opComp->count();
		if (v[j] > v[p]) {
			opAttr->count(3);
			aux = v[j];
			v[j] = v[p];
			v[p] = aux;
			exchange(n, v, p, opComp, opAttr);
		}

	}
}


void down(int n, int v[], int v1[])
{
	Operation opComp = tema2.createOperation("compTD", n);
	Operation opAttr = tema2.createOperation("attrTD", n);
	for (int i = 0; i < n; i++) {
		v1[i] = v[i];
		exchange(i + 1, v1, i, &opComp, &opAttr);
	}
}
void demo2()
{
	int v[] = { 7,10,9,8,4,20 };
	int n = sizeof(v) / sizeof(v[0]);
	heapsort(n, v);
	for (int i = 0; i < n; i++)
		cout << v[i] << " ";

}
void demo()
{
	int v[] = { 7,10,9,8,4,20 };
	int n = sizeof(v) / sizeof(v[0]);
	up(n, v);
	for (int i = 0; i < n; i++)
		cout << v[i] << " ";
}
void demo3()
{
	int v[] = { 7,10,9,8,4,20 };
	int n = sizeof(v) / sizeof(v[0]);
	int v1[20] = { 0 };
	down(n, v, v1);
	for (int i = 0; i < n; i++)
		cout << v1[i] << " ";
}
void perf(int order)
{
	int v[MAX_SIZE];
	int n;
	for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE)
	{
		for (int test = 0; test < NR_TESTS; test++)
		{
			FillRandomArray(v, n, 10, 10000, false, order);
			int v1[MAX_SIZE] = { 0 };
			down(n, v, v1);
			up(n, v);
		}
	}
	tema2.divideValues("compBP", NR_TESTS);
	tema2.divideValues("attrBP", NR_TESTS);
	tema2.addSeries("BP", "compBP", "attrBP");
	tema2.divideValues("compTD", NR_TESTS);
	tema2.divideValues("attrTD", NR_TESTS);
	tema2.addSeries("TD", "compTD", "attrTD");
	tema2.createGroup("comp", "compBP", "compTD");
	tema2.createGroup("attr", "attrBP", "attrTD");
	tema2.createGroup("total", "BP", "TD");
}
void perf_all()
{
	perf(UNSORTED);
	tema2.reset("worst");
	perf(ASCENDING);
	tema2.showReport();
}
int main()
{
	//demo();
	//cout << endl;
	//demo2();
	//cout << endl;
	//demo3();
	perf_all();

}