// Lab3

#include <gl/glut.h>
#include <iostream>
#include <fstream>
#include <math.h>

using std::cout;
using std::fstream;
using std::ios;

const int screenWidth = 640;	   // width of screen window in pixels 
const int screenHeight = 480;	   // height of screen window in pixels
double rotate_x = 1;

void setWindow(int xs, int xe, int ys, int ye) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D((GLint)xs, (GLint)xe, (GLint)ys, (GLint)ye);
}

void drawPolyLineFile(const char* fileName)
{
	fstream inStream;

	inStream.open(fileName, ios::in);	// open the file

	if (inStream.fail())
	{
		cout << "can't open it!"; return;
	}
	// clear the screen
    //GLint numpolys, numPoints, x ,y;
	GLfloat numpolys, numPoints, x, y;
	inStream >> numpolys;		           // read the number of polylines

	glScalef(rotate_x, rotate_x, 1.0f);
	for (int j = 0; j < numpolys; j++)  // read each polyline
	{
		inStream >> numPoints;       //number of points in first PolyLine  
		glBegin(GL_LINE_STRIP);	     // draw the next polyline
		for (int i = 0; i < numPoints; i++)
		{
			inStream >> x >> y;        // read the next x, y pair
			glVertex2f(x, y);
		}
		glEnd();
	}
	inStream.close();
}

void keyPress(int key, int x, int y)
{
	if (key == 27)
		exit(0);
	if (key == GLUT_KEY_UP) {

		rotate_x += .05;
		glutPostRedisplay();
	}
	if (key == GLUT_KEY_DOWN) {
		rotate_x -= .05;
		glutPostRedisplay();
	}
}

void myInit(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);       // background color is white
	glColor3f(0.0f, 0.0f, 0.0f);         // drawing color is black
	glPointSize(2.0);		          // a 'dot' is 2 by 2 pixels
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)screenWidth, 0.0, (GLdouble)screenHeight);//dino window
	glViewport(0, 0, screenWidth, screenHeight);

}


void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawPolyLineFile("dino.txt");
	glFlush();
	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // set display mode
	glutInitWindowSize(screenWidth, screenHeight); // set window size
	glutInitWindowPosition(10, 10); // set window position on screen
	glutCreateWindow("Dino Zoom out and in"); // open the screen window
	glutDisplayFunc(myDisplay);     // register redraw function
	glutSpecialFunc(keyPress);
	myInit();
	glutMainLoop(); 		     // go into a perpetual loop
	return 0;
}