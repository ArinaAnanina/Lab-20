#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>    
#include <gl/GL.h>    
#include <gl/GLU.h>    
#include <glut.h>

using namespace std;
class Tree {
public:
	double data; // Данные типа double
	Tree* left; // Указатель на узел слева
	Tree* right; // Указатель на узел справа
	Tree* parent; // Указатель на предка

	Tree(double dt); // Конструктор
	Tree(); // Конструктор
	~Tree(); // Деструктор
	void deleteTree() 
	{ 
		delete this; 
	}
	double getData();
	void addLeftTree(Tree* tree);
	void addRightTree(Tree* tree);
	// Удалить дерево
	void printTree(int );
	void printVTree();
	void printVTreeIter(int, vector<vector<int>>& arr);
	int watchDeep(int n = 1);
	void setData(double dt) 
	{ 
		data = dt; 
	}
	Tree* next(); // Найти следующий элемент
	void insertNode(double dt); // Вставить узел
	void deleteNode(double dt); // Удалить узел
	Tree* findElement(double dt); // Найти элемент
	double findMax(); // Найти максимум
	Tree* findMin();
	void balancedSortTree(int n);
	void balancedTree(vector<double>& vec);
};
