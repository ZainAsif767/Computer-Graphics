//#include<iostream>
//#include<gl/glut.h>
//
//using namespace std;
//
//float l = 50.0;
//float r = 550.0;
//float b = 50.0;
//float t = 359.0;
//
//void init()
//{
//	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluOrtho2D(0.0, 600.0, 0.0, 400.0);
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//}
//
//void drawGoldenTriangle(float l, float b, float r, float t) {
//
//	glColor3f(0.0, 1.0, 0.0);
//	glBegin(GL_LINE_LOOP);
//	glVertex2f(l, t);
//	glVertex2f(r, t);
//	glVertex2f(r, b);
//	glVertex2f(l, b);
//	glEnd();
//}
//
//void display() {
//	glClear(GL_COLOR_BUFFER_BIT);
//	drawGoldenTriangle(l, b, r, t);
//	cout << "l:" << l << " b : " << b << " r : " << r << "t : " << t << endl;
//	float temp_r = t;
//	drawGoldenTriangle(l, b, temp_r, t);
//	cout << "l:" << l << " b : " << b << " r : " << temp_r << "t : " << t << endl;
//	l = t;
//	b = t;
//	t = r - temp_r;
//	r = temp_r;
//	drawGoldenTriangle(l, b, r, t);
//	cout << "l:" << l << " b : " << b << " r : " << r << "t : " << t << endl;
//	//temp_r = r - t;
//	//drawGoldenTriangle(l, b, temp_r, t);
//	//cout << "l:" << l << " b : " << b << " r : " << temp_r << "t : " << t << endl;
//	glutSwapBuffers();
//}
//
//int main(int argc, char** argv)
//{
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
//	glutInitWindowPosition(150, 150);
//	glutInitWindowSize(600, 400);
//	glutCreateWindow("Golden Triangle");
//	init();
//	glutDisplayFunc(display);
//	glutMainLoop();
//
//	return 0;
//}

#include<iostream>
#include<gl/glut.h>
using namespace std;

float l = 0.0;
float r = 500.0;
float b = 0.0;
float t = 309.0;

void init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 600.0, 0.0, 400.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void drawGoldenRectangle(float l, float b, float r, float t) {

	glColor3f(1.0, 0.0, 0.3);
	//glLineWidth(0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(l, t);
	glVertex2f(r, t);
	glVertex2f(r, b);
	glVertex2f(l, b);
	glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	drawGoldenRectangle(l+50, b+50, r+50, t+50);
	float temp_r = r;
	r = t;
	t = temp_r - t;
	drawGoldenRectangle(l+50, b+50, r+50, t+50);

	while (r > 1) {
		temp_r = r;
		r = t;
		t = temp_r - t;
		drawGoldenRectangle(l+50, b+50, r+50, t+50);
	}
	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(150, 150);
	glutInitWindowSize(600, 400);
	glutCreateWindow("Golden Ratio Rectangle");
	init();
	glutDisplayFunc(display);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glutMainLoop();
}


