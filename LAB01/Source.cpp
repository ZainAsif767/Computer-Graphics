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
//
////Program for background image
//
//#include <gl/glut.h>
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h" // Include stb_image.h
//
//// Window dimensions
//int windowWidth = 800;
//int windowHeight = 600;
//
//// Global variable to hold the texture ID
//GLuint texture;
//
//const char* imageFile = "background.png"; // Change this to your image file
//
//void init() {
//    glClearColor(1.0, 1.0, 1.0, 1.0);
//
//    // Load the image and create a texture using stb_image.h
//    int width, height, channels;
//    unsigned char* image = stbi_load(imageFile, &width, &height, &channels, 4); // Ensure 4 channels (RGBA)
//    if (!image) {
//        printf("Error loading image\n");
//        exit(1);
//    }
//
//    glGenTextures(1, &texture);
//    glBindTexture(GL_TEXTURE_2D, texture);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
//
//    stbi_image_free(image); // Free the image data
//
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//}
//
//void display() {
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D, texture);
//
//    glBegin(GL_QUADS);
//    glTexCoord2f(0.0, 0.0); glVertex2f(-1.0, -1.0); // Bottom-left
//    glTexCoord2f(1.0, 0.0); glVertex2f(1.0, -1.0);  // Bottom-right
//    glTexCoord2f(1.0, 1.0); glVertex2f(1.0, 1.0);   // Top-right
//    glTexCoord2f(0.0, 1.0); glVertex2f(-1.0, 1.0);  // Top-left
//    glEnd();
//
//    glDisable(GL_TEXTURE_2D);
//
//    glutSwapBuffers();
//}
//
//int main(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
//    glutInitWindowSize(windowWidth, windowHeight);
//    glutCreateWindow("OpenGL Background Image");
//
//    glutDisplayFunc(display);
//
//    init();
//
//    glutMainLoop();
//
//    return 0;
//}
