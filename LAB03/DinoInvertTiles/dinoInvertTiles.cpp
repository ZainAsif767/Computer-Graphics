// Lab3

#include <gl/glut.h>
#include <iostream>
#include <fstream>
#include <math.h>

using std::cout;
using std::fstream;
using std::ios;

const int screenWidth = 650;  // width of screen window in pixels
const int screenHeight = 450; // height of screen window in pixels
double rotate_x = 0.5;

void drawPolyLineFile(const char *fileName)
{
	fstream inStream;

	inStream.open(fileName, ios::in); // open the file

	if (inStream.fail())
	{
		cout << "can't open it!";
		return;
	}

	// clear the screen

	// GLint numpolys, numPoints, x ,y;

	GLfloat numpolys, numPoints, x, y;
	inStream >> numpolys; // read the number of polylines

	for (int j = 0; j < numpolys; j++) // read each polyline
	{
		inStream >> numPoints;	// number of points in first PolyLine
		glBegin(GL_LINE_STRIP); // draw the next polyline
		for (int i = 0; i < numPoints; i++)
		{
			inStream >> x >> y; // read the next x, y pair
			glVertex2f(x, y);
		}
		glEnd();
	}
	inStream.close();
}

void setWindow(int xs, int xe, int ys, int ye)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D((GLint)xs, (GLint)xe, (GLint)ys, (GLint)ye);
}

void myInit(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0); // background color is white
	glColor3f(0.0f, 0.0f, 0.0f);	  // drawing color is black
	glPointSize(2.0);				  // a 'dot' is 2 by 2 pixels
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)screenWidth, 0.0, (GLdouble)screenHeight); // dino window
	glViewport(0, 0, screenWidth, screenHeight);
}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	// drawPolyLineFile("birdhead.dat");		   // send all output to display
	// drawPolyLineFile("house.dat");
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if ((i + j) % 2 == 0)
				setWindow(0, 640, 0, 480);
			else
				setWindow(0, 640, 480, 0);
			glViewport(i * 64, j * 44, 64, 44);
			drawPolyLineFile("dino.txt");
		}
	}
	glFlush();
	glutSwapBuffers();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv); // Initialize GLUT with command-line arguments
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Dino Inverted Tiles Drawing");
	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();
	return 0;
}
