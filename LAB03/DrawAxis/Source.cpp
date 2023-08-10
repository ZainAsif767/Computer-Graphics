#include <iostream>
#include <fstream>
#include <string>
#include <GL/glut.h>
#include <vector>

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

int screenWidth = 640;
int screenHeight = 480;
int dot_x = -1;
int dot_y = -1;

float minX = -1.0, minY = -1.0, maxX = 1.0, maxY = 1.0;
int VPBottom = 0, VPLeft = 0, VPWidth = 640, VPHeight = 480;

std::vector<Dot> dotsVector = {};

void initGL() {
	glClearColor(255.0f, 255.0f, 255.0f, 1.0f);
	glColor3f(1, 0, 0);
}

void drawDot(int x, int y) {
	glColor3f(1.0f, 0.0f, 0.0f);
	glPointSize(10.0);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void drawAxis() {
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2f(minX, 0);
	glVertex2f(maxX, 0);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(0, minY);
	glVertex2f(0, maxX);
	glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	if (dot_x != -1 && dot_y != -1) {
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	for (int i = 0; i < dotsVector.size(); i++) {
		drawDot(dotsVector[i].x, dotsVector[i].y);
	}
	glViewport(VPBottom, VPLeft, VPWidth, VPHeight);
	//gluOrtho2D(minX, maxX, minY, maxY);
	drawAxis();
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

void keyboardHandler(unsigned char key, int x, int y) {
	switch (key)
	{
	case 'q':
		exit(0);
	case 's':
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void mouseHandler(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		dot_x = x;
		dot_y = screenHeight - y;
		Dot newDot = Dot(x, screenHeight - y);
		dotsVector.push_back(newDot);
	}

	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		glClear(GL_COLOR_BUFFER_BIT);
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


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(screenWidth, screenHeight);
	glutCreateWindow("Lab 03 - Axis ");
	initGL();
	glutDisplayFunc(display); // Set the display callback function
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboardHandler);
	glutMouseFunc(mouseHandler);
	glutMotionFunc(motionHandler);
	glutMainLoop(); // Start the main GLUT loop
	return 0;
}