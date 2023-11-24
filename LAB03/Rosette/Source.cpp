// Lab Activity 9

#include <gl/glut.h>
#include <Windows.h>
#include <gl/GLU.h>
#include <gl/GL.h>
#include <math.h>

using namespace std;

int screenWidth = 640;
int screenHeight = 480;

class GlintPoint
{
public:
	int  x, y;
};

class Point2 {
public:
	float x, y;
	void set(float dx, float dy) { x = dx; y = dy; }
	void set(Point2& p) { x = p.x; y = p.y; }
	Point2(float xx, float yy) { x = xx; y = yy; }
	Point2() { x = y = 0; }
};

Point2 currPos;
Point2 CP;

void moveTo(Point2 p)
{
	CP.set(p);
}
void lineTo(Point2 p)
{
	glBegin(GL_LINES);
	glVertex2f(CP.x, CP.y);
	glVertex2f(p.x, p.y);
	glEnd();
	glFlush();
	CP.set(p);
}

void myInit(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 0.0); // background is red
	glColor3f(0.0, 0.0, 1.0); // drawing color is blue
}

void rosette(int N, float radius)
{
	Point2* pointlist = new Point2[N];
	GLfloat theta = (2.0f * 3.1415926536) / N;
	for (int c = 0; c < N; c++)
	{
		pointlist[c].set(radius * sin(theta * c), radius * cos(theta * c));
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			moveTo(pointlist[i]);
			lineTo(pointlist[j]);
		}
	}
}

void render()
{
	//this is the callback for displays
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(10, 10, 640, 480);
	rosette(20, .66f);
	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(30, 30);
	glutCreateWindow("Lab 3 - Rossete");
	glutDisplayFunc(render);

	myInit();
	glutMainLoop();

}

