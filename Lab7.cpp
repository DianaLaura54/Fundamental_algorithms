//Vaida Diana
//group 3 
//build tree:O(n)
//os_selection:O(lgn)
//os_delete:O(h)
//in the build tree I initialize every node with the value it should have,and then with a divide and
//impera method I also initialize the right and left node of the current node,the size index is assigned
//for every node after it reaches the 'last' recursive call,it is postponed,once it reaches a leaf,the leaf
//will have the size 1 and the respective sizes for each node will be calculated
//it takes approximately O(n) because every node needs to be initialized and additional comparasions 
//and assignments will be made for the size field

//os_selection takes O(lgn) because it goes through the branch to find the element assigned to that 
//position using the size field

//delete takes O(lgn), lgn being the height of the tree,it has 3 cases, when the element I'm trying
//to find is bigger than the node,case when I go to the right, if the key is smaller I go to the left
//and I have the case when I find the key, I also have 4 additional cases - when it has no child,a child to
//the left or the right,or it has two, to update the size I simply substract 1,since it goes down a branch
//on the right or the left the other one down to the root isn't affected 


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <cstdlib>
#include "Profiler.h"

#define MAX_SIZE 1000
#define STEP_SIZE 100
#define  NR_TESTS 5
using namespace std;
Profiler tema7("tree");
typedef struct node
{
	int key;
	struct node* left;
	struct node* right;

	int size;
}NodeT;
NodeT* init(int key) {

	NodeT* node = (NodeT*)malloc(sizeof(NodeT));
	node->key = key;
	node->size = 1;
	node->left = nullptr;
	node->right = nullptr;
	return node;
}

NodeT* create(int i, int j, Operation& opComp, Operation& opAttr)
{

	if (i <= j)
	{
		opAttr.count();
		NodeT* root = nullptr;
		if ((i + j) % 2 == 0)
		{
			root = init((i + j + 1) / 2);
		}
		else
		{
			root = init((i + j) / 2);
		}
		root->left = create(i, root->key - 1, opComp, opAttr);
		root->right = create(root->key + 1, j, opComp, opAttr);

		opComp.count();
		if (root->left != nullptr)
		{
			opAttr.count();
			root->size = root->left->size + root->size;
		}
		opComp.count();
		if (root->right != nullptr)
		{
			opAttr.count();
			root->size = root->right->size + root->size;
		}

		return root;
	}
	else return nullptr;

}
void print3(NodeT* root, int space)
{
	if (root == nullptr)
		return;
	print3(root->right, space + 10);
	cout << endl;
	for (int i = 0; i < space; i++)
	{
		cout << " ";
	}
	cout << root->key;
	cout << endl;
	print3(root->left, space + 10);
}

NodeT* os_select(NodeT* x, int i, Operation& opComp, Operation& opAttr)
{
	int r;
	opComp.count();
	if (x == nullptr)
		return nullptr;
	opComp.count();
	if (x->left != nullptr)
	{
		opAttr.count();
		r = x->left->size + 1;
	}
	else
	{
		r = 1;
	}
	if (i == r)
		return x;
	else if (i < r)
		return os_select(x->left, i, opComp, opAttr);
	else return os_select(x->right, i - r, opComp, opAttr);
}

NodeT* minim(NodeT* min, Operation& opComp, Operation& opAttr)
{
	opAttr.count();
	NodeT* nod = min;
	opComp.count();
	while (nod->left != nullptr)
	{
		opComp.count();
		nod = nod->left;
	}
	return nod;
}
NodeT* deleted(NodeT* root, int key, Operation& opComp, Operation& opAttr)
{
	opComp.count();
	if (root == nullptr)
	{
		return root;
	}
	opComp.count();
	if (key > root->key)
	{
		root->right = deleted(root->right, key, opComp, opAttr);
	}
	opComp.count();
	if (key < root->key)
	{
		root->left = deleted(root->left, key, opComp, opAttr);
	}
	opComp.count();
	if (root->key == key)
	{
		opComp.count(2);
		if (root->left == nullptr && root->right == nullptr)
		{
			return nullptr;
		}
		opComp.count();
		if (root->left == nullptr) {
			opAttr.count();
			NodeT* temp = root->right;
			free(root);
			return temp;
		}
		opComp.count();
		if (root->right == nullptr) {
			opAttr.count();
			NodeT* temp = root->left;
			free(root);
			return temp;
		}
		opComp.count(2);
		if (root->left && root->right) {
			opAttr.count(2);
			NodeT* temp = minim(root->right, opComp, opAttr);
			root->key = temp->key;
			root->right = deleted(root->right, temp->key, opComp, opAttr);
		}
	}
	opAttr.count();
	root->size = root->size - 1;
	return root;
}

void demo()
{
	Operation opComp = tema7.createOperation("compS", 11);
	Operation opAttr = tema7.createOperation("attrS", 11);
	Operation opComp2 = tema7.createOperation("compD", 11);
	Operation opAttr2 = tema7.createOperation("attrD", 11);
	Operation opComp3 = tema7.createOperation("compB", 11);
	Operation opAttr3 = tema7.createOperation("attrB", 11);
	NodeT* root = (NodeT*)malloc(sizeof(NodeT));
	root = create(1, 11, opComp3, opAttr3);
	print3(root, 0);
	int size = 11;
	srand(time(0));
	for (int i = 1; i <= 11; i++)
	{
		NodeT* y = (NodeT*)malloc(sizeof(NodeT));
		int x = (rand() % (size)) + 1;
		y = os_select(root, x, opComp, opAttr);
		root = deleted(root, y->key, opComp2, opAttr2);
		size--;
		cout << endl;
		cout << "*" << x << "*" << endl;
		cout << endl;
		print3(root, 0);
		cout << endl;
	}
}
void perf()
{
	int n;

	for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE)
	{
		Operation opComp = tema7.createOperation("compS", n);
		Operation opAttr = tema7.createOperation("attrS", n);
		Operation opComp2 = tema7.createOperation("compD", n);
		Operation opAttr2 = tema7.createOperation("attrD", n);
		Operation opComp3 = tema7.createOperation("compB", n);
		Operation opAttr3 = tema7.createOperation("attrB", n);
		for (int test = 0; test < NR_TESTS; test++)
		{

			NodeT* root = (NodeT*)malloc(sizeof(NodeT));
			root = create(1, n, opComp3, opAttr3);
			int m = n;
			srand(time(0));
			for (int j = 1; j <= n; j++)
			{
				NodeT* y = (NodeT*)malloc(sizeof(NodeT));
				int x = (rand() % (m)) + 1;
				y = os_select(root, x, opComp, opAttr);
				root = deleted(root, y->key, opComp2, opAttr2);
				m--;

			}
		}
	}
	tema7.divideValues("compS", NR_TESTS);
	tema7.divideValues("attrS", NR_TESTS);
	tema7.addSeries("S", "compS", "attrS"); //selection

	tema7.divideValues("compD", NR_TESTS);
	tema7.divideValues("attrD", NR_TESTS);
	tema7.addSeries("D", "compD", "attrD"); //delete

	tema7.divideValues("compB", NR_TESTS);
	tema7.divideValues("attrB", NR_TESTS);
	tema7.addSeries("B", "compB", "attrB"); //build

	tema7.addSeries("total2", "S", "D");
	tema7.addSeries("total3", "total2", "B");
	tema7.createGroup("TOTAL", "total3");
}
void perf_all()
{
	perf();
	tema7.showReport();

}
int main()
{
	demo();
	//perf_all();
	return 0;
}