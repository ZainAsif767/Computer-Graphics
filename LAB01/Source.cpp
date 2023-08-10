#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <gl/glut.h>

int screenWidth = 840;
int screenHeight = 680;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer
	glClearColor(0.9f, 0.9f, 0.9f, 0.0); // Set clear color to black
	glColor3f(1, 0, 0);
	glFlush(); // Render the scene
}

int main(int argc, char** argv)	
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(screenWidth,screenHeight);
	glutInitWindowPosition(30, 30);
	glutCreateWindow("Zain's first OGL program");
	glutDisplayFunc(display); // Set the display callback function
	PlaySoundW(L"Sickick.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	glutMainLoop(); // Start the main GLUT loop
	return 0;
}