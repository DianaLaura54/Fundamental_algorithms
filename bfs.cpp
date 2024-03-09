#include <stdlib.h>
#include <string.h>
#include <cmath>
#include "bfs.h"

int get_neighbors(const Grid* grid, Point p, Point neighb[])
{
	int v[4] = { -1,1,0,0 };
	int v2[4] = { 0,0,1,-1 };
	int e = 0;
	if (grid->mat[p.row][p.col] == 0)
	{
		for (int i = 0; i < 4; i++)
		{
			int x = p.row + v[i];
			int y = p.col + v2[i];
			if (x != MAX_ROWS + 1 && y != MAX_COLS + 1)
			{
				if (grid->mat[x][y] == 0)
				{
					neighb[e].row = x;
					neighb[e].col = y;
					e++;
				}
			}
		}
	}
	// TODO: fill the array neighb with the neighbors of the point p and return the number of neighbors
	// the point p will have at most 4 neighbors (up, down, left, right)
	// avoid the neighbors that are outside the grid limits or fall into a wall
	// note: the size of the array neighb is guaranteed to be at least 4
	return e;
}

void grid_to_graph(const Grid* grid, Graph* graph)
{
	//we need to keep the nodes in a matrix, so we can easily refer to a position in the grid
	Node* nodes[MAX_ROWS][MAX_COLS];
	int i, j, k;
	Point neighb[4];

	//compute how many nodes we have and allocate each node
	graph->nrNodes = 0;
	for (i = 0; i < grid->rows; ++i) {
		for (j = 0; j < grid->cols; ++j) {
			if (grid->mat[i][j] == 0) {
				nodes[i][j] = (Node*)malloc(sizeof(Node));
				memset(nodes[i][j], 0, sizeof(Node)); //initialize all fields with 0/NULL
				nodes[i][j]->position.row = i;
				nodes[i][j]->position.col = j;
				++graph->nrNodes;
			}
			else {
				nodes[i][j] = NULL;
			}
		}
	}
	graph->v = (Node**)malloc(graph->nrNodes * sizeof(Node*));
	k = 0;
	for (i = 0; i < grid->rows; ++i) {
		for (j = 0; j < grid->cols; ++j) {
			if (nodes[i][j] != NULL) {
				graph->v[k++] = nodes[i][j];
			}
		}
	}

	//compute the adjacency list for each node
	for (i = 0; i < graph->nrNodes; ++i) {
		graph->v[i]->adjSize = get_neighbors(grid, graph->v[i]->position, neighb);
		if (graph->v[i]->adjSize != 0) {
			graph->v[i]->adj = (Node**)malloc(graph->v[i]->adjSize * sizeof(Node*));
			k = 0;
			for (j = 0; j < graph->v[i]->adjSize; ++j) {
				if (neighb[j].row >= 0 && neighb[j].row < grid->rows &&
					neighb[j].col >= 0 && neighb[j].col < grid->cols &&
					grid->mat[neighb[j].row][neighb[j].col] == 0) {
					graph->v[i]->adj[k++] = nodes[neighb[j].row][neighb[j].col];
				}
			}
			if (k < graph->v[i]->adjSize) {
				//get_neighbors returned some invalid neighbors
				graph->v[i]->adjSize = k;
				graph->v[i]->adj = (Node**)realloc(graph->v[i]->adj, k * sizeof(Node*));
			}
		}
	}
}

void free_graph(Graph* graph)
{
	if (graph->v != NULL) {
		for (int i = 0; i < graph->nrNodes; ++i) {
			if (graph->v[i] != NULL) {
				if (graph->v[i]->adj != NULL) {
					free(graph->v[i]->adj);
					graph->v[i]->adj = NULL;
				}
				graph->v[i]->adjSize = 0;
				free(graph->v[i]);
				graph->v[i] = NULL;
			}
		}
		free(graph->v);
		graph->v = NULL;
	}
	graph->nrNodes = 0;
}
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
List* insertLast(List* list, Node* s)
{
	Node2* newNode = (Node2*)malloc(sizeof(Node2));
	newNode->m = s;
	newNode->next = NULL;
	if (list)
	{
		if (list->count == 0)
		{
			list->head = newNode;
		}
		else
		{
			list->tail->next = newNode;
		}
		list->tail = newNode;
		list->count++;
	}
	return list;
}
List* deleteFirst(List* listPtr)
{
	if (listPtr->head == NULL)
	{
		listPtr->tail = NULL;
		listPtr->count = 0;
	}
	if (listPtr->head != NULL)
	{
		listPtr->head = listPtr->head->next;
		listPtr->count--;
	}
	return listPtr;
}
void bfs(Graph* graph, Node* s, Operation* op)
{
	for (int i = 0; i < graph->nrNodes; i++)
	{
		graph->v[i]->color = COLOR_WHITE;
		graph->v[i]->dist = 0;
		graph->v[i]->parent = NULL;
		if (op != NULL)
			op->count(3);
	}
	if (op != NULL)
		op->count(3);
	s->color = COLOR_GRAY;
	s->dist = 0;
	s->parent = NULL;

	List* lista = createEmptySLL();
	lista = insertLast(lista, s);

	while (lista->head != NULL)
	{
		Node* nod = lista->head->m;
		lista = deleteFirst(lista);
		for (int i = 0; i < nod->adjSize; i++)
		{
			if (op != NULL)
				op->count();
			if (nod->adj[i]->color == 0)
			{
				nod->adj[i]->color = COLOR_GRAY;
				nod->adj[i]->dist = nod->dist + 1;
				nod->adj[i]->parent = nod;
				if (op != NULL)
					op->count(3);
				lista = insertLast(lista, nod->adj[i]);
			}
		}
		if (op != NULL)
			op->count(2);
		nod->color = COLOR_BLACK;
	}

	// TOOD: implement the BFS algorithm on the graph, starting from the node s
	// at the end of the algorithm, every node reachable from s should have the color BLACK
	// for all the visited nodes, the minimum distance from s (dist) and the parent in the BFS tree should be set
	// for counting the number of operations, the optional op parameter is received
	// since op can be NULL (when we are calling the bfs for display purposes), you should check it before counting:
	// if(op != NULL) op->count();
}

void print1(int n, int parent, int space, int p[], Point repr[])
{
	for (int i = 0; i < n; i++)
	{
		if (p[i] == parent) {

			for (int j = 0; j < space; j++)
			{
				printf(" ");
			}
			printf("(%d,%d)", repr[i].row, repr[i].col);
			printf(" \n");
			print1(n, i, space + 10, p, repr);
		}
	}
}
void print_bfs_tree(Graph* graph)
{
	//first, we will represent the BFS tree as a parent array
	int n = 0; //the number of nodes
	int* p = NULL; //the parent array
	Point* repr = NULL; //the representation for each element in p

	//some of the nodes in graph->v may not have been reached by BFS
	//p and repr will contain only the reachable nodes
	int* transf = (int*)malloc(graph->nrNodes * sizeof(int));
	for (int i = 0; i < graph->nrNodes; ++i) {
		if (graph->v[i]->color == COLOR_BLACK) {
			transf[i] = n;
			++n;
		}
		else {
			transf[i] = -1;
		}
	}
	if (n == 0) {
		//no BFS tree
		free(transf);
		return;
	}

	int err = 0;
	p = (int*)malloc(n * sizeof(int));
	repr = (Point*)malloc(n * sizeof(Node));
	for (int i = 0; i < graph->nrNodes && !err; ++i) {
		if (graph->v[i]->color == COLOR_BLACK) {
			if (transf[i] < 0 || transf[i] >= n) {
				err = 1;
			}
			else {
				repr[transf[i]] = graph->v[i]->position;
				if (graph->v[i]->parent == NULL) {
					p[transf[i]] = -1;
				}
				else {
					err = 1;
					for (int j = 0; j < graph->nrNodes; ++j) {
						if (graph->v[i]->parent == graph->v[j]) {
							if (transf[j] >= 0 && transf[j] < n) {
								p[transf[i]] = transf[j];
								err = 0;
							}
							break;
						}
					}
				}
			}
		}
	}
	free(transf);
	transf = NULL;

	if (!err) {

		print1(n, -1, 0, p, repr);


		// TODO: pretty print the BFS tree
		// the parrent array is p (p[k] is the parent for node k or -1 if k is the root)
		// when printing the node k, print repr[k] (it contains the row and column for that point)
		// you can adapt the code for transforming and printing multi-way trees from the previous labs
	}

	if (p != NULL) {
		free(p);
		p = NULL;
	}
	if (repr != NULL) {
		free(repr);
		repr = NULL;
	}
}

int shortest_path(Graph* graph, Node* start, Node* end, Node* path[])
{
	// TODO: compute the shortest path between the nodes start and end in the given graph
	// the nodes from the path, should be filled, in order, in the array path
	// the number of nodes filled in the path array should be returned
	// if end is not reachable from start, return -1
	// note: the size of the array path is guaranteed to be at least 1000
	return -1;
}

void adaugare(Graph G, int i, int j)
{
	G.v[i]->adj[G.v[i]->adjSize] = G.v[j];
	G.v[j]->adj[G.v[j]->adjSize] = G.v[i];
	G.v[i]->adjSize++;
	G.v[j]->adjSize++;
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
void performance()
{
	srand(time(0));
	int n, i;
	Profiler p("bfs");
	// vary the number of edges
	for (n = 1000; n <= 4500; n += 100) {
		Operation op = p.createOperation("bfs-edges", n);
		Graph graph;
		graph.nrNodes = 100;
		int m = n;
		//initialize the nodes of the graph
		graph.v = (Node**)malloc(graph.nrNodes * sizeof(Node*));
		for (i = 0; i < graph.nrNodes; ++i) {
			graph.v[i] = (Node*)malloc(sizeof(Node));
			memset(graph.v[i], 0, sizeof(Node));
		}
		for (int i = 0; i < graph.nrNodes; i++)
		{
			graph.v[i]->key = i;
			graph.v[i]->adj = (Node**)malloc(graph.nrNodes * sizeof(Node*));
			for (int j = 0; j < graph.nrNodes; j++)
			{
				graph.v[i]->adj[j] = (Node*)malloc(sizeof(Node));

			}
		}
		for (int i = 0; i < graph.nrNodes - 1; i++)
		{
			adaugare(graph, i, i + 1);
		}
		m = m - graph.nrNodes + 1;

		while (m != 0)
		{
			int end = (rand() % (graph.nrNodes - 1));
			int start = (rand() % (graph.nrNodes - 1));
			if (end != start && findedge(graph, start, end) == 0)
			{
				adaugare(graph, start, end);
				m--;
			}

		}

		// TODO: generate n random edges
		// make sure the generated graph is connected

		bfs(&graph, graph.v[0], &op);
		free_graph(&graph);
	}

	// vary the number of vertices
	for (n = 100; n <= 200; n += 10) {
		Operation op = p.createOperation("bfs-vertices", n);
		Graph graph;
		graph.nrNodes = n;
		int m = 4500;
		//initialize the nodes of the graph
		graph.v = (Node**)malloc(graph.nrNodes * sizeof(Node*));
		for (i = 0; i < graph.nrNodes; ++i) {
			graph.v[i] = (Node*)malloc(sizeof(Node));
			memset(graph.v[i], 0, sizeof(Node));
		}
		for (int i = 0; i < graph.nrNodes; i++)
		{
			graph.v[i]->key = i;
			graph.v[i]->adj = (Node**)malloc(graph.nrNodes * sizeof(Node*));
			for (int j = 0; j < graph.nrNodes; j++)
			{
				graph.v[i]->adj[j] = (Node*)malloc(sizeof(Node));
			}

		}
		for (int i = 0; i < graph.nrNodes - 1; i++)
		{
			adaugare(graph, i, i + 1);
		}
		m = m - graph.nrNodes + 1;

		while (m != 0)
		{
			int end = (rand() % (graph.nrNodes - 1));
			int start = (rand() % (graph.nrNodes - 1));
			if (end != start && findedge(graph, start, end) == 0)
			{
				adaugare(graph, start, end);
				m--;
			}

		}
		// TODO: generate 4500 random edges
		// make sure the generated graph is connected

		bfs(&graph, graph.v[0], &op);
		free_graph(&graph);
	}

	p.showReport();
}
