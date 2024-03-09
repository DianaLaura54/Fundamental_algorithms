//in the recursive version I simply print the key,then go to the left and then to the right
//in the iterative version I have 3 directions I go through
//I print the key,then I go to the left,to the left of the left I print the key each time because 
//I am in the first direction...if I can't, I go to the right,I print the key,then I go to the
//left of the right,if I can't I go to the right of the right
//if I have reached a leaf I try to go back to the parent,if the leaf is the left of the parent
// I go and print the right subtree,if the leaf was on the right,I go to the parent of the parent
//and the process happens again if there are keys that weren't printed
//the algorithm stops when I reached the parent and already processed the right subtree

//hybrid is better because insertion sort is better on smaller arrays than quicksort 
//the optimal threshold I found is usually between 9-12 for the size of the arrays
//in the graph quicksort is almost a straight line because I apply it for n=10000 and it
//will always be O(nlgn) 
//insertion sort has a efficiency of O(n^2),which is far worse for big numbers, but it
//it works better for smaller sized arrays



#include <iostream>
#include "Profiler.h"
#define MAX_SIZE 10000
#define STEP_SIZE 1000
#define  NR_TESTS 200
using namespace std;
Profiler tema8("tree");

typedef struct node
{
	int key;
	struct node* left;
	struct node* right;
	struct node* parent;

} NodeT;

NodeT* init(int key, NodeT* parent) {

	NodeT* node = (NodeT*)malloc(sizeof(NodeT));
	node->key = key;
	node->left = nullptr;
	node->right = nullptr;
	node->parent = parent;
	return node;
}
NodeT* create(int i, int j, NodeT* parent)
{
	if (i <= j)
	{
		NodeT* root = nullptr;
		if ((i + j) % 2 == 0)
		{
			root = init((i + j + 1) / 2, parent);
		}
		else
		{
			root = init((i + j) / 2, parent);
		}
		root->left = create(i, root->key - 1, root);
		root->right = create(root->key + 1, j, root);
		return root;
	}
	else return nullptr;

}
void preorder(NodeT* p, Operation& opAttr, int x)
{
	if (p != NULL)
	{
		opAttr.count();
		if (x == 1)
		{
			cout << p->key << " ";
		}
		preorder(p->left, opAttr, x);
		preorder(p->right, opAttr, x);
	}
}

void iterative(NodeT* p, Operation& opAttr, int x)
{
	NodeT* root = p;
	int d = 1;
	do
	{
		if (d == 1)
		{
			opAttr.count();
			if (x == 1)
			{
				cout << root->key << " ";
			}
			if (root->left != nullptr)
			{
				root = root->left;

			}
			else d = 2;
		}
		if (d == 2)
		{
			if (root->right != nullptr)
			{
				root = root->right;
				d = 1;
			}
			else d = 3;
		}
		if (d == 3)
		{
			if (root->parent != nullptr)
			{
				if (root == root->parent->left)
				{
					d = 2;
				}
				root = root->parent;
			}
		}
	} while (d != 3 || p != root);
}
void print(NodeT* root, int space)
{
	if (root == nullptr)
		return;
	print(root->right, space + 10);
	cout << endl;
	for (int i = 0; i < space; i++)
	{
		cout << " ";
	}
	cout << root->key;
	cout << endl;
	print(root->left, space + 10);
}
void demo()
{
	NodeT* root = (NodeT*)malloc(sizeof(NodeT));
	Operation opAttr = tema8.createOperation("assign", 10);
	NodeT* parent = (NodeT*)malloc(sizeof(NodeT));
	parent->key = 0;
	root = create(1, 10, parent);
	print(root, 0);
	cout << endl;
	preorder(root, opAttr, 1);
	cout << endl;
	iterative(root, opAttr, 1);
}
void insertionsort(int u, int n, int v[], Operation& opComp, Operation& opAttr)
{
	for (int i = u + 1; i < n + 1; i++)
	{
		opAttr.count();
		int x = v[i];
		int j = i;
		opComp.count();
		while (j >= u && v[j - 1] > x)
		{
			opAttr.count();
			opComp.count();
			v[j] = v[j - 1];
			j = j - 1;
		}
		opAttr.count();
		v[j] = x;
	}
}

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
void hybrid(int v[], int p, int r, Operation& opComp, Operation& opAttr, int x)
{
	if (p < r)
	{
		if (r - p < x)
		{
			insertionsort(p, r, v, opComp, opAttr);
		}
		else
		{
			int q = partition(v, p, r, opComp, opAttr);
			hybrid(v, p, q - 1, opComp, opAttr, x);
			hybrid(v, q + 1, r, opComp, opAttr, x);
		}
	}
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

void demo2()
{
	int v[20] = { 1,2,3,7,6,5,8,4,10,9,11,12,13,14,15,16,17,19,18,20 };
	int n = 20;
	int v1[20];
	for (int i = 0; i < 20; i++)
	{
		v1[i] = v[i];
	}
	Operation opComp = tema8.createOperation("comp", 9);
	Operation opAttr = tema8.createOperation("attr", 9);
	Operation opComp2 = tema8.createOperation("comp2", 9);
	Operation opAttr2 = tema8.createOperation("attr2", 9);
	quicksort(v, 0, 19, opComp, opAttr);
	hybrid(v1, 0, 19, opComp2, opAttr2, 10);
	for (int i = 0; i < 20; i++)
		cout << v[i] << " ";
	cout << endl;
	for (int i = 0; i < 20; i++)
		cout << v1[i] << " ";

}
void perf()
{
	int n;
	for (n = 100; n <= MAX_SIZE; n += 100)
	{
		Operation opAttr = tema8.createOperation("assign", n);
		Operation opAttr2 = tema8.createOperation("assign2", n);
		NodeT* root = (NodeT*)malloc(sizeof(NodeT));
		NodeT* parent = (NodeT*)malloc(sizeof(NodeT));
		parent->key = 0;
		root = create(1, n, parent);
		preorder(root, opAttr, 0);
		iterative(root, opAttr2, 0);
	}
	tema8.addSeries("total", "assign", "assign2");
	tema8.createGroup("TOTAL", "total");
}
void perf2(int order)
{

	int v[MAX_SIZE], v1[MAX_SIZE];
	int n = MAX_SIZE;
	for (int j = 1; j <= 50; j = j + 1)
	{
		Operation opComp = tema8.createOperation("compQ", j);
		Operation opAttr = tema8.createOperation("attrQ", j);

		Operation opComp2 = tema8.createOperation("compH", j);
		Operation opAttr2 = tema8.createOperation("attrH", j);
		for (int test = 0; test < NR_TESTS; test++)
		{
			FillRandomArray(v, n, 10, 10000, false, order);

			for (int i = 0; i < n; i++)
			{
				v1[i] = v[i];
			}
			quicksort(v, 0, n - 1, opComp, opAttr);
			hybrid(v1, 0, n - 1, opComp2, opAttr2, j);

		}
	}
	tema8.divideValues("compH", NR_TESTS);
	tema8.divideValues("attrH", NR_TESTS);
	tema8.addSeries("HYBRID", "compH", "attrH");

	tema8.divideValues("compQ", NR_TESTS);
	tema8.divideValues("attrQ", NR_TESTS);
	tema8.addSeries("QS", "compQ", "attrQ");

	tema8.createGroup("comp", "compH", "compQ");
	tema8.createGroup("attr", "attrH", "attrQ");
	tema8.createGroup("total", "HYBRID", "QS");
}
void timp(int order)
{
	int v[MAX_SIZE];
	int v1[MAX_SIZE];
	int n = MAX_SIZE;
	int TESTS = 100;
	for (int i = 0; i <= 1000; i = i + 10)
	{
		tema8.startTimer("quicksort", i);
		for (int test = 0; test < TESTS; test++)
		{
			Operation opComp = tema8.createOperation("compQ", i);
			Operation opAttr = tema8.createOperation("attrQ", i);
			FillRandomArray(v, n, 10, 10000, false, order);
			quicksort(v, 0, n - 1, opComp, opAttr);
		}
		tema8.stopTimer("quicksort", i);
	}
	for (int i = 0; i <= 1000; i = i + 10)
	{
		tema8.startTimer("hybrid", i);
		for (int test = 0; test < TESTS; test++)
		{
			Operation opComp2 = tema8.createOperation("compH", i);
			Operation opAttr2 = tema8.createOperation("attrH", i);
			FillRandomArray(v1, n, 10, 10000, false, order);
			hybrid(v1, 0, n - 1, opComp2, opAttr2, i);
		}
		tema8.stopTimer("hybrid", i);
	}
	tema8.createGroup("run time", "quicksort", "hybrid");
}

void perf_all()
{
	//perf();
	//tema8.reset("hybrid quicksort vs quicksort");
	//perf2(UNSORTED);
	tema8.reset("time run");
	timp(UNSORTED);
	tema8.showReport();
}
int main()
{
	//demo();
	demo2();
	//perf_all();


	return 0;
}