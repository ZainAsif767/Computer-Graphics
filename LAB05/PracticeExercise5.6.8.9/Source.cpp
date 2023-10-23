#include <gl/glut.h>
#include <iostream>
#include <math.h>

using namespace std;

int screenWidth = 740;
int screenHeight = 480;

class Turtle {
public:
	float x, y;
	float angle;
	Turtle() {
		this->x = 150;
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
		glColor3f(1.2, 1.0, 0.5);
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
		if (isVisible >= 1 ) {
			lineTo(x, y);

		}
		else {
			moveTo(x, y);
		}
	}
};

float increment = 3;
Turtle ninja;

// Practice Qustion 3.5.9
void PolySpiral(float dist) {
	if (dist > 200) {
		return;
	}
	ninja.forward(dist, 1);
	ninja.turn(-144);
	dist += increment;
	PolySpiral(dist + increment);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	// 3.5.5 Classes of Meanders 
	// part a 
	/* float L = 70.0;
	for (int i = 0; i < 3; i++) {
		ninja.forward(L, 1);
		ninja.turn(90);
		ninja.forward(L - 20, 1);
		ninja.turn(90);
		ninja.forward(L / 2,1);
		ninja.turn(270);
		ninja.forward(L/2, 1);
		ninja.turn(270);
		ninja.forward(L + 20, 1);
		ninja.turn(270);
		ninja.forward(L / 2, 1);
		ninja.turn(270);
		ninja.forward(L / 2, 1);
		ninja.turn(90);
		ninja.forward(L - 20, 1);
		ninja.turn(90);
		ninja.forward(L, 1);
	}*/

	// 3.5.5 part b
	float L = 70.0;	
	for (int i = 0; i < 3; i++) {
		ninja.forward(L, 1);
		ninja.turn(90);
		ninja.forward(L - 20, 1);
		ninja.turn(90);
		ninja.forward(L / 2, 1);
		ninja.turn(270);
		ninja.forward(L / 2, 1);
		ninja.turn(270);
		ninja.forward(L-20, 1);
		ninja.turn(270);
		ninja.forward(15, 1);
		ninja.turn(90);
		ninja.forward(25, 1);
		ninja.turn(90);
		ninja.forward(15, 1);
		ninja.turn(270);
		ninja.forward(L - 20, 1);
		ninja.turn(270);
		ninja.forward(L / 2, 1);
		ninja.turn(270);
		ninja.forward(L / 2, 1);
		ninja.turn(90);
		ninja.forward(L - 20, 1);
		ninja.turn(90);
		ninja.forward(L, 1);
	}

	// 3.5.8 . Is a Polyspiral an IFS ? (example 3.5.3) 
	/*float L = 80.0;
	for (int i = 0; i < 50; i++) {
		ninja.forward(L, 1);
		ninja.turn(-144);
		L += increment;
	}	*/

	// 3.5.9  Recursive form for Polyspiral()
	//PolySpiral(L);


	// 3.5.6  Drawing Elaborate Meanders.
	/*float L = 80.0;
	bool limitReached = false;
	for (int i = 0; i < 24; i++) {
		if (!limitReached && L == 0) {
			L = 10;
			ninja.forward(L, 1);
			ninja.turn(-90);
			limitReached = true;
		}
		if (!limitReached && L >= 10) {
			cout << i << L << endl;
			ninja.forward(L, 1);
			ninja.turn(90);
			cout << "curr-angle:" << ninja.angle << endl;
			L -= 10;
		}
		if (limitReached && L <= 80 + 10) {
			cout << i << L << endl;
			ninja.forward(L, 1);
			ninja.turn(-90);
			L += 10;
		}
	}*/
	glFlush();

}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Week 5 | 3.5.5 - 3.5.9");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, screenWidth, 0.0, screenHeight);
	glMatrixMode(GL_MODELVIEW);

	glutDisplayFunc(display);

	glutMainLoop();
	return 0;
}