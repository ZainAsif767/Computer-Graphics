#include <gl/glut.h>
#include <iostream>
#include <stdio.h>
#include <gl/RGBpixmap.h>
#include "Mario.h"

using namespace std;

int screenWidth = 640;
int screenHeight = 480;

class Point2
{
public:
	float x, y;

	void set(float dx, float dy)
	{
		x = dx;
		y = dy;
	}

	void set(Point2& p)
	{
		x = p.x;
		y = p.y;
	}

	Point2(float xx, float yy)
	{
		x = xx;
		y = yy;
	}

	Point2()
	{
		x = y = 0;
	}
};

class Mario {
public:
	RGBpixmap pix[5];
	enum state{STANDING,RUNNING1,RUNNING2,RUNNING3,JUMPING,DIE};
	enum ModeType{STAY,RUN,JUMP,DEAD};
	float pos_X, pos_Y;
	Mario() {

	}
	Mario(Point2 pos) {
		pix[0].readBMPFile("MarioJump.bmp");
		//pix[1].readBMPFile("MarioStanding.bmp");
		//pix[2].readBMPFile("MarioStanding.bmp");
		//pix[3].readBMPFile("MarioStanding.bmp");
		//pix[4].readBMPFile("MarioStanding.bmp");
		for (int i = 0; i < 5; i++) {
			pix[i].setChromakey(192, 192, 192);
			this->pos_X = getX();
			this->pos_Y = getY();
		}
	}
	void setPosition(float x, float y) {
		this->pos_X = x;
		this->pos_Y = y;
	}
	void render();

	void changeMode(modeType m);
	void run();
	void stay();
	void jump();
	void die();
};

void Mario:: render(
	{
		switch (mode) {
		case STAY:
			glRasterPos2i(this->pos_X, this->pos_Y)
				pix[0].mDraw();
			break;
		case RUN:
			run();
			break;
		case JUMP:
			//body
			break;
		case DEAD:
			//body
			break;
		}
	});

void Mario::run() {
	switch (state) {
	case RUNNING1:
		state = RUNNING2;
		break;
	case RUNNING2:
		state = RUNNING3;
		break;
	case RUNNING3:
		state = RUNNING1;
		break;
	}
}


//void changeMode(modeType m);
//void run();
//void stay;
//void jump();
//void die();

Mario m;

void myInit() {
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_EQUAL, 1.0);
	//changeMode(Mario::STAY);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0, screenWidth, 0, screenHeight);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void myKB_Handler(unsigned char key, int mx, int my)
{
	switch (key)
	{
	case 'r':

		break;
	}
	glutPostRedisplay();
}

void pressKeySpecial(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		m.setPosition(-20, 0);
		m.changeMode(Mario::RUN);
		break;

	case GLUT_KEY_RIGHT:
		m.setPosition(20, 0);
		m.changeMode(Mario::RUN);
		break;

	case GLUT_KEY_UP:
		if (m.pos_Y < 12)
			m.setPosition(4, 5);
		m.changeMode(Mario::JUMP);
		break;

	case GLUT_KEY_DOWN:

		break;
	}
	glutPostRedisplay();
}

void releaseKeySpecial(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:

		break;
	case GLUT_KEY_RIGHT:

		break;

	case GLUT_KEY_UP:
		if (m.pos_Y != 0) {
			m.setPosition(m.pos_X, 0);
			m.changeMode(Mario::STAY);
		}
		break;

	case GLUT_KEY_DOWN:

		break;
	}
	glutPostRedisplay();
}

void myDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m.render();
	glFlush();

}
void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("MY Mario");

	glutDisplayFunc(myDisplay);
	glutSpecialFunc(pressKeySpecial);
	glutSpecialUpFunc(releaseKeySpecial);
	glutKeyboardFunc(myKB_Handler);

	myInit();
	//glutIdleFunc(myDisplay);
	//glutTimerFunc(500, myTimer, 1);
}

