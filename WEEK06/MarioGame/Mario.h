#pragma once 

#include <gl/glut.h>
#include "pixMap.h"
#include <stdio.h>
#include <iostream>
#include <gl/RGBpixmap.h>

using namespace std;

int screenWidth = 800;
int screenHeight = 500;

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
	RGBApixmap pix[10];// make 10 empty pixmaps, one for each side of cube
	enum State { STANDING1, STANDING2, RUNNING1, RUNNING2, RUNNING3, JUMPING, RUNNING4, RUNNING5, RUNNING6, JUMPINGLEFT } state;
	enum ModeType { STAY_RIGHT, STAY_LEFT, RUN_RIGHT, RUN_LEFT, JUMP, JUMPLEFT } mode;
	float pos_X, pos_Y;

	Mario(Point2 pos) {
		pix[0].readBMPFile("MarioStanding.bmp", 1);
		pix[1].readBMPFile("MarioStandingL.bmp", 1);
		pix[2].readBMPFile("MarioRun1.bmp", 1);
		pix[3].readBMPFile("MarioRun2.bmp", 1);
		pix[4].readBMPFile("MarioRun3.bmp", 1);
		pix[5].readBMPFile("MarioJump.bmp", 1);
		pix[6].readBMPFile("MarioRun4.bmp", 1);
		pix[7].readBMPFile("MarioRun5.bmp", 1);
		pix[8].readBMPFile("MarioRun6.bmp", 1);
		pix[9].readBMPFile("MarioJumpL.bmp", 1);

		for (int i = 0; i < 10; i++)
			pix[i].setChromaKey(192, 192, 192); //removing unnecessary bmp except mario

		this->pos_X = pos.getX();
		this->pos_Y = pos.getY();

		mode = Mario::STAY_RIGHT;
		state = Mario::STANDING1;

	}

	void setPosition(float x, float y) {
		this->pos_X = x;
		this->pos_Y = y;
	}

	void changePosition(float dx, float dy)
	{
		this->pos_X += dx;  this->pos_Y += dy;
		if (this->pos_X >= screenWidth) {
			setPosition(0, 0);
		}
		else if (this->pos_X < 0) {
			setPosition(screenWidth, 0);
		}
	}

	void render();
	void changeMode(ModeType m);
	void runRight();
	void runLeft();
	void stay();
	//void jump();
	//void die();
};

void Mario::render()
{
	switch (mode) {
	case STAY_RIGHT:
		glRasterPos2i(this->pos_X, this->pos_Y);
		pix[0].mDraw();
		break;
	case STAY_LEFT:
		glRasterPos2i(this->pos_X, this->pos_Y);
		pix[1].mDraw();
		break;
	case RUN_RIGHT:
		runRight();
		break;
	case RUN_LEFT:
		runLeft();
		break;
	case JUMP:
		glRasterPos2i(this->pos_X, this->pos_Y);
		pix[5].mDraw();
		break;
	case JUMPLEFT:
		glRasterPos2i(this->pos_X, this->pos_Y);
		pix[9].mDraw();
		break;
	}
};


void Mario::runRight() {
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
	changePosition(20, 0);
	glRasterPos2i(this->pos_X, this->pos_Y);
	pix[state].mDraw();
}

void Mario::runLeft() {
	switch (state) {
	case RUNNING4:
		state = RUNNING5;
		break;
	case RUNNING5:
		state = RUNNING6;
		break;
	case RUNNING6:
		state = RUNNING4;
		break;
	}
	changePosition(-20, 0);
	glRasterPos2i(this->pos_X, this->pos_Y);
	pix[state].mDraw();
}

void Mario::stay() {
	if (mode == RUN_RIGHT) {
		mode = STAY_RIGHT;
		state = STANDING1;
	}
	else if (mode == RUN_LEFT) {
		mode = STAY_LEFT;
		state = STANDING2;
	}
}

void Mario::changeMode(ModeType m) {
	if (mode == m)
		return;

	switch (m)
	{
	case STAY_RIGHT:
		state = STANDING1;
		break;
	case STAY_LEFT:
		state = STANDING2;
		break;
	case RUN_RIGHT:
		state = RUNNING1;
		break;
	case RUN_LEFT:
		state = RUNNING4;
		break;
	case JUMP:
		state = JUMPING;
		break;
	case JUMPLEFT:
		state = JUMPINGLEFT;
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
		m.changeMode(Mario::RUN_LEFT);
		break;
	case 'j':
		m.changeMode(Mario::JUMP);
		break;
	}
	glutPostRedisplay();
}

void pressKeySpecial(int key, int x, int y)
{
	
	if (key == GLUT_KEY_LEFT) {
		if (m.pos_Y == 0)
		{
			m.changePosition(-2, 0);
			m.changeMode(Mario::RUN_LEFT);
		}
	}
	else if (key == GLUT_KEY_RIGHT) 
	{
		if (m.pos_Y == 0) 
		{
			m.changePosition(2, 0);
			m.changeMode(Mario::RUN_RIGHT);
		}
	}
	else if (key == GLUT_KEY_UP)
	{
		if (m.mode == Mario::STAY_RIGHT || m.mode == Mario::RUN_RIGHT)
		{
			if (m.pos_Y < 12) 
			{
				m.changePosition(0, 50);
			}
			m.changeMode(Mario::JUMP);
		}
		else if (m.mode == Mario::STAY_LEFT || m.mode == Mario::RUN_LEFT)
		{
			if (m.pos_Y < 12)
			{
				m.changePosition(0, 50);
			}
			m.changeMode(Mario::JUMPLEFT);
		}
	}

	else if (key == (GLUT_KEY_UP && GLUT_KEY_RIGHT)) 
	{
		if (m.pos_Y < 12) 
		{
			m.changePosition(5, 50);
		}
		m.changeMode(Mario::JUMP);
	}

	else if (key == (GLUT_KEY_UP && GLUT_KEY_LEFT)) 
	{
		if (m.pos_Y < 12) 
		{
			m.changePosition(-5, 50);
		}
		m.changeMode(Mario::JUMPLEFT);
	}

	else if (key == GLUT_KEY_DOWN)
	{
		return;
	}
	glutPostRedisplay();
}

void releaseKeySpecial(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		m.stay();
		break;

	case GLUT_KEY_RIGHT:
		m.stay();
		break;

	case GLUT_KEY_UP:
		if (m.pos_Y != 0)
		{
			m.setPosition(m.pos_X, 0);
			if (m.mode == Mario::JUMP)
				m.changeMode(Mario::STAY_RIGHT);
			else if (m.mode == Mario::JUMPLEFT)
				m.changeMode(Mario::STAY_LEFT);
		}
		break;

	case GLUT_KEY_DOWN:
		
		break;
	}
	glutPostRedisplay();
}