//#include <windows.h>
//#include <iostream>
//#include <fstream>
//#include <math.h>
//#include <gl/glut.h>
//
//using std::cout;
//using std::fstream;
//using std::ios;
//
//const int screenWidth = 640;	   // width of screen window in pixels
//const int screenHeight = 480;	   // height of screen window in pixels
//
//void drawPolyLineFile(const char* fileName)
//{
//	fstream inStream;
//
//	inStream.open(fileName, ios::in);	// open the file
//
//	if (inStream.fail())
//	{
//		cout << "can't open it!";return;
//	}
//
//	//glClear(GL_COLOR_BUFFER_BIT);      // clear the screen
//
//	//GLint numpolys, numPoints, x ,y;
//
//	GLfloat numpolys, numPoints, x, y;
//	inStream >> numpolys;		           // read the number of polylines
//
//	for (int j = 0; j < numpolys; j++)  // read each polyline
//	{
//		inStream >> numPoints;       //number of points in first PolyLine
//		glBegin(GL_LINE_STRIP);	     // draw the next polyline
//		for (int i = 0; i < numPoints; i++)
//		{
//			inStream >> x >> y;        // read the next x, y pair
//			glVertex2f(x + 1800, y + 1800);
//		}
//		glEnd();
//	}
//
//	inStream.close();
//}
//
//void myInit(void)
//{
//	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // background color is black
//	glColor3f(0.0f, 0.0f, 0.0f);         // drawing color is black
//	glPointSize(2.0);		          // a 'dot' is 2 by 2 pixels
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	//gluOrtho2D(-(GLdouble)screenWidth, (GLdouble)screenWidth, -(GLdouble)screenHeight, (GLdouble)screenHeight);//dino window
//	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);//dino window
//
//	glViewport(0, 0, screenWidth, screenHeight);
//
//}
//
//const int numMotifs = 1;
//float H = 400;
//void myDisplay(void)
//{
//	glClear(GL_COLOR_BUFFER_BIT);      // clear the screen
//	glColor3f(0.0f, 0.0f, 0.0f);         // drawing color is Red
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	glViewport(20, 20, 640, 480);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluOrtho2D(-2000, 640 * 12, -1600, 480 * 12);
//	float x = 90;
//	glPushMatrix();
//	for (float i = 0; i < 2 * 3.142; i = i + ((2 * 3.142) / 12)) {
//
//		glTranslatef(1200 * cos(i), 1200 * sin(i), 0);
//		glPushMatrix();
//		glRotatef(x, 0, 0, 1);
//		drawPolyLineFile("dino.txt");
//		glPopMatrix();
//		x += 30;
//
//	}
//	glPopMatrix();
//	glutSwapBuffers();
//}
//
//int main(int argc, char** argv)
//{
//
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // set display mode
//	glutInitWindowSize(screenWidth, screenHeight); // set window size
//	glutInitWindowPosition(100, 100); // set window position on screen
//	glutCreateWindow("Dino Rotated"); // open the screen window
//	glutDisplayFunc(myDisplay);     // register redraw function
//	myInit();
//	glutMainLoop(); 		     // go into a perpetual loop
//	return 1;
//}

//
////////////////////////////////
//
//
//#include <iostream>
//#include <fstream>
//#include <math.h>
//#include <GL/glut.h>
//#include <GL/gl.h>
//#include <cmath>    
//
//
//using std::cout;
//using std::fstream;
//using std::ios;
//#define M_PI  3.14157
//
//const int screenWidth = 800;  // width of screen window in pixels
//const int screenHeight = 900; // height of screen window in pixels
//double rotate_x = 0.5;
//
//void drawPolyLineFile(const char *fileName)
//{
//    fstream inStream;
//
//    inStream.open(fileName, ios::in); // open the file
//
//    if (inStream.fail())
//    {
//        cout << "can't open it!";
//        return;
//    }
//
//    GLfloat numpolys, numPoints, x, y;
//    inStream >> numpolys; // read the number of polylines
//
//    for (int j = 0; j < numpolys; j++) // read each polyline
//    {
//        inStream >> numPoints;  // number of points in first PolyLine
//        glBegin(GL_LINE_STRIP); // draw the next polyline
//        for (int i = 0; i < numPoints; i++)
//        {
//            inStream >> x >> y; // read the next x, y pair
//            glVertex2f(x, y);
//        }
//        glEnd();
//    }
//    inStream.close();
//}
//
//void setWindow(int xs, int xe, int ys, int ye)
//{
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluOrtho2D((GLint)xs, (GLint)xe, (GLint)ys, (GLint)ye);
//}
//
//void myInit(void)
//{
//    glClearColor(1.0, 1.0, 1.0, 1.0); // background color is white
//    glColor3f(1.0f, 0.0f, 0.0f);      // drawing color is black
//    glPointSize(2.0);                 // a 'dot' is 2 by 2 pixels
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluOrtho2D(0.0, (GLdouble)screenWidth, 0.0, (GLdouble)screenHeight); // dino window
//    glViewport(0, 0, screenWidth, screenHeight);
//}
//
//void myDisplay(void)
//{
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    const int numMotifs = 12;
//    const int centerX = 300; // X-coordinate of the center of the circle
//    const int centerY = 350; // Y-coordinate of the center of the circle
//    const int radius = 120;
//    const int motifWidth = 200;
//    const int motifHeight = 200;
//    // Radius of the circular arrangement
//    for (int i = 0; i < numMotifs; i++)
//    {
//        double angle = 2 * M_PI * i / numMotifs; // Calculate angle for each motif
//        int x = centerX + static_cast<int>(radius * cos(angle));
//        int y = centerY + static_cast<int>(radius * sin(angle));
//
//        glViewport(x, y, 164, 164);
//        glMatrixMode(GL_MODELVIEW);
//        glPushMatrix();
//        glLoadIdentity(); // Load identity matrix before transformations
//        double rotationAngle = angle - M_PI / 2.0;
//        cout << x + motifWidth / 2 << ":" << y + motifHeight / 2;
//        glTranslatef(x + motifWidth / 2, y + motifHeight / 2, 0); // Translate to the center of the motif
//        glRotatef(rotationAngle * 180.0 / M_PI, 0, 0, 1);         // Rotate around the z-axis
//        glTranslatef(-motifWidth / 2, -motifHeight / 2, 0);       // Translate back to the original position
//        cout << -motifWidth / 2 << ":" << -motifHeight / 2 << std::endl;
//
//        drawPolyLineFile("dino.txt");
//        glPopMatrix();
//    }
//
//    glFlush();
//    glutSwapBuffers();
//}
//
//int main(int argc, char **argv)
//{
//    glutInit(&argc, argv); // Initialize GLUT with command-line arguments
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//    glutInitWindowSize(screenWidth, screenHeight);
//    glutInitWindowPosition(100, 10);
//    glutCreateWindow("Dino Rotated");
//    glutDisplayFunc(myDisplay);
//    myInit();
//    glutMainLoop();
//    return 0;
//}