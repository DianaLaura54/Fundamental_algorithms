//in the R2 transformation every node has a key that represents the value,a link to it's children,and the number
// of children it has
// 
// the key takes the value it should have from the previous representation,then it checks if that key has a parent, 
// if the parent isn't -1 (because I don't need -1 in the representation) it adds itself to the parent it has and 
// increases the number of children for that parent
// this transformation runs in o(2n)  because it does at least n comparisons and n assignments
// it does additional assignments for when it finds that the parent isn't -1
// 
//in the R3 transformation every node has a key,a brother(that is on the right) and a child(on the left)
// 
//again,like in R2, every key takes the value it should have,then it checks if the node has any children
//if it does,it puts it in the left as a child, then it does a for from 1 to the number of children it has,
//it stores in a variable the key of the first child,then with the for it adds to the first child it's brother
//(the second son of the node from the multiway representation),x stores the key of the second child and adds
//the 3rd child of the original node as it's brother,etc..until the for ends
//this transformation runs in o(2n) because it does at least n assignments for every node and checks n times
//if the node has any children,then it does additional assignments for the child and brother
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;
#define N 100
typedef struct node1
{
	int key;
	int parent;
}NodeT1;
typedef struct node2
{
	int key;
	struct node2* children[10];
	int nr;
}NodeT2;
typedef struct node3
{
	int key;
	node3* brother;
	node3* child;
}NodeT3;
NodeT1 noduri[10];
NodeT2 noduri2[10];
NodeT3 noduri3[10];
int v[N] = { 2,7,5,2,7,7,-1,5,2 };
void parentrepresentation()
{

	for (int i = 1; i <= 9; i++)
	{
		noduri[i].key = i;
		noduri[i].parent = v[i - 1];
	}
}
void initializare()
{
	NodeT2* p = (NodeT2*)malloc(sizeof(NodeT2));
	p->key = 0;
	p->nr = 0;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			noduri2[i].children[j] = p;
		}
	}
}
void initializare2()
{

	NodeT3* p = (NodeT3*)malloc(sizeof(NodeT3));
	p->key = 0;

	for (int i = 0; i < 10; i++)
	{
		noduri3[i].child = p;
		noduri3[i].brother = p;
	}
}
void multiway()
{
	initializare();

	for (int i = 1; i <= 9; i++)
	{
		noduri2[i].key = noduri[i].key;

		if (noduri[i].parent != -1)
		{
			NodeT2* p = (NodeT2*)malloc(sizeof(NodeT2));
			p->key = i;
			noduri2[noduri[i].parent].children[noduri2[noduri[i].parent].nr] = p;
			noduri2[noduri[i].parent].nr++;
		}
	}

}
void afisare()
{

	for (int i = 1; i <= 9; i++)
	{
		cout << noduri[i].key << ":" << noduri[i].parent << endl;
	}

}
void afisare2()
{
	for (int i = 1; i <= 9; i++)
	{
		cout << noduri2[i].key << ":";
		for (int j = 0; j < noduri2[i].nr; j++)
		{
			cout << noduri2[i].children[j]->key << " ";
		}
		cout << endl;

	}
}
void print1(int n, int parent, int space)
{
	for (int i = 0; i < n; i++)
	{

		if (v[i] == parent) {
			for (int j = 0; j < space; j++)
			{
				cout << ' ';
			}
			cout << i + 1 << endl;
			cout << endl;

			print1(n, i + 1, space + 4);
		}
	}
}
void print2(NodeT2 root, int space)
{
	if (root.key == 0)
		return;
	for (int i = 0; i < space; i++)
	{
		cout << ' ';
	}
	cout << root.key << endl;
	cout << endl;
	for (int i = 0; i < root.nr; i++)
	{
		print2(noduri2[root.children[i]->key], space + 4);
	}

}
void binary()
{
	initializare2();
	for (int i = 1; i <= 9; i++)
	{
		noduri3[i].key = i;
		if (noduri2[i].nr != 0)
		{
			NodeT3* p = (NodeT3*)malloc(sizeof(NodeT3));
			p->key = noduri2[i].children[0]->key;
			noduri3[i].child = p;
			int x = noduri2[i].children[0]->key;
			for (int j = 1; j < noduri2[i].nr; j++)
			{
				NodeT3* m = (NodeT3*)malloc(sizeof(NodeT3));
				m->key = noduri2[i].children[j]->key;
				noduri3[x].brother = m;
				x = noduri2[i].children[j]->key;
			}
		}
	}
}
void afisare3()
{

	for (int i = 1; i <= 9; i++)
	{
		if (noduri3[i].brother->key != 0)
			cout << "brother of " << noduri3[i].key << " is:" << noduri3[i].brother->key << endl;
	}
	for (int i = 1; i <= 9; i++)
	{
		if (noduri3[i].child->key != 0)
			cout << "child of " << noduri3[i].key << " is:" << noduri3[i].child->key << endl;
	}


}
void print3(NodeT3 root, int space)
{
	if (root.key == 0)
		return;
	for (int i = 0; i < space; i++)
	{
		cout << ' ';
	}
	cout << root.key << endl;
	cout << endl;
	print3(noduri3[root.child->key], space + 4);
	print3(noduri3[root.brother->key], space);
}

int main()
{
	parentrepresentation();
	afisare();
	print1(9, -1, 0);
	multiway();
	afisare2();
	print2(noduri2[7], 0);
	binary();
	afisare3();
	print3(noduri3[7], 0);

}