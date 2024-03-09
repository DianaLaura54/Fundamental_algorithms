//average - unsorted arrays 
//bubble sort has a o(n^2) time complexity in this selection
//insertion sort has a o(n^2) time complexity in this selection
//selection sort has a o(n^2) time complexity in this selection
//all have a similiar time complexity,but overall bubble sort is the most non-efficient choice because it makes the most attributions
//and uses 2 fors that start from 0 and 1



//best - ascending sorted arrays
//bubble sort has a o(n) time complexity in this selection
//insertion sort has a o(n) time complexity in this selection
//selection sort has a o(n^2) time complexity in this selection
//bubblesort and insertion sort are the best choices here because selection sort does far more comparisons

//worst - descending sorted arrays
//bubble sort has a o(n^2) time complexity in this selection
//insertion sort has a o(n^2) time complexity in this selection
//selection sort has a o(n^2) time complexity in this selection
//in this case selection sort is the fastest because it does the least attributions,it swaps the first element with last,the second
//with the second to last,etc,the array is ascending sorted after it reaches half the size of the array

#include <iostream>
#include "Profiler.h"

#define MAX_SIZE 1000
#define STEP_SIZE 100
#define  NR_TESTS 5
using namespace std;
Profiler tema1("selection1");
void bubblesort(int n,  int v[])
{
	Operation opComp = tema1.createOperation("bubblesort-compSort", n);
	Operation opAttr = tema1.createOperation("bubblesort-attrSort", n);
	int ok = 0;
	for (int i = 0; i < n; i++)
	{
		ok = 0;
		for (int j = 1; j < n -i; j++)
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
void insertionsort(int n,  int v[])
{
	Operation opComp = tema1.createOperation("insertionsort-compSort", n);
	Operation opAttr = tema1.createOperation("insertionsort-attrSort", n);
	int x;
	for (int i = 1; i < n; i++)
	{
		
		opAttr.count();
		x = v[i];
		int j = i - 1;
		opComp.count();
		while (v[j] > x && j>=0) 
		{
			opComp.count();
			opAttr.count();
				v[j + 1] = v[j];
	
				j = j - 1;	
		}	
		opAttr.count();
		v[j + 1] = x;
	}

}
void selectionsort(int n,int v[])
{
	Operation opComp = tema1.createOperation("selectionsort-compSort", n);
	Operation opAttr = tema1.createOperation("selectionsort-attrSort", n);
	for (int i = 0; i<n ; i++)
	{
		int max_i = i;
		for (int j = i + 1; j < n; j++)
		{
			opComp.count();
			if (v[j] < v[max_i])
			{
				max_i = j;
			}
		}
		if (max_i != i)
		{
			opAttr.count(3);
			
			int aux = v[i];
			v[i] = v[max_i];
			v[max_i] = aux;
			
		}
}
}
void demo()
{

	int v[] = { 7,2,8,5,9,1,6 };
	int n = sizeof(v) / sizeof(v[0]);

	bubblesort(n, v);
	for (int i = 0; i < n; i++)
		cout << v[i] << " ";
}
void demo2()
{
	int v[] = { 7,2,8,5,9,1,6 };
	int n = sizeof(v) / sizeof(v[0]);

	insertionsort(n, v);
	for (int i = 0; i < n; i++)
		cout << v[i] << " ";
}
void demo3()
{
	int v[] = { 7,2,8,5,9,1,6 };
	int n = sizeof(v) / sizeof(v[0]);

	selectionsort(n, v);
	for (int i = 0; i < n; i++)
		cout << v[i] << " ";

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
			
			insertionsort(n, v);
		}
	}
	

	tema1.divideValues("insertionsort-attrSort", NR_TESTS);
	tema1.divideValues("insertionsort-compSort", NR_TESTS);
	tema1.addSeries("IS", "insertionsort-attrSort", "insertionsort-compSort");

	tema1.createGroup("attr", "insertionsort-attrSort");
	tema1.createGroup("comp", "insertionsort-compSort");

	tema1.createGroup("total", "IS");

}
void perf_all2()
{
	perf2(UNSORTED);
	tema1.reset("best");
	perf2(ASCENDING);
	tema1.reset("worst");
	perf2(DESCENDING);
	tema1.showReport();
}
void perf(int order)
{
	int v[MAX_SIZE];
	int v1[MAX_SIZE], v2[MAX_SIZE];
	int n;

	for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE)
	{
		for (int test = 0; test < NR_TESTS; test++)
		{
			FillRandomArray(v, n, 10, 10000, false, order);
			
for(int j=0;j<n;j++)
{
	v1[j] = v[j];
	v2[j] = v[j];
}            bubblesort(n, v1);
insertionsort(n, v);
			selectionsort(n, v2);
	
			
			
		}
	}
	tema1.divideValues("bubblesort-attrSort", NR_TESTS);
	tema1.divideValues("bubblesort-compSort", NR_TESTS);
	tema1.addSeries("BS", "bubblesort-attrSort", "bubblesort-compSort");

	tema1.divideValues("insertionsort-attrSort", NR_TESTS);
	tema1.divideValues("insertionsort-compSort", NR_TESTS);
	tema1.addSeries("IS", "insertionsort-attrSort", "insertionsort-compSort");

	tema1.divideValues("selectionsort-attrSort", NR_TESTS);
	tema1.divideValues("selectionsort-compSort", NR_TESTS);
tema1.addSeries("SS", "selectionsort-attrSort", "selectionsort-compSort");

	tema1.createGroup("attr", "bubblesort-attrSort", "insertionsort-attrSort", "selectionsort-attrSort");
	tema1.createGroup("comp", "bubblesort-compSort", "insertionsort-compSort", "selectionsort-compSort");
	
	tema1.createGroup("total", "BS","IS","SS");

}
void perf_all()
{
	perf(UNSORTED);
	tema1.reset("best");
	perf(ASCENDING);
	tema1.reset("worst");
	perf(DESCENDING);
	tema1.showReport();
}
int main()
{
	
	//demo();
	//demo2();
   //demo3();
	//perf_all2();
	perf_all();

	



}