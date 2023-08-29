//#pragma once
//
//#include "pixMap.h"
//class Point2
//{
//public:
//	Point2() { x = y = 0.0f; } // constructor 1
//	Point2(float xx, float yy) { x = xx; y = yy; } // constructor 2
//	void set(float xx, float yy) { x = xx; y = yy; }
//	float getX() { return x; }
//	float getY() { return y; }
//	void draw(void)
//	{
//		glPointSize(2.0);
//
//		glEnable(GL_BLEND);
//		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//		glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
//		glEnable(GL_POINT_SMOOTH);
//
//		glBegin(GL_POINTS); // draw this point
//		glVertex2f((GLfloat)x, (GLfloat)y);
//		glEnd();
//
//		glDisable(GL_POINT_SMOOTH);
//
//	}// end draw
//private:
//	float x, y;
//}; // end class Point2
//
//
//
//
//class Mario
//{
//public:
//
//	RGBApixmap pix[5]; // make six empty pixmaps, one for each side of cube
//	enum State { STANDING, RUNNING1, RUNNING2, RUNNING3, JUMPING, DIE }state;
//	enum ModeType { STAY, RUN, R, JUMP, DEAD } mode;
//	float pos_X, pos_Y;
//
//	Mario(Point2 pos)
//
//	{
//
//
//
//	};
//
//	void setPosition(float x, float y)
//	{
//	}
//	void render();
//	void changeMode(ModeType m);
//	void run();
//	void die();
//
//
//	void changePosition(float dx, float dy)
//	{
//
//	}
//
//};
//
//void Mario::render()
//{
//
//
//}
//
//
//void Mario::run()
//{
//
//}
//
//
//
//
//void Mario::changeMode(ModeType m)
//{
//
//}