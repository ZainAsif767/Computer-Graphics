#include <gl/glut.h>
#include <iostream>
#include <math.h>

using namespace std;

int screenWidth = 640;
int screenHeight = 440;
class GLintPoint
{
public:
	GLint x, y;
};

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

class Turtle {
private:
	int CD = 90;
	Point2 CP;
public:
	float x, y;
	float angle; // also called CD - Current Direction
	Turtle() {
		//this->x = 220;
		//this->y = 240;
		CP.set(220, 240);
	}
	Turtle(Point2 currPoss) {
		CP.set(currPoss);
	}
	void turnTo(float angle) {
		this->angle = angle;
	}
	void turn(float angle) {
		this->angle += angle;
	}
	/*void lineTo(float x, float y) {
		float t_x = x; float t_y = y;
		glColor3f(0.0, 1.0, 1.0);
		glLineWidth(2.0);
		glBegin(GL_LINES);
		glVertex2f(this->x, this->y);
		glVertex2f(x, y);
		glEnd();
		glFlush();
		moveTo(t_x, t_y);
	}*/
	void moveTo(Point2 p)
	{
		CP.set(p);
	}

	void lineTo(Point2 p)
	{
		glBegin(GL_LINES);
		glVertex2f(CP.x, CP.y);
		glVertex2f(p.x, p.y);
		glEnd();
		glFlush();
		CP.set(p);
	}
	/*void moveTo(float x, float y) {
		this->x = x;
		this->y = y;

	}*/

	void moveRel(float dx, float dy) {
		CP.set(CP.x + dx, CP.y + dy);
	}

	void lineRel(float dx, float dy) {
		glColor3f(0.0, 1.0, 1.0);
		glLineWidth(3.0);
		glBegin(GL_LINES);
		glVertex2f(CP.x, CP.y);
		Point2 p2(CP.x + dx, CP.y + dy);
		glVertex2f(p2.x, p2.y);
		glEnd();
		glFlush();
		CP.set(p2);
	}

	void forward(float dist, int isVisible) {
		const float RadPerDeg = 0.017453393;
		float x = this->x + dist * cos(RadPerDeg * this->angle);
		float y = this->y + dist * sin(RadPerDeg * this->angle);
		if (isVisible >= 1) {
			lineRel(x, y);

		}
		else {
			moveRel(x, y);
		}
	}

};

float L = 50.0;
Turtle ninja;

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	// 3.5.2 (Example Motif)
	//for part(a) set i < 1, for part(b) set i < 4
	for (int i = 0; i < 4; i++) {
		ninja.forward(3 * L, 1);
		ninja.turn(90);
		ninja.forward(L, 1);
		ninja.turn(90);
		ninja.forward(L, 1);
		ninja.turn(90);
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Exmaple 3.5.2");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, screenWidth, 0.0, screenHeight);
	glMatrixMode(GL_MODELVIEW);

	glutDisplayFunc(display);

	glutMainLoop();
	return 0;
}