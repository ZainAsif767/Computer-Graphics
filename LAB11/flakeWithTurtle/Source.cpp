#include "Canvas.h"
#include "Turtle.h"

#include <gl/glut.h>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

Canvas cvs(640, 600, "SnowFlake using Turtle");

float L = 10.0;
Turtle ninja;

void flakemotif() {
	ninja.moveTo(0.0, 0.1 * L);
	ninja.turnTo(0);
	ninja.forward(2 * L, 1);
	ninja.turn(60);
	ninja.forward(1 * L, 1);
	ninja.turn(270);
	ninja.forward(0.2 * L, 1);
	ninja.turn(270);
	ninja.forward(0.9 * L, 1);
	ninja.turn(120);
	ninja.forward(1 * L, 1);
	ninja.turn(60);
	ninja.forward(0.9 * L, 1);
	ninja.turn(270);
	ninja.forward(0.2 * L, 1);
	ninja.turn(270);
	ninja.forward(0.8 * L, 1);
	ninja.turn(120);
	ninja.forward(1 * L, 1);
	ninja.turn(330);
	ninja.forward(0.2 * L, 1);
	ninja.turn(30);
}

void drawFlake() {
	for (int i = 0; i < 6; i++) {
		flakemotif();
		cvs.scale2D(1.0, -1.0);
		flakemotif();
		cvs.scale2D(1.0, -1.0);
		cvs.rotate2D(60.0);
	}
}

void display(void)
{
	cvs.setBackgroundColor(1.0, 1.0, 1.0); //background color is white 
	cvs.clearScreen(); //clear screen
	cvs.setColor(1.0, 0.0, 0.0); //drawing color is red 
	cvs.setWindow(-80.0, 80.0, -80.0, 80.0);
	cvs.setViewport(20, 580, 20, 580);

	/*  flakemotif();
	  cvs.scale2D(1.0,-1.0);
	  flakemotif();
	  cvs.scale2D(1.0,-1.0);*/
	drawFlake();
	glFlush();
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, screenWidth, 0.0, screenHeight);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv)
{
	// the window is opened in the Canvas constructor
	glutInitWindowPosition(100,100);
	init();
	glutDisplayFunc(display);
	glutMainLoop();
}//end main