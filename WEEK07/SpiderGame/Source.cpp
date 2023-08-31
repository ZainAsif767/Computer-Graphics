#include <gl/glut.h>
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <gl/RGBpixmap.h>
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

class Spider {
private:
	RGBApixmap pix[2];
	enum State { DIE } state;
	float pos_X, pos_Y;
public:
	bool isMoving;
	float spiderSpeed;
	float theta;
	float rateOfChange;

	Spider(){}

	Spider(Point2 pos) {
		isMoving = true;
		spiderSpeed = 400.0f;
		theta = 0.0;
		rateOfChange = 1.0;
		this->pos_X = pos.getX();
		this->pos_Y = pos.getY();

		string fname[2] = { "nameofimage1.bmp", "nameofimage2.bmp" }; // Replace with actual image filenames
		for (int i = 0; i < 2; i++) {
			pix[i].readBMPFile(fname[i], 1);
			pix[i].setChromaKey(192, 192, 192);
		}
	}

	void changePosition(float dx, float dy)
	{
		this->pos_X += dx;  this->pos_Y += dy;
	}

	void die();
	void render();
};

void Spider::render() {
	glRasterPos2f(this->pos_X, this->pos_Y);

	if (this->isMoving) {
		pix[0].mDraw();
	}
	else {
		pix[1].mDraw();
	}
}

Spider spider(Point2(0, 0));

void myDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	spider.render();
	glFlush();
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

}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Spider Game");

	glutDisplayFunc(myDisplay);
	//PlaySound(L"MarioSong.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	//glutSpecialFunc(pressKeySpecial);
	//glutSpecialUpFunc(releaseKeySpecial);
	//glutKeyboardFunc(myKB_Handler);

	myInit();
	//glutIdleFunc(myDisplay);
	//spinner(50); // sets timer for mario to keep running
	glutMainLoop();
}