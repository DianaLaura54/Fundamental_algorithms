//quicksort(with the last element as pivot) has a time complexity of o(nlgn) in the average case(when the array is
//  unsorted)
//quicksort has a time complexity of o(nlgn) in best case(the partitions sizes are equal or within 1 of each other)
// when the array is unsorted, it does slightly less comparations and attributions than the average case
// it has a o(n^2) time complexity in the worst case(when the array is ascending - if the pivot is the last element,
// it does every single comparasion and attribution- because every element before the pivot is smaller,
// then the pivot becomes the second to last and this thing happens again


//heapsort has a time complexity of o(nlgn) in every case but it is worse than quicksort in the average case
//quicksort is better than heapsort in the average case because we don't do many unnecessary swaps,but in heapsort
//we swap each element with the root at least once, we also do more comparasion because we must apply heapify 
//for every non-leaf even if the tree is balanced already


//bubblesort iterative or recursive does the same number of comparasions and attributions but the run time 
//for the recursive version is slower than the iterative one because it uses more memory


#include <iostream>
#include "Profiler.h"
#define MAX_SIZE 1000
#define STEP_SIZE 100
#define  NR_TESTS 5
using namespace std;
Profiler tema3("sorting");

int partition(int a[], int p, int r, Operation& opComp, Operation& opAttr)
{
	opAttr.count();
	int x = a[r];
	int i = p - 1;
	for (int j = p; j <= r - 1; j++)
	{
		opComp.count();
		if (a[j] <= x)
		{
			i++;
			opAttr.count(3);
			swap(a[i], a[j]);
		}
	}
	opAttr.count(3);
	swap(a[i + 1], a[r]);
	return i + 1;

}
void quicksort(int v[], int p, int r, Operation& opComp, Operation& opAttr)
{
	if (p < r)
	{
		int q = partition(v, p, r, opComp, opAttr);
		quicksort(v, p, q - 1, opComp, opAttr);
		quicksort(v, q + 1, r, opComp, opAttr);
	}
}
void QS(int v[], int n)
{
	Operation opComp = tema3.createOperation("compQS", n);
	Operation opAttr = tema3.createOperation("attrQS", n);
	quicksort(v, 0, n - 1, opComp, opAttr);
}

void median(int p, int r, int v[])
{
	int x = r - p;
	if (x <= 2)
		return;
	int m = p + x / 2;
	median(p, m, v);
	swap(v[p], v[m]);
	median(m + 1, r, v);
}
void heapify(int n, int v[], int i, Operation& opComp, Operation& opAttr)
{

	int aux = i;
	int aux2;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	opComp.count();
	if (v[l] > v[aux] && l < n) {
		aux = l;
	}
	opComp.count();
	if (v[r] > v[aux] && r < n) {
		aux = r;
	}
	if (aux != i) {
		opAttr.count(3);
		aux2 = v[i];
		v[i] = v[aux];
		v[aux] = aux2;
		heapify(n, v, aux, opComp, opAttr);
	}
}
void up(int n, int v[], Operation& opComp, Operation& opAttr)
{
	for (int i = (n / 2) - 1; i >= 0; i--) {
		heapify(n, v, i, opComp, opAttr);
	}
}
void heapsort(int n, int v[], Operation& opComp, Operation& opAttr)
{

	up(n, v, opComp, opAttr);
	for (int i = n - 1; i > 0; i--) {
		opAttr.count(3);
		int aux = v[0];
		v[0] = v[i];
		v[i] = aux;
		heapify(i, v, 0, opComp, opAttr);
	}
}
void HP(int v[], int n)
{
	Operation opComp = tema3.createOperation("compHP", n);
	Operation opAttr = tema3.createOperation("attrHP", n);
	heapsort(n, v, opComp, opAttr);
}
void bubblesort(int n, int v[])
{
	Operation opComp = tema3.createOperation("compBS", n);
	Operation opAttr = tema3.createOperation("attrBS", n);
	int ok = 0;
	for (int i = 0; i < n; i++)
	{
		ok = 0;
		for (int j = 1; j < n - i; j++)
		{
			opComp.count();

			if (v[j - 1] > v[j])
			{
				opAttr.count(3);
				int aux = v[j - 1];
				v[j - 1] = v[j];
				v[j] = aux;
				ok = 1;
			}
		}
		if (ok == 0)
			break;
	}
}
void bubblesortrec(int n, int v[], Operation& opComp, Operation& opAttr)
{

	if (n == 1)
		return;
	int  x = 0;
	for (int i = 0; i <= n - 2; i++)
	{
		opComp.count();
		if (v[i] > v[i + 1])
		{
			opAttr.count(3);
			swap(v[i], v[i + 1]);
			x++;
		}
	}
	if (x == 0)
		return;
	bubblesortrec(n - 1, v, opComp, opAttr);
}
void BSrec(int v[], int n)
{
	Operation opComp = tema3.createOperation("compBSrec", n);
	Operation opAttr = tema3.createOperation("attrBSrec", n);
	bubblesortrec(n, v, opComp, opAttr);

}
void demo()
{
	int v[] = { 7,2,8,5,9,1,6 };
	int n = sizeof(v) / sizeof(v[0]);
	QS(v, n);
	for (int i = 0; i < n; i++)
		cout << v[i] << " ";
}
void demo2()
{
	int v[] = { 10,9,8,6,8,7,5,7,8,8 };
	int n = sizeof(v) / sizeof(v[0]);

	HP(v, n);
	for (int i = 0; i < n; i++)
		cout << v[i] << " ";
}
void demo3()
{
	int v[] = { 7,2,8,5,9,1,6 };
	int n = sizeof(v) / sizeof(v[0]);
	bubblesort(n, v);
	for (int i = 0; i < n; i++)
		cout << v[i] << " ";
}
void demo4()
{
	int v[] = { 7,2,8,5,9,1,6 };
	int n = sizeof(v) / sizeof(v[0]);
	BSrec(v, n);
	for (int i = 0; i < n; i++)
		cout << v[i] << " ";
}
void perf(int order)
{
	int v[MAX_SIZE], v1[MAX_SIZE];
	int n;

	for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE)
	{

		for (int test = 0; test < NR_TESTS; test++)
		{
			FillRandomArray(v, n, 10, 10000, false, order);
			for (int i = 0; i < n; i++)
			{
				v1[i] = v[i];
			}
			if (order == UNSORTED)
			{
				QS(v, n);
				HP(v, n);
			}
			else
			{
				QS(v, n);

			}

		}
	}

	tema3.divideValues("compQS", NR_TESTS);
	tema3.divideValues("attrQS", NR_TESTS);
	tema3.addSeries("QS", "compQS", "attrQS");


	if (order == UNSORTED)
	{
		tema3.divideValues("compHP", NR_TESTS);
		tema3.divideValues("attrHP", NR_TESTS);
		tema3.addSeries("HP", "compHP", "attrHP");

		tema3.createGroup("comp", "compQS", "compHP");
		tema3.createGroup("attr", "attrQS", "attrHP");
		tema3.createGroup("total", "QS", "HP");
	}
	else
	{
		tema3.createGroup("comp", "compQS");
		tema3.createGroup("attr", "attrQS");
		tema3.createGroup("total", "QS");

	}
}
void perf2(int order)
{
	int v[MAX_SIZE];
	int n;
	for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE)
	{
		for (int test = 0; test < NR_TESTS; test++)
		{
			FillRandomArray(v, n, 10, 10000, false, order);
			median(0, n - 1, v);
			QS(v, n);
		}
	}

	tema3.divideValues("compQS", NR_TESTS);
	tema3.divideValues("attrQS", NR_TESTS);
	tema3.addSeries("QS", "compQS", "attrQS");

	tema3.createGroup("comp", "compQS");
	tema3.createGroup("attr", "attrQS");
	tema3.createGroup("total", "QS");
}
void perf3(int order)
{

	int v[MAX_SIZE], v1[MAX_SIZE];
	int n;
	for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE)
	{
		for (int test = 0; test < NR_TESTS; test++)
		{
			FillRandomArray(v, n, 10, 10000, false, order);
			for (int i = 0; i < n; i++)
			{
				v1[i] = v[i];
			}
			bubblesort(n, v);
			BSrec(v1, n);
		}
	}
	tema3.divideValues("compBS", NR_TESTS);
	tema3.divideValues("attrBS", NR_TESTS);
	tema3.addSeries("BS", "compBS", "attrBS");

	tema3.divideValues("compBSrec", NR_TESTS);
	tema3.divideValues("attrBSrec", NR_TESTS);
	tema3.addSeries("BSrec", "compBSrec", "attrBSrec");

	tema3.createGroup("comp", "compBS", "compBSrec");
	tema3.createGroup("attr", "attrBS", "attrBSrec");
	tema3.createGroup("total", "BS", "BSrec");
}
void timp(int order)
{
	int v[MAX_SIZE], v1[MAX_SIZE];
	int n;
	int TESTS = 200;
	for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE)
	{
		tema3.startTimer("BSrec", n);
		for (int test = 0; test < TESTS; test++)
		{
			FillRandomArray(v, n, 10, 10000, false, order);
			BSrec(v, n);

		}
		tema3.stopTimer("BSrec", n);
	}
	for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE)
	{
		tema3.startTimer("bubblesort", n);
		for (int test = 0; test < TESTS; test++)
		{
			FillRandomArray(v, n, 10, 10000, false, order);
			bubblesort(n, v);
		}
		tema3.stopTimer("bubblesort", n);
	}
	tema3.createGroup("run time", "bubblesort", "BSrec");
}
void perf_all()
{
	perf(UNSORTED);
	tema3.reset("WORST");
	perf(ASCENDING);
	tema3.reset("BEST");
	perf2(UNSORTED);
	tema3.reset("AVERAGE BS");
	perf3(UNSORTED);
	tema3.reset("TIMER");
	timp(UNSORTED);
	tema3.showReport();

}

int main()
{
	//demo();
	demo2();
	//demo3();
	//demo4();
	//perf_all();
}