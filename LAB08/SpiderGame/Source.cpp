#include <iostream>
#include <Windows.h>
#include <gl/glut.h>
#include "math.h"
#include "pixMap.h"
#include "Spider.h"
#include "vector"


int width = 680;
int height = 440;

void myinit(void);
void draw_bullet(float x, float y);

void pressKeySpecial(int key, int x, int y);
void releaseKeySpecial(int key, int x, int y);

//Global variables for sprite SPIDER
float posx = 0.0f;
float posy = 0.0f;

bool isMoving = true; // indicate the spider is still alive 
float s1 = 400.0f;
RGBApixmap pix[3];


Spider spider(Point2(0.0, 0.0));


//Global variables for sprite BULLET
float bullet_posx = 0.0f;	// center
float bullet_posy = -height / 2 + 25;   	// bottom
float bullet_horizontal_velocity = 50.0f; // does not move
float bullet_speed = 1000.0f;
bool isFiring = false;	// true when firing
static int K = 0;

int random(int min, int max) //range : (min, max)
{
	static bool first = true;
	if (first)
	{
		srand(NULL); //seeding for the first time only!
		first = false;
	}
	return min + rand() % (max - min);
}
void myinit()
{
	glClearColor(1, 1, 1, 0);  //Set the clear color to white
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-width / 2, width / 2, -height / 2, height / 2);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_EQUAL, 1.0);

	pix[0].readBMPFile("spider.bmp", 1);
	pix[1].readBMPFile("splash.bmp", 1);


}int i = 0;
void pressKeySpecial(int key, int x, int y) {

	if (key == GLUT_KEY_LEFT)
	{
		bullet_horizontal_velocity = -200.0f;
		K = 1;
	}
	//move right
	if (key == GLUT_KEY_RIGHT)
	{
		bullet_horizontal_velocity = 200.0f;
		K = 1;

	}
	if (key == GLUT_KEY_UP) 
	{
		isFiring = true;
		PlaySound(L"shoot.wav", NULL, SND_ASYNC | SND_FILENAME );
	}
	glutPostRedisplay();
}

//stop moving when release key
void releaseKeySpecial(int key, int x, int y) {

	if (key == GLUT_KEY_LEFT) {
		bullet_horizontal_velocity = .0f;
	}

	if (key == GLUT_KEY_RIGHT) {
		bullet_horizontal_velocity = .0f;
	}
	glutPostRedisplay();
}


void draw_bullet(float x, float y)
{
	glPushMatrix();

	glColor3f(.5, .4, .0);	// the head
	glBegin(GL_TRIANGLES);
	glVertex2f(x, y);
	glVertex2f(x - 3, y - 5);
	glVertex2f(x + 3, y - 5);

	glEnd();

	glBegin(GL_POLYGON);	// the shell
	glVertex2f(x + 3, y - 5);
	glVertex2f(x - 3, y - 5);
	glVertex2f(x - 3, y - 15);
	glVertex2f(x + 3, y - 15);
	glEnd();
	glPopMatrix();
}

void drawTrajectory(float x, float y) {
	static std::vector<std::pair<float, float>> trajectoryPoints; // Store trajectory points

	// Store current position in the trajectoryPoints vector
	trajectoryPoints.push_back(std::make_pair(x, y));

	// Limit the number of points to prevent excessive memory usage
	if (trajectoryPoints.size() > 5000) {
		trajectoryPoints.erase(trajectoryPoints.begin());
	}

	if (!isMoving) {
		trajectoryPoints.clear();
	}

	// Draw the trajectory as a line
	glColor3f(0.5, 0.5, 1.0);
	glBegin(GL_LINE_STRIP);
	for (const auto& point : trajectoryPoints) {
		glVertex2f(point.first, point.second);
	}
	glEnd();
	glLineWidth(2.0);
}

void drawSpider(float posx, float posy)
{
	glRasterPos2f(posx, posy);
	pix[0].mDraw();
	//glDrawPixels(pix[0].nRows, pix[0].nCols, GL_RGBA, GL_UNSIGNED_BYTE, pix[0].pixel);
}
float gettime()
{
	static __int64 i64Frequency = 0;
	static __int64 i64BeginCount = 0;
	if (i64Frequency == 0) {	// do this only for the first time
		QueryPerformanceFrequency((LARGE_INTEGER*)&i64Frequency);
		QueryPerformanceCounter((LARGE_INTEGER*)&i64BeginCount); //retrieve the number of
		//ticks since system start (64bit int).

	}
	__int64 i64CurrentCount;
	QueryPerformanceCounter((LARGE_INTEGER*)&i64CurrentCount);
	return  (float)(i64CurrentCount - i64BeginCount) / i64Frequency;
}

static int a = 1;

void move()
{
	static float prevtime = 0.0f;	// previous frame’s time
	float currtime = gettime();		// current frame’s time
	float elapsedtime = currtime - prevtime;	// elapsed time
	static float Ф = 0;
	float speed = 250.0f;
	static float movebearing = 0.0f;
	float dx = speed * cosf(Ф) * elapsedtime;
	float dy = speed * sinf(Ф) * elapsedtime;

	if (isMoving == true)
	{
		posx += dx;
		posy += dy;
		//Ф = Ф + rand() - 1 + 1;
		if (posx < -width / 2)
		{
			posx = -width / 2;
			Ф = Ф + 180;// (to Reverse moving Direction)
		}

		if (posx > width / 2 - 32)
		{
			posx = width / 2 - 32;
			Ф = Ф + 180;
		}
		if (posy < -height / 2)
		{
			posy = -height / 2;
			Ф = Ф + 180;// (to Reverse moving Direction)
		}
		if (posy > height / 2 - 32)
		{
			posy = height / 2 - 32;
			Ф = Ф + 180;
		}
	}

	if (isFiring == true)
	{

		float bullet_speed = 4.0f;
		bullet_posy = bullet_posy + bullet_speed;

		if (bullet_posy > height / 2 + 15)
		{
			glRasterPos2f(-width / 2, height / 2 - 35);

			glutSwapBuffers();
			Sleep(500);
			bullet_posy = -height / 2 + 15;
			isFiring = false;
		}
		if (abs(bullet_posx - (posx + 34)) < 34 && abs((bullet_posy - 20) - (64 + posy)) < 64)
		{
			isMoving = false;

		}
	}

	if (isMoving == false)
	{
		isFiring = false;
		bullet_posy = -height / 2 + 25;
		glRasterPos2f(posx, posy);  // position, in world coordinate
		pix[0].mDraw();
		glRasterPos2f(posx, posy);
		pix[1].mDraw();
		glFlush();
		glEnd();
		drawTrajectory(posx, posy);
		glutSwapBuffers();
		Sleep(1000);
		isMoving = true;

	}
	//  Calculate dx dy for spider either by changing theta randomly or
	//  by changing rate of theta randomly
	//  Update Posx,Posy for spider
	//  Perform boundary check so spiders couldn't escape from world window
	//  reverse the direction of spider when it hits world boundary

	/********************************************************/
	
	/**************Do all this stuff here if bullet is firing****************/
	
	if (K == 1)
	{
		bullet_posx += bullet_horizontal_velocity * (elapsedtime);
		bullet_posx = max(-width / 2 + 5, min(width / 2 - 5, bullet_posx));
	}

	//update bullets y bc it only fires vertically
	// check if bullet move out of windo  fire ends
	/********************************************************/

	// Finally perform collision detection i.e postion of bullet and spider collapse or 
	// the the difference b/w the bullet position and spider positon < 2 pixels

	if (isMoving == true)
		glutPostRedisplay();
	prevtime = currtime;
}


void reshape(int w, int h)		// called whenever the
{					// window is resized
	width = w;
	height = h;
	bullet_posy = -(height / 2) + 13; //update bullet y position upon reshape

	glViewport(0, 0, w, h);			// use the entire window
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-w / 2, w / 2, -h / 2, h / 2);	// maintain unit-pixel proj.
	glMatrixMode(GL_MODELVIEW);
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer
	drawTrajectory(posx, posy);
	drawSpider(posx, posy);
	draw_bullet(bullet_posx, bullet_posy);

	glutSwapBuffers();
}


int  main(int argc, char** argv)
{
	glutInit(&argc, argv);          // Initialize GLUT function callings

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	// Set window size (width, height) in number of pixels  	
	glutInitWindowSize(width, height);

	// Specify window position, from the left and top of the screen,
	glutInitWindowPosition(200, 100);        // in numbers of pixels 

	// Specify a window creation event 
	glutCreateWindow("Spider Game");

	myinit();
	glutDisplayFunc(display);
	glutIdleFunc(move);
	glutReshapeFunc(reshape);
	glutSpecialFunc(pressKeySpecial);
	glutSpecialUpFunc(releaseKeySpecial);
	glutMainLoop();

	return 0;
}