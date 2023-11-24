#include <gl/glut.h>
#include <iostream>
#include <math.h>

using namespace std;

int screenWidth = 640;
int screenHeight = 480;
class GLintPoint{
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
	float angle;
	Turtle() {
		this->x = 225;
		this->y = 200;
	}
	void turnTo(float angle) {
		this->angle = angle;
	}
	void turn(float angle) {
		this->angle += angle;
	}
	void lineTo(float x, float y) {
		float t_x = x; float t_y = y;
		glColor3f(1.0, 0.0, 0.0);
		glLineWidth(2.0);
		glBegin(GL_LINES);
		glVertex2f(this->x, this->y);
		glVertex2f(x, y);
		glEnd();
		glFlush();
		moveTo(t_x, t_y);
	}
	void moveTo(float x, float y) {
		this->x = x;
		this->y = y;

	}
	
	void forward(float dist, int isVisible) {
		const float RadPerDeg = 0.017453393;
		float x = this->x + dist * cos(RadPerDeg * this->angle);
		float y = this->y + dist * sin(RadPerDeg * this->angle);
		if (isVisible >= 1) {
			lineTo(x, y);

		}
		else {
			moveTo(x, y);
		}
	}
	
};


float increment = 3;
Turtle turtle;

void init() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	 //3.5.1 Drawing Turtles Figure
	 //part (a)
	/*float L = 200.0;
	for (int j = 0; j < 4; j++) {

		for (int i = 0; i < 4; i++) {
			turtle.forward(L, 1);
			turtle.turn(90);
			turtle.forward(L, 1);
			turtle.turn(90);
			turtle.forward(L, 1);
			turtle.turn(90);
		}
		L -= 40;
	}*/

	//3.5.1 part (b)
	/*float L = 200.0;
	for (int j = 0; j < 4; j++) {

		turtle.forward(L, 1);
		turtle.turn(90);
		turtle.forward(L, 1);
		turtle.turn(90);
		L -= 20;
		turtle.forward(L, 1);
		turtle.turn(90);
		turtle.forward(L, 1);
		turtle.turn(90);
		L -= 20;
	}*/

	// 3.5.1 part (c)
	/*float L = 200.0;
	turtle.forward(L, 1);
	turtle.turn(120);
	turtle.forward(L / 2, 1);
	turtle.turn(120);
	turtle.forward(L / 2, 1);
	turtle.turn(240);
	turtle.forward(L / 2, 1);
	turtle.turn(240);
	turtle.forward(L / 2, 1);
	turtle.turn(120);
	turtle.forward(L / 2, 1);
	turtle.turn(120);
	turtle.forward(L, 1);*/


	// 3.5.2 Drawing a well-known logo
	/*float L = 100.0;
	turtle.forward(L, 1);
	turtle.turn(320);
	turtle.forward(L, 1);
	turtle.turn(220);
	turtle.forward(L, 1);
	turtle.turn(320);
	turtle.forward(L, 1);

	turtle.turn(40);

	turtle.forward(L, 1);
	turtle.turn(40);
	turtle.forward(L, 1);
	turtle.turn(140);
	turtle.forward(L, 1);
	turtle.turn(40);
	turtle.forward(L * 2, 1);

	turtle.turn(90);
	turtle.forward(L, 1);
	turtle.turn(100);
	turtle.forward(L, 1);
	turtle.turn(80);
	turtle.forward(L, 1);*/

	turtle.forward(100, 0);

	// 3.5.3 Driving the turtle with strings
	string input = "FLFLFLFRFLFLFLFRFLFLFLFR";
	for (char key : input) {
		switch (key) {
		case 'F':
			turtle.forward(30, 1);
			break;
		case 'L':
			turtle.turn(60);
			break;
		case 'R':
			turtle.turn(-60);
			break;
		}
	}
	glFlush();
}

 //3.5.3 Driving the turtle with strings
void myKeys(unsigned char key, int x, int y) {
    int L = 30;
	switch (key) {
	case 'f':
		turtle.forward(L, 1);
		break;
	case 'l':
		turtle.turn(60);
		break;
	case 'r':
		turtle.turn(-60);
		break;
	}
	
}
int main(int argc, char** argv) {
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
		glutInitWindowSize(screenWidth, screenHeight);
		glutInitWindowPosition(100, 100);
		glutCreateWindow("Practice Exercise 3.5.1-3.5.3");

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0.0, screenWidth, 0.0, screenHeight);
		glMatrixMode(GL_MODELVIEW);

		glutDisplayFunc(display);
		glutKeyboardFunc(myKeys);

		init();
		glutMainLoop();
		return 0;
}
