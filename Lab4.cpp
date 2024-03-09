//merging the elements from a heap of lists requires o(nlgk) because we have k sorted lists and n elements
//  in total in them, so we apply heapify n times,for each element, heapify takes o(lgk)
// pop and push both take o(1)
//we create the heap first using the bottom up approach,after that we take the first element from the root list,which
// is the minimum,we put it in a new list,the root goes to the next element in the list,if it doesn't exist, we pop it
//  from the list and decrease the size of the heap,at the end,in any case,we apply heapify from the root to 
// arrange the elements in the heap and find the next minimum to place in our new ordered list


#include <iostream>
#include "Profiler.h"
#include <cstdlib>
#define MAX_SIZE 1000
#define STEP_SIZE 100
#define  NR_TESTS 5
using namespace std;
Profiler tema4("heap");
struct Node
{
	int  key;
	int index;
	Node* next;
};
void insertAtRear(Node*& cap, int val, int i)
{

	Node* elem = new Node;
	elem->key = val;
	elem->next = NULL;
	elem->index = i;
	if (cap == NULL)
		cap = elem;
	else
	{
		Node* nod = cap;
		while (nod->next != NULL)
			nod = nod->next;
		nod->next = elem;
	}
}

void Show(Node* cap)
{
	while (cap != NULL)
	{
		cout << cap->key << " ";
		cap = cap->next;
	}
	cout << endl;
}
void swapNodes(Node* a, Node* b, Operation& opComp, Operation& opAttr)
{
	Node temp = *a;
	*a = *b;
	*b = temp;
	opAttr.count(3);

}

void randomList(int k, int n, int arr[])
{
	for (int i = 0; i < k; i++)
	{
		arr[i] = 1;
	}
	n = n - k;
	srand(time(0));
	for (int i = 0; i < n; i++) {
		arr[rand() % k]++;
	}
}

Node* inserare(int arr[], int n, int x)
{
	Node* nod = NULL;
	for (int i = 0; i < n; i++)
		insertAtRear(nod, arr[i], x);
	return nod;
}


void klists(int n, int k, int order, Node* H[])
{
	int arr[MAX_SIZE];
	int v[MAX_SIZE];
	randomList(k, n, arr);
	for (int i = 0; i < k; i++)
	{
		FillRandomArray(v, arr[i], 10, 10000, false, order);
		H[i] = inserare(v, arr[i], i);
	}

}
void demo(int n, int k)
{
	Node* H[MAX_SIZE];

	klists(n, k, ASCENDING, H);
	srand(time(0));
	int i = rand() % k;
	int j = rand() % k;
	while (i == j)
	{
		j = rand() % k;
	}
	for (int e = 0; e < k; e++)
	{
		cout << e << " ";
		Show(H[e]);
	}

	Node* nou = NULL;
	Show(H[i]);
	Show(H[j]);

	while (H[i] != NULL && H[j] != NULL)
	{
		int x = H[i]->key;
		int y = H[j]->key;
		if (x > y)
		{
			insertAtRear(nou, y, j);
			H[j] = H[j]->next;
		}
		else if (x < y)
		{
			insertAtRear(nou, x, i);
			H[i] = H[i]->next;
		}
	}

	while (H[i] != NULL)
	{
		int x = H[i]->key;
		insertAtRear(nou, x, i);
		H[i] = H[i]->next;
	}


	while (H[j] != NULL)
	{
		int y = H[j]->key;
		insertAtRear(nou, y, j);
		H[j] = H[j]->next;
	}

	Show(nou);

}
void heapify(int n, Node* heap[], int i, Operation& opComp, Operation& opAttr)
{
	int aux = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l < n)
	{
		opComp.count();
		if (heap[l]->key < heap[aux]->key) {
			aux = l;
		}
	}
	if (r < n) {
		opComp.count();
		if (heap[r]->key < heap[aux]->key && r < n) {
			aux = r;
		}
	}

	if (aux != i) {
		swapNodes(heap[i], heap[aux], opComp, opAttr);
		heapify(n, heap, aux, opComp, opAttr);
	}
}
void up(int n, Node* H[], Operation& opComp, Operation& opAttr)
{
	for (int i = (n / 2) - 1; i >= 0; i--) {
		heapify(n, H, i, opComp, opAttr);
	}
}
void mergewithheap(int n, int k, Operation& opComp, Operation& opAttr)
{

	Node* m[MAX_SIZE];
	klists(n, k, ASCENDING, m);
	up(k, m, opComp, opAttr);

	int x = k;
	Node* nou = NULL;
	for (int j = 0; j < n; j++)
	{
		int y = m[0]->key;
		int w = m[0]->index;
		opAttr.count();
		insertAtRear(nou, y, w);
		opAttr.count();
		m[0] = m[0]->next;
		opComp.count();
		if (m[0] == NULL)
		{
			opAttr.count();
			m[0] = m[x - 1];
			x--;
		}
		heapify(x, m, 0, opComp, opAttr);
	}
}
void mergewithheap2(int n, int k, Node*& nou, Operation& opComp, Operation& opAttr)
{

	Node* m[MAX_SIZE];
	klists(n, k, ASCENDING, m);
	up(k, m, opComp, opAttr);

	int x = k;

	for (int j = 0; j < n; j++)
	{
		int y = m[0]->key;
		int w = m[0]->index;
		insertAtRear(nou, y, w);

		m[0] = m[0]->next;

		if (m[0] == NULL)
		{
			x--;
			m[0] = m[x];
		}
		heapify(x, m, 0, opComp, opAttr);
	}

}
void Show2(Node* cap)
{
	while (cap != NULL)
	{
		cout << cap->index << " " << cap->key << "  ";
		cap = cap->next;
	}
	cout << endl;
}
void demo2(int n, int k)
{
	Operation opComp = tema4.createOperation("compMerge", k);
	Operation opAttr = tema4.createOperation("attrMerge", k);
	Node* nou = NULL;
	mergewithheap2(n, k, nou, opComp, opAttr);
	Show2(nou);


}
void perf()
{
	int n, k1 = 5, k2 = 10, k3 = 100;
	for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE)
	{
		for (int test = 0; test < NR_TESTS; test++)
		{

			Operation opComp = tema4.createOperation("compMerge5", n);
			Operation opAttr = tema4.createOperation("attrMerge5", n);
			Operation opComp2 = tema4.createOperation("compMerge10", n);
			Operation opAttr2 = tema4.createOperation("attrMerge10", n);
			Operation opComp3 = tema4.createOperation("compMerge100", n);
			Operation opAttr3 = tema4.createOperation("attrMerge100", n);
			mergewithheap(n, k1, opComp, opAttr);
			mergewithheap(n, k2, opComp2, opAttr2);
			mergewithheap(n, k3, opComp3, opAttr3);

		}
	}
	tema4.divideValues("compMerge5", NR_TESTS);
	tema4.divideValues("attrMerge5", NR_TESTS);
	tema4.addSeries("Merge5", "compMerge5", "attrMerge5");

	tema4.divideValues("compMerge10", NR_TESTS);
	tema4.divideValues("attrMerge10", NR_TESTS);
	tema4.addSeries("Merge10", "compMerge10", "attrMerge10");

	tema4.divideValues("compMerge100", NR_TESTS);
	tema4.divideValues("attrMerge100", NR_TESTS);
	tema4.addSeries("Merge100", "compMerge100", "attrMerge100");

	tema4.createGroup("comp", "compMerge5", "compMerge10", "compMerge100");
	tema4.createGroup("attr", "attrMerge5", "attrMerge10", "attrMerge100");
	tema4.createGroup("total", "Merge5", "Merge10", "Merge100");
}

void perf2()
{
	int n = MAX_SIZE;
	for (int k = 10; k <= 500; k += 10)
	{
		Operation opComp = tema4.createOperation("compMerge", k);
		Operation opAttr = tema4.createOperation("attrMerge", k);
		for (int test = 0; test <= NR_TESTS; test++)
		{
			mergewithheap(n, k, opComp, opAttr);
		}
	}
	tema4.divideValues("compMerge", NR_TESTS);
	tema4.divideValues("attrMerge", NR_TESTS);
	tema4.addSeries("totalheap", "compMerge", "attrMerge");
	tema4.createGroup("total", "totalheap");


}
void perf_all()
{

	perf();
	tema4.reset();
	perf2();
	tema4.showReport();
}
int main() {

	//demo(100, 5);
	demo2(20, 4);
	//perf_all();
	return 0;




}