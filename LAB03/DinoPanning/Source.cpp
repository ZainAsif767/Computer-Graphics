// Lab3

#include <gl/glut.h>
#include <iostream>
#include <fstream>
#include <math.h>


using std::cout;
using std::fstream;
using std::ios;


const int screenWidth = 650;	   // width of screen window in pixels 
const int screenHeight = 450;      // height of screen window in pixels

int ReferenceX = 0;
int ReferenceY = 0;
int viewportXmin = 0;
int viewportXmax = screenWidth;
int viewportYmin = 0;
int viewportYmax = screenHeight;

void setViewport()
{
	glViewport(viewportXmin, viewportYmin, viewportXmax - viewportXmin, viewportYmax - viewportYmin);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(viewportXmin, viewportXmax, viewportYmin, viewportYmax);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void drawPolyLineFile(const char* fileName)
{
	fstream inStream;

	inStream.open(fileName, ios::in);	// open the file

	if (inStream.fail())
	{
		cout << "can't open it!";
		return;
	}

	glClear(GL_COLOR_BUFFER_BIT);      // clear the screen

	//GLint numpolys, numPoints, x ,y;

	GLfloat numpolys, numPoints, x, y;
	inStream >> numpolys;		           // read the number of polylines

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
	glFlush();
	inStream.close();
}

void setWindow(int x, int y, double width, double height) {
	glViewport(x, y, (GLsizei)width, (GLsizei)height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, width, 0.0, height, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void myMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && GLUT_DOWN)
	{
		ReferenceX = x;
		ReferenceY = y;
	}
}

void myMotion(int x, int y)
{
	int dx = x - ReferenceX;
	int dy = -(y - ReferenceY);

	viewportXmin += dx;
	viewportXmax += dx;
	viewportYmin += dy;
	viewportYmax += dy;
	setViewport();

	ReferenceX = x;
	ReferenceY = y;

	glutPostRedisplay();
}

void myKeys(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w': 
		viewportYmin += 2;
		break;
	
	case 's':
		viewportYmax -= 2;
		break;
	case 'a':
		viewportXmin += 2;
		break;
	case 'd':
		viewportXmax -= 2;
		break;
	
	default:
		break;
	}
	setViewport();
	glutPostRedisplay();
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
	//drawPolyLineFile("birdhead.dat");		   // send all output to display
	//drawPolyLineFile("house.dat");

	drawPolyLineFile((char*)("dino.txt"));
	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB); // set display mode
	glutInitWindowSize(screenWidth, screenHeight); // set window size
	glutInitWindowPosition(230, 200); // set window position on screen
	glutCreateWindow("Dino Line Drawing"); // open the screen window
	glutDisplayFunc(myDisplay);     // register redraw function
	glutKeyboardFunc(myKeys);
	glutMouseFunc(myMouse);
	glutMotionFunc(myMotion);
	myInit();
	glutMainLoop(); 		     // go into a perpetual loop
	return 1;
}