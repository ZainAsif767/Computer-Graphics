//#include <iostream>
//#include <fstream>
//#include <math.h>
//#include <GL/glut.h>
//#include <GL/gl.h>
//
//using std::cout;
//using std::fstream;
//using std::ios;
//#define M_PI  3.14157
//
//const int screenWidth = 800;  // width of screen window in pixels
//const int screenHeight = 600; // height of screen window in pixels
//double rotate_x = 0.5;
//
//void drawPolyLineFile(const char *fileName)
//{
//	fstream inStream;
//
//	inStream.open(fileName, ios::in); // open the file
//
//	if (inStream.fail())
//	{
//		cout << "can't open it!";
//		return;
//	}
//
//	GLfloat numpolys, numPoints, x, y;
//	inStream >> numpolys; // read the number of polylines
//
//	for (int j = 0; j < numpolys; j++) // read each polyline
//	{
//		inStream >> numPoints;	// number of points in first PolyLine
//		glBegin(GL_LINE_STRIP); // draw the next polyline
//		for (int i = 0; i < numPoints; i++)
//		{
//			inStream >> x >> y; // read the next x, y pair
//			glVertex2f(x, y);
//		}
//		glEnd();
//	}
//	inStream.close();
//}
//
//void setWindow(int xs, int xe, int ys, int ye)
//{
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluOrtho2D((GLint)xs, (GLint)xe, (GLint)ys, (GLint)ye);
//}
//
//void myInit(void)
//{
//	glClearColor(1.0, 1.0, 1.0, 1.0); // background color is white
//	glColor3f(1.0f, 0.0f, 0.0f);	  // drawing color is red
//	glPointSize(2.0);				  // a 'dot' is 2 by 2 pixels
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluOrtho2D(0.0, (GLdouble)screenWidth, 0.0, (GLdouble)screenHeight); // dino window
//	glViewport(0, 0, screenWidth, screenHeight);
//}
//
//void myDisplay(void)
//{
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	const int numMotifs = 12;
//	const int centerX = 300; // X-coordinate of the center of the circle
//	const int centerY = 300; // Y-coordinate of the center of the circle
//    const int radius = 150;
//    const int motifWidth = 200;
//    const int motifHeight = 200;
//    // Radius of the circular arrangement
//
//	for (int i = 0; i < numMotifs; i++) {
//		double angle = 2 * M_PI * i / numMotifs; // Calculate angle for each motif
//		int x = centerX + static_cast<int>(radius * cos(angle));
//		int y = centerY + static_cast<int>(radius * sin(angle));
//
//		glViewport(x, y, 104, 84);
//        glMatrixMode(GL_MODELVIEW);
//        glPushMatrix();
//        glLoadIdentity(); // Load identity matrix before transformations
//		drawPolyLineFile("dino.txt");
//
//        // glTranslatef(x + motifWidth / 2, y + motifHeight / 2, 0);
//        // glRotatef(angle * 180 / M_PI, 0, 0, 1); // Rotate around the z-axis
//        // glRotatef(i*30, 0, 0, 1); // Rotate around the z-axis
//        // glTranslatef(-motifWidth / 2, -motifHeight / 2, 0);
//		drawPolyLineFile("dino.txt");
//	}
//	
//
//	glFlush();
//	glutSwapBuffers();
//}
//
//int main(int argc, char **argv)
//{
//	glutInit(&argc, argv); // Initialize GLUT with command-line arguments
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//	glutInitWindowSize(screenWidth, screenHeight);
//	glutInitWindowPosition(10, 10);
//	glutCreateWindow("Dino CircleTiles Drawing");
//	glutDisplayFunc(myDisplay);
//	myInit();
//	glutMainLoop();
//	return 0;
//}