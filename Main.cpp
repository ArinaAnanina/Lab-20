#include "Tree.h"
#include <iostream>
#include <Windows.h>    
#include <gl/GL.h>    
#include <gl/GLU.h>    
#include <glut.h>
#include <string>
using namespace std;

Tree* bt = new Tree();

int MAX_LEVEL = 0;
int LEVEL_HEIGHT = 0;
float WIDTH_EL = 0.0f;

const int NODE_RADIUS = 20;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

float getY(int level = 1) 
{
	return (MAX_LEVEL - level + 1) * LEVEL_HEIGHT;
}

void drawNode(float cx, float cy, double value, int num_segments = 20) {
	float th = 2.0f * 3.1415926f / float(num_segments);

	// Set new viewport
	glViewport(cx - NODE_RADIUS, cy - NODE_RADIUS, NODE_RADIUS * 2, NODE_RADIUS * 2);

	// Draw circle
	glColor3ub(255, 255, 255);
	glBegin(GL_TRIANGLE_FAN);
	for (int ii = 0; ii < num_segments; ii++) {
		glVertex2f(cosf(th * ii), sinf(th * ii));
	}
	glEnd();

	// Prepare text 0,1230000 => 0,123
	string text = to_string(value);
	int foundedIndex = text.length();
	for (int i = text.length() - 1; i >= 0; i--) {
		if (text[i] == (char)'0') {
			foundedIndex = i;
		}
		else {
			continue;
		}
	}
	if (text[foundedIndex - 1] == (char)',') {
		foundedIndex++;
	}
	text = text.substr(0, foundedIndex);

	// Draw Value
	glColor3ub(11, 65, 179);

	float xPos = -0.25 * (text.length() - 0.5);
	glRasterPos2f(xPos, -0.31);
	for (const char* p = text.c_str(); *p != '\0'; p++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p);
	}

	// Return viewport
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}
void drawLine(float sx, float sy, float ex, float ey) {
	float x1 = sx < ex ? -1 : 1;
	float y1 = sy > ey ? 1 : -1;
	float x2 = sx < ex ? 1 : -1;
	float y2 = sy > ey ? -1 : 1;

	glViewport(min(sx, ex), min(sy, ey), abs(sx - ex) + 1, abs(sy - ey) + 1);

	glLineWidth(4);
	glColor3ub(100, 100, 100);

	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}
void displayNodeIter(Tree& inner, float x, float y, int level = 1) {
	float k = WIDTH_EL * pow(2, MAX_LEVEL - level - 1);
	float nextY = getY(level + 1);
	if (inner.left != NULL) {
		drawLine(x, y, x - k, nextY);
		displayNodeIter(*inner.left, x - k, nextY, level + 1);
	}
	if (inner.right != NULL) {
		drawLine(x, y, x + k, nextY);
		displayNodeIter(*inner.right, x + k, nextY, level + 1);
	}
	drawNode(x, y, inner.data);
}
void display() {
	glClear(GL_COLOR_BUFFER_BIT); // очищение
	float y = getY(1);
	displayNodeIter(*bt, WINDOW_WIDTH / 2, y);
	glFlush();
}
void drawTreeGL(int argc, char** argv) {
	MAX_LEVEL = bt->watchDeep(0);
	WIDTH_EL = round(WINDOW_WIDTH / (pow(2, MAX_LEVEL - 1) + 1) / 2);
	LEVEL_HEIGHT = round(WINDOW_HEIGHT / (MAX_LEVEL + 1));

	glutInit(&argc, argv);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT); //создание окна
	glutInitWindowPosition(80, 80); // указание позиции окна
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutCreateWindow("Tree");
	glutDisplayFunc(display);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glutMainLoop();
}
int main(int argc, char** argv)
{
	system("color F0");
	setlocale(LC_ALL, "rus");

	cout << "Введите кол-во узлов дерева." << endl;
	cout << "n=";
	int n;
	cin >> n;
	Tree tree;
	bt->balancedSortTree(n);
	bt->printVTree();
	cout << "Максимальный элемент дерева: "<< bt->findMax() << endl;

	drawTreeGL(argc, argv);
	return 0;
}