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
	enum State { ALIVE, DEAD } state;
	RGBApixmap pix[2];
public:
	float pos_X, pos_Y;
	bool isMoving;
	float spiderSpeed;
	float theta;
	float rateOfChange;

	Spider() {}

	Spider(Point2 pos) {
		isMoving = true;
		spiderSpeed = 400.0f;
		theta = 0.0;
		rateOfChange = 1.0;
		this->pos_X = pos.getX();
		this->pos_Y = pos.getY();

		string fname[2] = { "spider.bmp", "mak3.bmp" }; // Replace with actual image filenames
		for (int i = 0; i < 2; i++) {
			pix[i].readBMPFile(fname[i], 1);
			pix[i].setChromaKey(255, 255, 255);
		}
	}
	void setState(int i) {
		if (i == 1)
			this->state = DEAD;
		else {
			this->state = ALIVE;
		}
	}

	int getState() {
		if (this->state == DEAD) {
			return 1;
		}
		return 0;
	}

	void changePosition(float dx, float dy)
	{
		this->pos_X += dx;  this->pos_Y += dy;
	}
	
	void die();
	void render();
};

void Spider::die() {
	this->isMoving = false;
	this->state = DEAD;
}


void Spider::render() {
	glRasterPos2f(this->pos_X, this->pos_Y);

	if (this->isMoving) {
		pix[0].mDraw();
	}
	else {
		pix[1].mDraw();
		cout << "Spider is dead!" << endl;
	}
}

Spider spider(Point2(300, 220));

bool isBulletFired = false;
bool isBulletMoving = false;
float bulletX = screenWidth / 2;
float bulletY = 40.0f;
float bulletSpeed = 5.0f;



void updateBullet() {
	if (isBulletMoving) {
		bulletY += bulletSpeed;

		if (bulletY >= screenHeight) {
			isBulletMoving = false;
		}
	}
}

class Bullet {
public:
	float x, y;
	Bullet(float initialX, float initialY) : x(initialX), y(initialY) {};

	void render()
	{
		glPushMatrix();
		glTranslatef(x, y, 0.0);

		glColor3f(0.5, 0.1, 0.2);
		glBegin(GL_TRIANGLES);
		glVertex2f(0, 0);
		glVertex2f(-3, -5);
		glVertex2f(3, -5);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(3, -5);
		glVertex2f(-3, -5);
		glVertex2f(-3, -15);
		glVertex2f(3, -15);
		glEnd();
		glPopMatrix();
	};

	void setPosition(float x, float y) {
		this->x = x;
		this->y = y;
	}

	void changePosition(float dx, float dy) {
		x += dx;
		y += dy;
	};
};

Bullet bullet(bulletX, bulletY);

void myKB_Handler(unsigned char key, int mx, int my)
{
	switch (key)
	{
	case ' ':
		if (!isBulletFired) {
			isBulletFired = true;
			isBulletMoving = true;
			bullet.changePosition(0, 20);
		}
		break;
	}
	glutPostRedisplay();
}

void bullet_movement(int y) {
	bullet.changePosition(0, 20);
	glutPostRedisplay();
	if ((bullet.x >= 300 && bullet.x <= 396) && (bullet.y >= 220 && bullet.y <= 316)) {
		bullet.setPosition(bulletX, 20);
		spider.die();
		glutPostRedisplay();
		isBulletMoving = false;
	}
	if (bullet.y < 480 && isBulletMoving) {
		glutTimerFunc(5, bullet_movement, y);
	}
	else if (bullet.y >= 480) {
		bullet.setPosition(bulletX, 20);
		glutPostRedisplay();
	}
}

void pressKeySpecial(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP:
		cout << "Bullet Moving" << isBulletMoving << endl;
		if (isBulletMoving) {

		}
		else {
			isBulletMoving = true;
		if (spider.getState() == 1) {
			spider.setState(0);
			spider.isMoving = true;
			spider.render();
		}
		isBulletMoving = true;
		isBulletFired = true;
		bullet_movement(0);
		}
		break;
	}
}


void releaseKeySpecial(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_UP:
		break;

	case ' ':
		break;
	}

	glutPostRedisplay();
}


void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	updateBullet();

	spider.render();
	bullet.render();
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
	glutSpecialFunc(pressKeySpecial);
	glutSpecialUpFunc(releaseKeySpecial);
	glutKeyboardFunc(myKB_Handler);

	myInit();
	//glutIdleFunc(myDisplay);
	//bullet_movement(50); 
	glutMainLoop();
}