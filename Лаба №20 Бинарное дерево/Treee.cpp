#include "Tree.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;


Tree::Tree(double dt)
{
	data = dt; 
	left = NULL; 
	right = NULL;
	parent = NULL;
}
Tree::Tree()
{
	data = NULL;
	left = NULL;
	right = NULL;
	parent = NULL;
}
Tree::~Tree()
{
	delete this->left;
	delete this->right;
}
double Tree::getData()
{
	return data;
}
void Tree::addLeftTree(Tree* tree)
{
	left = tree;
}
void Tree::addRightTree(Tree* tree)
{
	right = tree;
}

void Tree::printTree(int n)
{
	if (this != NULL) {
		this->left->printTree(n + 1);
		for (int i = 1; i < n; i++) cout << " ";
		cout << this->getData() << endl;
		this->right->printTree(n + 1);
	}
}

void Tree::printVTree()
{
	int height = this->watchDeep(); // поиск глубины дерева
	vector<vector<int>> arr;
	// создание вектора векторов
	for (int i = 0; i < height; i++) {
		vector<int> in_arr;
		arr.push_back(in_arr);
	}

	this->printVTreeIter(0, arr);

	string valMargin = " ";
	for (int i = 0; i < arr.size() - 1; i++) {
		string spaces = "";
		for (int k = 0; k < pow(2, arr.size() - i - 2) - 1; k++) {
			spaces += " ";
		}
		for (int j = 0; j < arr[i].size(); j++) {
			if (arr[i][j] == NULL) {
				cout << spaces << "-" << spaces << valMargin;
			}
			else {
				cout << spaces << arr[i][j] << spaces << valMargin;
			}
			
		}
		cout << endl;
	}
}

void Tree::printVTreeIter(int n, vector<vector<int>>&arr)
{
	if (this != NULL) {
		arr[n].push_back(this->getData());
		this->left->printVTreeIter(n + 1, arr);
		this->right->printVTreeIter(n + 1, arr);
	}
	else {
		arr[n].push_back(NULL);
		if (n < arr.size() - 1) {
			this->printVTreeIter(n + 1, arr);
			this->printVTreeIter(n + 1, arr);
		}
	}
}

int Tree::watchDeep(int n)
{
	if (this != NULL) {
		int kLeft = this->left->watchDeep(n + 1);
		int kRight = this->right->watchDeep(n + 1);
		return (kLeft > kRight) ? kLeft : kRight;
	}
	return n;
}
Tree* Tree::next()
{
	Tree* tree = this;
	if (tree->right != NULL)
		return tree->right->findMin();
	Tree* t = tree->parent;
	while ((t != NULL) && (tree == t->right)) {
		tree = t;
		t = t->parent;
	}
	return t;
}

void Tree::insertNode(double dt)
{
	Tree* tree = this;
	if (tree == NULL) {
		return;
	}
	if (tree->data == NULL) {
		this->data = dt;
		return;
	}
	while (tree != NULL) {
		if (dt >= tree->data) {
			if (tree->right != NULL) {
				tree = tree->right;
			}
			else {
				Tree* t = new Tree(dt);
				t->parent = tree;
				tree->right = t;
				break;
			}
		}
		else if (dt < tree->data) {
			if (tree->left != NULL) {
				tree = tree->left;
			}
			else {
				Tree* t = new Tree(dt);
				t->parent = tree;
				tree->left = t;
				break;
			}
		}
	}
}
void Tree::deleteNode(double dt)
{
	Tree* e = this->findElement(dt);
	Tree* p = e->parent; //предок удаляемого элемента
	// Первый случай: удаляемый элемент не имеет потомков
	if ((e->left == NULL) && (e->right == NULL)) {
		if (p->left == e) p->left = NULL;
		if (p->right == e) p->right = NULL;
	}
	else if ((e->left == NULL) || (e->right == NULL)) {
		if (e->left == NULL) {
			if (p->left == e) p->left = e->right;
			else p->right = e->right;
			e->right->parent = p;
		}
		else {
			if (p->left == e) p->left = e->left;
			else p->right = e->left;
			e->left->parent = p;
		}
	}
	else {
		Tree* s = e->next();
		// Следующий элемент за удаляемым
		e->data = s->data;
		if (s->parent->left == s) {
			s->parent->left = s->right;
			if (s->right != NULL)
				s->right->parent = s->parent;
		}
		else {
			s->parent->right = s->right;
			if (s->right != NULL)
				s->right->parent = s->parent;
		}
	}

}
Tree* Tree::findElement(double dt) 
{
	if ((this == NULL) || (dt == this->data))
		return this;
	if (dt < this->data) return this->left->findElement(dt);
	else return this->right->findElement(dt);
	
}
double Tree::findMax()
{
	if (this == NULL) return NULL;
	if (this->right == NULL) return this->data;
	return this->right->findMax();
}
Tree* Tree::findMin() 
{
	if (this->left == NULL) return this;
	return this->left->findMin();
}
void Tree::balancedSortTree(int n) {
	if (n == 0) return ;
	vector<double> vec;
	double dt;
	for (int l = 0; l < n; l++)
	{
		cout << "data=";
	    cin >> dt; 
	    vec.push_back(dt);
	}
	sort(vec.begin(), vec.end());
	balancedTree(vec);
}
void Tree::balancedTree(vector<double>& vec)
{
	this->insertNode(vec[vec.size() / 2]);
	if (vec.size() == 2)
	{
		this->insertNode(vec[0]);
		return;
	}
	if (vec.size() == 1)
	{
		return;
	}
	vector<double> left;
	vector<double> right;
	int mid = vec.size() / 2;
	for (int i = 0; i < mid; i++)
	{
		left.push_back(vec[i]);
	}
	for (int i = mid + 1; i < vec.size(); i++)
	{
		right.push_back(vec[i]);
	}
	balancedTree(left);
	balancedTree(right);
}