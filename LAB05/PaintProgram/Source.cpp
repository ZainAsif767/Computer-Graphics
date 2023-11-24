#include <iostream>
#include <gl/glut.h>
#include <vector>
#include <math.h>
#include <fstream>
#include <string>

using namespace std;

int screenWidth = 840;
int screenHeight = 480;
int dot_x = -1;
int dot_y = -1;
float minX = -1.0, minY = -1.0, maxX = 1.0, maxY = 1.0;
int VPBottom = 0, VPLeft = 0, VPWidth = 640, VPHeight = 480;
const char* instructionText = "To draw a triangle press 't', circle 'c', rectangle 'r', pentagon 'p', cylinder 'p', DELETE using 'd'";



class Dot {
public:
	int x = -1;
	int y = -1;
	Dot(int x, int y) {
		this->x = x;
		this->y = y;
	}

	Dot() = default;
};

vector<Dot> dotsVector = {};


class Shape {
public:
	virtual void draw() = 0;
	//virtual bool containsPoint(float x, float y) = 0;
	//virtual void move(float dx, float dy) = 0;
};

class Triangle : public Shape {
public:
	void draw() override {
		glBegin(GL_TRIANGLES);
		glColor3f(1.0, 1.0, 0.0);
		glVertex2f(200, 150);
		glVertex2f(100, 150);
		glVertex2f(150, 50);
		glEnd();
	}
	//bool containsPoint(float x, float y) override {
	//	// Check if the point is inside the triangle's bounding box
	//	return (x >= 100 && x <= 200 && y >= 50 && y <= 150);
	//}
	//void move(float dx, float dy) override {
	//	// Update the triangle's vertices based on the movement
	//	// Adjust the vertices' coordinates by dx and dy
	//	// For example:
	//	// vertex1.x += dx; vertex1.y += dy;
	//	// vertex2.x += dx; vertex2.y += dy;
	//	// vertex3.x += dx; vertex3.y += dy;
	//}
};

class Circle : public Shape {
public:
	void draw() override {
		const float PI = 3.14159;
		int segments = 50;
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(1.0, 0.0, 0.0);
		for (int i = 0; i <= segments; i++) {
			float angle = 2.0f * PI * float(i) / float(segments);
			float x = 50 * cos(angle);
			float y = 50 * sin(angle);
			glVertex2f(x + 320, y + 240);
		}
		glEnd();
	}
	//bool containsPoint(float x, float y) override {
	//	// Check if the point is inside the circle's bounding box
	//	float centerX = 320;
	//	float centerY = 240;
	//	float radius = 50;
	//	return ((x - centerX) * (x - centerX) + (y - centerY) * (y - centerY)) <= (radius * radius);
	//}
	//void move(float dx, float dy) override {
	//	// Update the circle's center based on the movement
	//	// Adjust centerX by dx and centerY by dy
	//}
};

class Rectangle : public Shape {
public:
	void draw() override {
		glBegin(GL_QUADS);
		glColor3f(1.4, 1.2, 0.4);
		glVertex2i(400, 400);  // Top left vertex
		glVertex2i(500, 400);  // Top right vertex
		glVertex2i(500, 300);  // Bottom right vertex
		glVertex2i(400, 300);  // Bottom left vertex
		glEnd();
	}
};

class Pentagon : public Shape {
public:
	void draw() override {
		glBegin(GL_POLYGON);
		glColor3f(0.0, 1.6, 1.2);
		glVertex2f(450, 150);
		glVertex2f(500, 200);
		glVertex2f(550, 200);
		glVertex2f(575, 175);
		glVertex2f(525, 125);
		glEnd();
	}
};

class Cylinder : public Shape {
public:
	void draw() override {
		const float PI = 3.14159;
		int segments = 50;
		float radius = 50.0f;
		glBegin(GL_TRIANGLE_STRIP);
		glColor3f(0.0, 1.0, 1.0);
		for (int i = 0; i <= segments; i++) {
			float angle = 2.0f * PI * float(i) / float(segments);
			float x = radius * cos(angle);
			float y = radius * sin(angle);
			glVertex2f(x + 100, y + 240);
			glVertex2f(x + 100, y + 340);
		}
		glEnd();
	}
};

void drawDot(int x, int y) {
	glColor3f(1.0f, 0.5f, 0.7f);
	glPointSize(10.0);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

vector<Shape*> shapes;
Shape* currentShape = nullptr;

void init() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
}
void renderShapes() {
	/*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);*/
	if (dot_x != -1 && dot_y != -1) {
	}
	for (int i = 0; i < dotsVector.size(); i++) {
		drawDot(dotsVector[i].x, dotsVector[i].y);
	}

	for (Shape* shape : shapes) {
		shape->draw();
	}

	glColor3f(0.0f, 0.0f, 0.0f);
	glRasterPos2i(10, screenHeight - 20);
	for (const char* c = instructionText; *c != '\0'; ++c) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
	}
	glFlush();
}

void reshape(int width, int height) {
	screenWidth = width;
	screenHeight = height;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)screenWidth, 0.0, (GLdouble)screenHeight);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void mouseHandler(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		Dot newDot = Dot(x, screenHeight - y);
		dotsVector.push_back(newDot);
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		glClear(GL_COLOR_BUFFER_BIT);
		// Clear all dots
		dotsVector.clear();
		glClear(GL_COLOR_BUFFER_BIT);
		glutPostRedisplay();

	}
	glutPostRedisplay();
	
}

void motionHandler(int x, int y) {
	dot_x = x;
	dot_y = screenHeight - y;
	Dot newDot = Dot(x, screenHeight - y);
	dotsVector.push_back(newDot);
	glutPostRedisplay();
}

//bool isDragging = false;  // Flag to indicate if a shape is being dragged
//float startX, startY;     // Starting position of the drag

//void myMouse(int button, int state, int x, int y) {
//	if (button == GLUT_LEFT_BUTTON) {
//		if (state == GLUT_DOWN) {
//			// Check if any shape contains the clicked point
//			for (Shape* shape : shapes) {
//				if (shape->containsPoint(x, screenHeight - y)) {
//					currentShape = shape;
//					isDragging = true;
//					startX = x;
//					startY = screenHeight - y;
//					break;
//				}
//			}
//		}
//		else if (state == GLUT_UP) {
//			isDragging = false;
//		}
//	}
//}
//
//void myMotion(int x, int y) {
//	if (isDragging && currentShape) {
//		float dx = x - startX;
//		float dy = screenHeight - y - startY;
//		currentShape->move(dx, dy);
//		startX = x;
//		startY = screenHeight - y;
//		glutPostRedisplay();
//	}
//}

void myKeys(unsigned char key, int x, int y) {
	switch (key) {
	case 't':
		currentShape = new Triangle();
		shapes.push_back(currentShape);
		glutPostRedisplay();
		break;
	case 'c':
		currentShape = new Circle();
		shapes.push_back(currentShape);
		glutPostRedisplay();
		break;
	case 'r':
		currentShape = new Rectangle();
		shapes.push_back(currentShape);
		glutPostRedisplay();
		break;
	case 'p':
		currentShape = new Pentagon();
		shapes.push_back(currentShape);
		glutPostRedisplay();
		break;
	case 'y':
		currentShape = new Cylinder();
		shapes.push_back(currentShape);
		glutPostRedisplay();
		break;
	case 'd':
		if (!shapes.empty()) {
			delete shapes.back();
			shapes.pop_back();
			currentShape = nullptr;
			glutPostRedisplay();
		}
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Simple Drawing Program");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, screenWidth, 0.0, screenHeight);
	glMatrixMode(GL_MODELVIEW);

	glutDisplayFunc(renderShapes);
	glutKeyboardFunc(myKeys);
	/*glutMouseFunc(myMouse);
	glutMotionFunc(myMotion);*/
	glutMouseFunc(mouseHandler);
	glutMotionFunc(motionHandler);

	init();
	glutMainLoop();

	for (Shape* shape : shapes) {
		delete shape;
	}

	return 0;
}
