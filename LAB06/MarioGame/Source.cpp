#include <gl/glut.h>
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include "Mario.h"

using namespace std;

void myInit(void)
{
	glClearColor(1.0,1.0,1.0,1.0);
	glViewport(0, 0, screenWidth, screenHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0, screenWidth, 0, screenHeight);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glEnable(GL_ALPHA_TEST); // in dono ko comment krne se full pic arhi hai with BG
	glAlphaFunc(GL_EQUAL, 1.0);
	//accept fragment if segment alpha = reference alpha i.e. 1.0
	// or glAlphaFunc(GL_NOTEQUAL,0.0);
	//accept fragment if fragment alpha not = reference alpha i.e. 0.0

}

void myDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	m.render();
	glPopMatrix();
	glFlush();
}

void spinner(int t)
{
	glutPostRedisplay();
	glutTimerFunc(50, spinner, t);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Mario Game");

	glutDisplayFunc(myDisplay);
	PlaySoundW(L"MarioSong.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	glutSpecialFunc(pressKeySpecial);
	glutSpecialUpFunc(releaseKeySpecial);
	glutKeyboardFunc(myKB_Handler);

	myInit();
	//glutIdleFunc(myDisplay);
	//spinner(500); // sets timer for mario to keep running

	glutMainLoop();
}








//#include <gl/glut.h>
//#include <iostream>
//#include <Windows.h>
//#include <stdio.h>
//#include "Mario.h"
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h" // Include stb_image.h
//
//using namespace std;
//
//GLuint texture;
//
//const char* imageFile = "background.png";
//
//
//void myInit(void)
//{
//	glClearColor(1.0, 1.0, 1.0, 1.0);
//	//glViewport(0, 0, screenWidth, screenHeight);
//
////	glMatrixMode(GL_PROJECTION);
//	//glLoadIdentity();
//
//	//gluOrtho2D(0, screenWidth, 0, screenHeight);
////	glMatrixMode(GL_MODELVIEW);
//	//glLoadIdentity();
//
//	int width, height, channels;
//	unsigned char* image = stbi_load(imageFile, &width, &height, &channels, 4); // Ensure 4 channels (RGBA)
//	if (!image) {
//		printf("Error loading image\n");
//		exit(1);
//	}
//
//	glGenTextures(1, &texture);
//	glBindTexture(GL_TEXTURE_2D, texture);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
//
//	stbi_image_free(image); // Free the image data
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//
//	//glEnable(GL_ALPHA_TEST | GL_DEPTH_TEST); // in dono ko comment krne se full pic arhi hai with BG
//	//glAlphaFunc(GL_EQUAL, 1.0);
//	//accept fragment if segment alpha = reference alpha i.e. 1.0
//	// or glAlphaFunc(GL_NOTEQUAL,0.0);
//	//accept fragment if fragment alpha not = reference alpha i.e. 0.0
//
//}
//
//void myDisplay(void) {
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	glLoadIdentity();
//
//
//	glEnable(GL_TEXTURE_2D);
//	glBindTexture(GL_TEXTURE_2D, texture);
//
//	glBegin(GL_QUADS);
//	glTexCoord2f(0.0, 0.0); glVertex2f(-1.0, -1.0); // Bottom-left
//	glTexCoord2f(1.0, 0.0); glVertex2f(1.0, -1.0);  // Bottom-right
//	glTexCoord2f(1.0, 1.0); glVertex2f(1.0, 1.0);   // Top-right
//	glTexCoord2f(0.0, 1.0); glVertex2f(-1.0, 1.0);  // Top-left
//	glEnd();
//
//	glDisable(GL_TEXTURE_2D);
// 
//	m.render();
//
//	glutSwapBuffers();
//	glFlush();
//}
//
//void spinner(int t)
//{
//	glutPostRedisplay();
//	glutTimerFunc(50, spinner, t);
//}
//
//int main(int argc, char** argv) {
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
//	glutInitWindowSize(screenWidth, screenHeight);
//	glutInitWindowPosition(10, 10);
//	glutCreateWindow("Mario Game");
//
//	glutDisplayFunc(myDisplay);
//	PlaySoundW(L"MarioSong.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
//	glutSpecialFunc(pressKeySpecial);
//	glutSpecialUpFunc(releaseKeySpecial);
//	glutKeyboardFunc(myKB_Handler);
//
//	myInit();
//	//glutIdleFunc(myDisplay);
//	//spinner(500); // sets timer for mario to keep running
//	glutMainLoop();
//}

