//Kruskal total efficiency:ElgE
//the nr of operations in Kruskal algorithm evaluating only the disjoint set operations is V+EalphaV
//where alpha approaches lg(but never becomes lg because of path compression)
//The graph is a struct containing the nr of edges,nr of nodes,an array of nodes and edges,and the 
//final weight of the graph
//Kruskal makes a set at first for every node,then sorts the edges by weight in order with quicksort,then
//for every edge I add the nodes in a new set if they don't already belong in the same set(so they won't form
//a cycle)
//I created the graphs taking every node once and adding it 4 edges(if the edge didn't exist or if I generated the 
//end of the edge the same value as the start- the value of the node I'm trying to add edges to)

#include <iostream>
#include "Profiler.h"
#include <cmath>
#define MAX_SIZE 10000
#define STEP_SIZE 100
#define  NR_TESTS 5
using namespace std;
Profiler tema9("sets");

typedef struct Node
{
	int key;
	int rank;
	struct Node* parent;
}NodeT;
typedef struct Edge
{
	int start;
	int end;
	int weight;
}EdgeT;
typedef struct Graph
{
	int nredges;
	int nrvertices;
	NodeT* V[10001];
	EdgeT* E[40004];
	int weight;
}Graph;

NodeT* Makeset(int key, Operation& opComp, Operation& opAttr) {
	opAttr.count();
	NodeT* node = (NodeT*)malloc(sizeof(NodeT));
	node->key = key;
	node->rank = 0;
	node->parent = node;
	return node;
}
void Link(NodeT* x, NodeT* y, Operation& opComp, Operation& opAttr)
{
	opComp.count();
	if (x->rank > y->rank)
	{
		opAttr.count();
		y->parent = x;
	}
	else
	{
		opAttr.count();
		x->parent = y;
	}
	opComp.count();
	if (x->rank == y->rank)
	{
		opAttr.count();
		y->rank = y->rank + 1;
	}
}
NodeT* Findset(NodeT* x, Operation& opComp, Operation& opAttr)
{
	opComp.count();
	if (x != x->parent)
	{
		opAttr.count();
		x->parent = Findset(x->parent, opComp, opAttr);
	}
	return x->parent;

}

void Union(NodeT* x, NodeT* y, Operation& opComp, Operation& opAttr)
{
	NodeT* x1 = (NodeT*)malloc(sizeof(NodeT));
	NodeT* y1 = (NodeT*)malloc(sizeof(NodeT));
	x1 = Findset(x, opComp, opAttr);
	y1 = Findset(y, opComp, opAttr);
	Link(x1, y1, opComp, opAttr);
}
void demo()
{
	Operation opComp = tema9.createOperation("compK", 11);
	Operation opAttr = tema9.createOperation("attrK", 11);
	NodeT** x = (NodeT**)malloc(11 * sizeof(NodeT*));
	for (int i = 1; i < 11; i++)
	{
		x[i] = Makeset(i, opComp, opAttr);
	}

	Union(x[1], x[2], opComp, opAttr);
	cout << "1 union 2" << endl;
	Union(x[1], x[3], opComp, opAttr);
	cout << "1 union 3" << endl;
	Union(x[1], x[4], opComp, opAttr);
	cout << "1 union 4" << endl;
	Union(x[1], x[5], opComp, opAttr);
	cout << "1 union 5" << endl;

	Union(x[6], x[8], opComp, opAttr);
	cout << "6 union 8" << endl;
	Union(x[7], x[8], opComp, opAttr);
	cout << "7 union 8" << endl;
	Union(x[8], x[9], opComp, opAttr);
	cout << "8 union 9" << endl;
	Union(x[9], x[10], opComp, opAttr);
	cout << "9 union 10" << endl;

	NodeT* t1 = Findset(x[2], opComp, opAttr);
	cout << "Parent for 2 is " << t1->key << endl;
	NodeT* t2 = Findset(x[3], opComp, opAttr);
	cout << "Parent for 3 is " << t2->key << endl;
	NodeT* t3 = Findset(x[7], opComp, opAttr);
	cout << "Parent for 7 is " << t3->key << endl;
	NodeT* t4 = Findset(x[10], opComp, opAttr);
	cout << "Parent for 10 is " << t4->key << endl;

	Union(x[3], x[10], opComp, opAttr);
	cout << "3 union 10" << endl;
	NodeT* t5 = Findset(x[3], opComp, opAttr);
	cout << "Parent for 3 is " << t5->key << endl;


}
EdgeT* init()
{
	EdgeT* edge = (EdgeT*)malloc(sizeof(EdgeT));
	edge->start = -1;
	edge->end = -1;
	edge->weight = MAX_SIZE;
	return edge;
}
EdgeT* add(int start, int end, int weight)
{
	EdgeT* edge = (EdgeT*)malloc(sizeof(EdgeT));
	edge->start = start;
	edge->end = end;
	edge->weight = weight;
	return edge;
}
int partition(Graph* G, int p, int r)
{
	int x = G->E[r]->weight;
	int i = p - 1;
	for (int j = p; j <= r - 1; j++)
	{
		if (G->E[j]->weight < x)
		{
			i++;
			swap(G->E[i], G->E[j]);
		}
	}
	swap(G->E[i + 1], G->E[r]);
	return i + 1;
}
void quicksort(Graph* G, int p, int r)
{
	if (p < r)
	{
		int q = partition(G, p, r);
		quicksort(G, p, q - 1);
		quicksort(G, q + 1, r);
	}
}
void Kruskal(Graph* G, int n, int m, Operation& opComp, Operation& opAttr, int x)
{
	for (int i = 1; i <= n; i++)
	{
		G->V[i] = Makeset(i, opComp, opAttr);
	}

	quicksort(G, 0, m);
	for (int i = 0; i <= m; i++)
	{
		int x = G->E[i]->start;
		int y = G->E[i]->end;
		if (Findset(G->V[x], opComp, opAttr) != Findset(G->V[y], opComp, opAttr))
		{
			Union(G->V[x], G->V[y], opComp, opAttr);
			G->weight = G->weight + G->E[i]->weight;
		}
	}
	if (x == 1)
		cout << G->weight << " ";
}
void initializare(Graph* G)
{
	for (int i = 0; i < G->nredges; i++)
	{
		G->E[i] = init();
	}
}
int findedge(Graph* G, int start, int end, int n)
{
	for (int i = 0; i < n; i++)
	{
		if ((G->E[i]->start == start && G->E[i]->end == end) || (G->E[i]->start == end && G->E[i]->end == start))
		{
			return 1;
		}
	}
	return 0;
}
void demo2()
{
	Graph* G = (Graph*)malloc(sizeof(Graph));
	G->nredges = 7;
	G->nrvertices = 5;
	G->weight = 0;
	initializare(G);
	G->E[4] = add(3, 4, 2);
	G->E[0] = add(1, 2, 3);
	G->E[3] = add(2, 4, 4);
	G->E[2] = add(2, 3, 5);
	G->E[1] = add(1, 3, 7);
	G->E[6] = add(4, 5, 8);
	G->E[5] = add(3, 5, 9);
	Operation opComp = tema9.createOperation("compK", G->nrvertices);
	Operation opAttr = tema9.createOperation("attrK", G->nrvertices);
	Kruskal(G, G->nrvertices, G->nredges - 1, opComp, opAttr, 1);
}

void perf()
{
	srand((unsigned)time(NULL));
	int n = MAX_SIZE;
	for (int i = STEP_SIZE; i <= MAX_SIZE; i = i + STEP_SIZE)
	{
		Operation opComp = tema9.createOperation("compK", i);
		Operation opAttr = tema9.createOperation("attrK", i);
		for (int test = 0; test < NR_TESTS; test++)
		{
			Graph* G = (Graph*)malloc(sizeof(Graph));
			G->nrvertices = i;
			G->nredges = (4 * i);
			G->weight = 0;
			initializare(G);
			int l = 0;
			for (int j = 2; j <= G->nrvertices; j++)
			{
				int weight = (rand() % 100) + 1;
				G->E[l] = add(1, j, weight);
				l++;
			}

			for (int j = 1; j <= G->nrvertices; j++)
			{
				int cont = 0;
				while (cont != 3)
				{

					int end = (rand() % (G->nrvertices)) + 1;
					int weight = (rand() % 100) + 1;

					if (findedge(G, j, end, l) == 0 && end != j)
					{
						G->E[l] = add(j, end, weight);
						l++;
						cont++;
					}
				}
			}
			Kruskal(G, G->nrvertices, G->nredges - 1, opComp, opAttr, 0);
		}
	}
	tema9.divideValues("compK", NR_TESTS);
	tema9.divideValues("attrK", NR_TESTS);
	tema9.addSeries("KRUSKAL", "compK", "attrK");
	tema9.createGroup("TOTAL", "KRUSKAL");
}
void perf_all()
{

	perf();
	tema9.showReport();
}

int main()
{
	//demo();
	//demo2();
	perf_all();

	return 0;
}