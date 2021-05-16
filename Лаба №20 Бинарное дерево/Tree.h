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
	double data; // ������ ���� double
	Tree* left; // ��������� �� ���� �����
	Tree* right; // ��������� �� ���� ������
	Tree* parent; // ��������� �� ������

	Tree(double dt); // �����������
	Tree(); // �����������
	~Tree(); // ����������
	void deleteTree() 
	{ 
		delete this; 
	}
	double getData();
	void addLeftTree(Tree* tree);
	void addRightTree(Tree* tree);
	// ������� ������
	void printTree(int );
	void printVTree();
	void printVTreeIter(int, vector<vector<int>>& arr);
	int watchDeep(int n = 1);
	void setData(double dt) 
	{ 
		data = dt; 
	}
	Tree* next(); // ����� ��������� �������
	void insertNode(double dt); // �������� ����
	void deleteNode(double dt); // ������� ����
	Tree* findElement(double dt); // ����� �������
	double findMax(); // ����� ��������
	Tree* findMin();
	void balancedSortTree(int n);
	void balancedTree(vector<double>& vec);
};
