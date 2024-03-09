#include <iostream>
#include "Profiler.h"
#include <cmath>
using namespace std;
#define MAX_SIZE 10000
#define STEP_SIZE 100
#define  NR_TESTS 5
Profiler tema11("dfs");
typedef struct _Node {
	int key;
	int adjSize;
	struct _Node** adj;
	int color;
	int dist;
	int f;
	int index;
	boolean onstack;
	int comp;
	int lowlink;
	struct _Node* parent;
}Node;
enum {
	COLOR_WHITE = 0,
	COLOR_GRAY,
	COLOR_BLACK
};
typedef struct {
	int nrNodes;
	Node** v;
}Graph;
typedef struct _Node2
{
	Node* m;
	struct _Node2* next;
} Node2;

typedef struct
{
	Node2* head;
	Node2* tail;
	int count;
} List;
List* lista;
List* createEmptySLL()
{
	List* listPtr = (List*)malloc(sizeof(List));
	if (listPtr)
	{
		listPtr->count = 0;
		listPtr->head = listPtr->tail = NULL;
	}
	return listPtr;
}
List* insertAtFront(List* listPtr, Node* p)
{
	Node2* newNode = (Node2*)malloc(sizeof(Node2));
	newNode->m = p;
	if (listPtr)
	{
		newNode->next = listPtr->head;

		if (listPtr->count == 0)
		{
			listPtr->tail = newNode;
		}
		listPtr->head = newNode;

		listPtr->count++;

	}
	return listPtr;
}
List* insertAtRear(List* listPtr, Node* p)
{
	Node2* newNode = (Node2*)malloc(sizeof(Node2));
	newNode->m = p;

	if (listPtr)
	{
		if (listPtr->count == 0)
		{
			listPtr->head = newNode;
		}
		else

		{
			listPtr->tail->next = newNode;
		}

		listPtr->tail = newNode;
		listPtr->count++;
	}
	return listPtr;
}
List* deleteLast(List* listPtr)
{
	Node2* q1 = (Node2*)malloc(sizeof(Node2));
	Node2* q = (Node2*)malloc(sizeof(Node2));
	q1 = NULL;
	q = listPtr->head;
	if (q != NULL)
	{
		while (q != listPtr->tail)
		{
			q1 = q;
			q = q->next;
		}
		if (q == listPtr->head)
		{
			listPtr->head = listPtr->tail = NULL;
		}
		else
		{
			q1->next = NULL;
			listPtr->tail = q1;
		}
		listPtr->count--;
	}
	return listPtr;
}
int timer;
int ok = 0;
int topological = 0;
void DFS_VISIT(Graph* G, Node* s, Operation& op)
{
	op.count(3);
	timer = timer + 1;
	s->dist = timer;
	s->color = COLOR_GRAY;

	for (int i = 0; i < s->adjSize; i++)
	{
		op.count();
		if (s->adj[i]->color == COLOR_WHITE)
		{
			op.count();
			s->adj[i]->parent = s;
			DFS_VISIT(G, s->adj[i], op);
		}
		if (s->adj[i]->color == COLOR_GRAY && topological == 1)
		{
			ok = 1;
		}
	}
	op.count(3);
	s->color = COLOR_BLACK;
	lista = insertAtFront(lista, s);
	timer = timer + 1;
	s->f = timer;
}
void DFS(Graph* G, Operation& op)
{
	for (int i = 0; i < G->nrNodes; i++)
	{
		G->v[i]->color = COLOR_WHITE;
		G->v[i]->parent = NULL;
		G->v[i]->dist = 0;
		G->v[i]->f = 0;
	}
	lista = createEmptySLL();
	op.count();
	timer = 0;
	for (int i = 0; i < G->nrNodes; i++)
	{
		op.count();
		if (G->v[i]->color == COLOR_WHITE)
		{
			DFS_VISIT(G, G->v[i], op);
		}
	}
}
void adaugare(Graph G, int i, int j)
{
	G.v[i]->adj[G.v[i]->adjSize] = G.v[j];
	G.v[j]->adj[G.v[j]->adjSize] = G.v[i];
	G.v[i]->adjSize++;
	G.v[j]->adjSize++;
}
void adaugare2(Graph G, int i, int j)
{
	G.v[i]->adj[G.v[i]->adjSize] = G.v[j];
	G.v[i]->adjSize++;
}
int findedge(Graph G, int i, int j)
{
	for (int t = 0; t < G.v[i]->adjSize; t++)
	{
		if (G.v[i]->adj[t] == G.v[j])
		{
			return 1;
		}
	}
	return 0;
}
int maxim(Graph G)
{
	int x = 0;
	for (int i = 0; i < G.nrNodes; i++)
	{
		if (x < G.v[i]->dist)
			x = G.v[i]->dist;
	}
	return x;
}

void print1(int n, int parent, Graph G, int x)
{
	if (parent <= x)
	{
		for (int i = 0; i < n; i++)
		{
			if (G.v[i]->dist == parent) {
				cout << G.v[i]->key << " ";
			}
		}
		print1(n, parent + 1, G, x);
	}
}

void topologic_sort(Graph G, Operation& op)
{
	topological = 1;
	DFS(&G, op);
	if (ok == 1)
	{
		cout << "no topological sorting";
	}
	else

		while (lista->head != NULL)
		{
			cout << lista->head->m->key << " ";
			lista->head = lista->head->next;
		}

}
void demo()
{

	Graph graph;
	graph.nrNodes = 7;
	graph.v = (Node**)malloc(graph.nrNodes * sizeof(Node*));
	for (int i = 0; i < graph.nrNodes; i++) {
		graph.v[i] = (Node*)malloc(sizeof(Node));
	}
	for (int i = 0; i < graph.nrNodes; i++)
	{
		graph.v[i]->key = i;
		graph.v[i]->adjSize = 0;
		graph.v[i]->adj = (Node**)malloc(graph.nrNodes * sizeof(Node*));
		for (int j = 0; j < graph.nrNodes; j++)
		{
			graph.v[i]->adj[j] = (Node*)malloc(sizeof(Node));
		}
	}
	adaugare2(graph, 0, 1);
	adaugare2(graph, 0, 3);
	adaugare2(graph, 1, 3);
	adaugare2(graph, 2, 3);
	adaugare2(graph, 3, 4);
	adaugare2(graph, 4, 5);
	adaugare2(graph, 0, 6);
	for (int i = 0; i < graph.nrNodes; i++)
	{
		cout << graph.v[i]->key << ":";
		for (int j = 0; j < graph.v[i]->adjSize; j++)
		{
			cout << graph.v[i]->adj[j]->key << " ";
		}
		cout << endl;
	}Operation op = tema11.createOperation("OP", graph.nrNodes);
	DFS(&graph, op);
	int maxi = maxim(graph);
	print1(graph.nrNodes, 1, graph, maxi);
	cout << endl;

}

void demo2()
{
	Graph graph;
	graph.nrNodes = 7;
	graph.v = (Node**)malloc(graph.nrNodes * sizeof(Node*));
	for (int i = 0; i < graph.nrNodes; i++) {
		graph.v[i] = (Node*)malloc(sizeof(Node));
	}
	for (int i = 0; i < graph.nrNodes; i++)
	{
		graph.v[i]->key = i;
		graph.v[i]->adjSize = 0;
		graph.v[i]->adj = (Node**)malloc(graph.nrNodes * sizeof(Node*));
		for (int j = 0; j < graph.nrNodes; j++)
		{
			graph.v[i]->adj[j] = (Node*)malloc(sizeof(Node));
		}
	}
	adaugare2(graph, 0, 1);
	adaugare2(graph, 0, 3);

	adaugare2(graph, 1, 3);
	adaugare2(graph, 2, 3);
	adaugare2(graph, 3, 4);

	adaugare2(graph, 4, 5);
	adaugare2(graph, 0, 6);
	for (int i = 0; i < graph.nrNodes; i++)
	{
		cout << graph.v[i]->key << ":";
		for (int j = 0; j < graph.v[i]->adjSize; j++)
		{
			cout << graph.v[i]->adj[j]->key << " ";
		}
		cout << endl;
	}
	Operation op = tema11.createOperation("OP", graph.nrNodes);
	topologic_sort(graph, op);
	cout << endl;
}
int index;
int comp;
List* S;
int minim(int i, int j)
{
	if (i < j)
		return i;
	else return j;
}
void strong_connect(Graph G, Node* x)
{
	x->index = x->lowlink = index;
	index = index + 1;
	insertAtRear(S, x);
	x->onstack = true;

	for (int i = 0; i < x->adjSize; i++)
	{
		if (G.v[x->adj[i]->key]->index == -1)
		{
			strong_connect(G, G.v[x->adj[i]->key]);
			x->lowlink = minim(x->lowlink, G.v[x->adj[i]->key]->lowlink);
		}
		else if (G.v[x->adj[i]->key]->onstack == true)
		{

			x->lowlink = minim(x->lowlink, G.v[x->adj[i]->key]->index);
		}
	}
	if (x->lowlink == x->index)
	{
		comp++;

		Node* y = (Node*)malloc(sizeof(Node));
		do
		{

			y = S->tail->m;
			S = deleteLast(S);
			G.v[y->key]->onstack = false;
			G.v[y->key]->comp = comp;

		} while (x != G.v[y->key]);
	}

}
void print2(int n, int lowlink, Graph G)
{
	if (lowlink <= index)
	{
		int ok = 0;
		for (int i = 0; i < n; i++)
		{

			if (G.v[i]->lowlink == lowlink) {
				cout << G.v[i]->key << " ";
				ok = 1;

			}
		}
		if (ok == 1)
		{
			cout << endl;
		}
		print2(n, lowlink + 1, G);
	}

}
void Tarjan(Graph G)
{
	index = 0;
	comp = 0;
	S = createEmptySLL();
	for (int i = 0; i < G.nrNodes; i++)
	{
		G.v[i]->lowlink = -1;
		G.v[i]->index = -1;
		G.v[i]->onstack = false;
		G.v[i]->comp = 0;
	}
	for (int i = 0; i < G.nrNodes; i++)
	{
		if (G.v[i]->index == -1)
		{
			strong_connect(G, G.v[i]);
		}
	}

}
void demo3()
{
	Graph graph;
	graph.nrNodes = 8;
	graph.v = (Node**)malloc(graph.nrNodes * sizeof(Node*));
	for (int i = 0; i < graph.nrNodes; i++) {
		graph.v[i] = (Node*)malloc(sizeof(Node));
	}
	for (int i = 0; i < graph.nrNodes; i++)
	{
		graph.v[i]->key = i;
		graph.v[i]->adjSize = 0;
		graph.v[i]->adj = (Node**)malloc(graph.nrNodes * sizeof(Node*));
		for (int j = 0; j < graph.nrNodes; j++)
		{
			graph.v[i]->adj[j] = (Node*)malloc(sizeof(Node));
		}
	}
	adaugare2(graph, 0, 2);
	adaugare2(graph, 1, 0);
	adaugare2(graph, 1, 3);
	adaugare2(graph, 2, 1);
	adaugare2(graph, 2, 3);
	adaugare2(graph, 2, 4);
	adaugare2(graph, 3, 5);
	adaugare2(graph, 4, 5);
	adaugare2(graph, 4, 6);
	adaugare2(graph, 5, 3);
	adaugare2(graph, 5, 7);
	adaugare2(graph, 6, 4);
	adaugare2(graph, 6, 7);
	for (int i = 0; i < graph.nrNodes; i++)
	{
		cout << graph.v[i]->key << ":";
		for (int j = 0; j < graph.v[i]->adjSize; j++)
		{
			cout << graph.v[i]->adj[j]->key << " ";
		}
		cout << endl;
	}
	Tarjan(graph);

	print2(graph.nrNodes, 0, graph);
}

void perf()
{
	for (int n = 1000; n <= 4500; n = n + 100) {
		Operation op = tema11.createOperation("dfs-edges", n);
		Graph graph;

		graph.nrNodes = 100;
		graph.v = (Node**)malloc(graph.nrNodes * sizeof(Node*));
		for (int i = 0; i < graph.nrNodes; i++) {
			graph.v[i] = (Node*)malloc(sizeof(Node));
		}
		for (int i = 0; i < graph.nrNodes; i++)
		{
			graph.v[i]->key = i;
			graph.v[i]->adjSize = 0;
			graph.v[i]->adj = (Node**)malloc(graph.nrNodes * sizeof(Node*));
			for (int j = 0; j < graph.nrNodes; j++)
			{
				graph.v[i]->adj[j] = (Node*)malloc(sizeof(Node));
			}
		}
		int ratio = n / 100;
		for (int i = 0; i < graph.nrNodes; i++)
		{
			int arr[200];
			FillRandomArray(arr, ratio, 0, 99, true, ASCENDING);
			graph.v[i]->adjSize = ratio;
			for (int j = 0; j < ratio; j++)
			{
				graph.v[i]->adj[j] = graph.v[arr[j]];
			}

		}

		DFS(&graph, op);
	}
	tema11.createGroup("TOTAL", "dfs-edges");
}
void perf2()
{

	for (int n = 100; n <= 200; n += 10) {
		Operation op = tema11.createOperation("dfs-vertices", n);
		Graph graph;
		int m = 4500;
		graph.nrNodes = n;
		graph.v = (Node**)malloc(graph.nrNodes * sizeof(Node*));
		for (int i = 0; i < graph.nrNodes; i++) {
			graph.v[i] = (Node*)malloc(sizeof(Node));
		}
		for (int i = 0; i < graph.nrNodes; i++)
		{
			graph.v[i]->key = i;
			graph.v[i]->adjSize = 0;
			graph.v[i]->adj = (Node**)malloc(graph.nrNodes * sizeof(Node*));
			for (int j = 0; j < graph.nrNodes; j++)
			{
				graph.v[i]->adj[j] = (Node*)malloc(sizeof(Node));
			}
		}

		int ratio = m / 100;
		for (int i = 0; i < graph.nrNodes; i++)
		{
			int arr[200];
			FillRandomArray(arr, ratio, 0, 99, true, ASCENDING);
			graph.v[i]->adjSize = ratio;

			for (int j = 0; j < ratio; j++)
			{
				graph.v[i]->adj[j] = graph.v[arr[j]];
			}

		}
		DFS(&graph, op);
	}
	tema11.createGroup("TOTAL2", "dfs-vertices");
}
void perf_all()
{
	perf();
	perf2();
	tema11.showReport();
}
int main()
{
	// demo();
	  //demo2();
	//demo3();
	perf_all();
	return 0;
}