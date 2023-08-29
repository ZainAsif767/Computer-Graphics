#include <gl/glut.h>
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <gl/RGBpixmap.h>
//#include "Mario.h"
#include "pixMap.h"

using namespace std;

int screenWidth = 640;
int screenHeight = 480;

class Point2
{
public:
	// constructor 1
	Point2()
	{ 
		x = y = 0.0f;
	} 
	// constructor 2
	Point2(float xx, float yy)
	{ 
		x = xx;
		y = yy;
	}
	void set(float xx, float yy) 
	{ 
		x = xx;
		y = yy;
	}
	float getX() { return x; }
	float getY() { return y; }
	void draw(void)
	{
		glPointSize(2.0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
		glEnable(GL_POINT_SMOOTH);

		glBegin(GL_POINTS); // draw this point
		glVertex2f((GLfloat)x, (GLfloat)y);
		glEnd();

		glDisable(GL_POINT_SMOOTH);

	}// end draw
private:
	float x, y;
}; // end class Point2


class Mario {	
public:
	RGBApixmap pix[5];// make six empty pixmaps, one for each side of cube
	enum State {STANDING,RUNNING1,RUNNING2,RUNNING3,JUMPING,DIE} state;
	enum ModeType{STAY,RUN,JUMP,DEAD} mode;
	float pos_X, pos_Y;
	
	Mario(Point2 pos) {	
		pix[0].readBMPFile("MarioStanding.bmp",1);
		pix[1].readBMPFile("MarioRun1.bmp",1);
		pix[2].readBMPFile("MarioRun2.bmp",1);
		pix[3].readBMPFile("MarioRun3.bmp",1);
		pix[4].readBMPFile("MarioJump.bmp",1);

		for (int i = 0; i < 5; i++) 
			pix[i].setChromaKey(192, 192, 192); //removing unnecessary bmp except mario
		
		this->pos_X = pos.getX();
		this->pos_Y = pos.getY();
		
	}

	void setPosition(float x, float y) {
		this->pos_X = x;
		this->pos_Y = y;
	}
	
	void changePosition(float dx, float dy)
	{
		this->pos_X += dx;  this->pos_Y += dy;
	}

	void render();
	void changeMode(ModeType m);
	void run();
	void stay();
	void jump();
	void die();
};

void Mario::render()
	{
		switch (mode) {
		case STAY:
			glRasterPos2i(this->pos_X, this->pos_Y);
			pix[0].mDraw();
			break;
		case RUN:
			run();
			break;
		case JUMP:
			glRasterPos2i(this->pos_X, this->pos_Y);
			pix[4].mDraw();
			break;
		case DEAD:
			//body
			break;
		}
	};

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
	changePosition(20,0);
	glRasterPos2i(this->pos_X,this->pos_Y);
	pix[state].mDraw();
}

void Mario::changeMode(ModeType m) {
	if (mode == m)
		return;

	switch (m)
	{
	case STAY:
		state = STANDING;
		break;
	case RUN:
		state = RUNNING1;
		break;
	case JUMP:
		state = JUMPING;
		break;
	}
	mode = m;
}

Mario m(Point2(0, 0));


void myKB_Handler(unsigned char key, int mx, int my)
{
	switch (key)
	{
	case 'r':
		m.changeMode(Mario::RUN);
		break;
	case 'j':
		m.changeMode(Mario::JUMP);
		break;
	}
	glutPostRedisplay();
}

void pressKeySpecial(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		//m.setPosition(-40, 0); // shows animation and sets position but do not change position
		m.changePosition(-40, 0);
		m.changeMode(Mario::RUN);
		break;

	case GLUT_KEY_RIGHT:
		//m.setPosition(20, 0);
		m.changePosition(20, 0);
		m.changeMode(Mario::RUN);
		break;

	case GLUT_KEY_UP:
		if (m.pos_Y < 12)
			//m.setPosition(4, 5);
			m.changePosition(4, 15);
		m.changeMode(Mario::JUMP);
		break;

	case GLUT_KEY_DOWN:
		//m.setPosition(0, -20); // Move Mario downwards
		//m.changeMode(Mario::RUN); // Change the mode to running
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
		if (m.pos_Y != 0)
		{
			m.setPosition(m.pos_X, 0);
			m.changeMode(Mario::STAY);
		}
		break;

	case GLUT_KEY_DOWN:

		break;
	}
	glutPostRedisplay();
}

void myInit(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

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

	m.changeMode(Mario::STAY);
}

void myDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m.render();
	glFlush();
}

void spinner(int t)
{
	glutPostRedisplay();
	glutTimerFunc(500, spinner, t);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("My Mario");

	glutDisplayFunc(myDisplay);
	PlaySoundW(L"MarioSong.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	glutSpecialFunc(pressKeySpecial);
	glutSpecialUpFunc(releaseKeySpecial);
	glutKeyboardFunc(myKB_Handler);

	myInit();
	//glutIdleFunc(myDisplay);
	//spinner(50); // sets timer for mario to keep running
	glutMainLoop();
}

