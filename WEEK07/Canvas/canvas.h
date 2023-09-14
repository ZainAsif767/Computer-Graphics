#pragma once

#include <gl/glut.h>
class Point2
{
public:
    Point2() { x = y = 0.0f; } // constructor 1
    Point2(float xx, float yy) { x = xx; y = yy; } // constructor 2
    void set(float xx, float yy) { x = xx; y = yy; }
    float getX() { return x; }
    float getY() { return y; }
    void draw(void)
    {
        glBegin(GL_POINTS); // draw this point
        glVertex2f((GLfloat)x, (GLfloat)y);
        glEnd();
    }// end draw
private:
    float x, y;
}; // end class Point2

class IntRect
{
public:
    IntRect() { l = 0; r = 100; b = 0; t = 100; } // constructors
    IntRect(int left, int right, int bottom, int top)
    {
        l = left; r = right; b = bottom; t = top;
    } // constructors
    void set(int left, int right, int bottom, int top)
    {
        l = left; r = right; b = bottom; t = top;
    }
    int getl() { return l; }
    int getr() { return r; }
    int getb() { return b; }
    int gett() { return t; }
    void draw(void); // draw this rectangle using OpenGL
private:
    int l, r, b, t;
}; //end class IntRect:

void IntRect::draw(void)
{
    glBegin(GL_LINE_LOOP);
    glVertex2i(l, b);
    glVertex2i(r, b);
    glVertex2i(r, t);
    glVertex2i(l, t);
    glEnd();
}// end IntRect::draw

class RealRect
{
public:
    RealRect() { l = 0; r = 100; b = 0; t = 100; } // constructors
    RealRect(float left, float right, float bottom, float top)
    {
        l = left; r = right; b = bottom; t = top;
    } // constructors
    void set(float left, float right, float bottom, float top)
    {
        l = left; r = right; b = bottom; t = top;
    }
    float getl() { return l; }
    float getr() { return r; }
    float getb() { return b; }
    float gett() { return t; }
    void draw(void); // draw this rectangle using OpenGL
private:
    float l, r, b, t;
}; //end class RealRect:
void RealRect::draw(void)
{
    glBegin(GL_LINE_LOOP);
    glVertex2f(l, b);
    glVertex2f(r, b);
    glVertex2f(r, t);
    glVertex2f(l, t);
    glEnd();
}// end RealRect

class Canvas
{
public:
    Canvas(int width, int height, const char* windowTitle);// constructor
    void setWindow(float l, float r, float b, float t);
    // changed setViewport float to int
    void setViewport(int l, int r, int b, int t);
    void clearScreen();
    void setBackgroundColor(float r, float g, float b);
    void setColor(float r, float g, float b);


    IntRect getViewport(void); // divulge or make known the viewport data
    RealRect getWindow(void); // divulge or make known the window data


    float getWindowAspectRatio(void);
    float getCP_X(void);
    float getCP_Y(void);


    void moveTo(float x, float y);
    void moveTo(Point2 p);

    void lineTo(float x, float y);
    void lineTo(Point2 p);


    // others later
private:
    Point2 CP; // current position in the world
    IntRect viewport; // the current viewport
    RealRect window; // the current window
}; // end class Cavas

//************************ End of file "canvas.h" ***************************




Canvas::Canvas(int width, int height, const char* windowTitle)// constructor
{
    char* argv[1]; // dmmy argument list for glutInit()
    char dummyString[8];
    argv[0] = dummyString; // hook up the pointer
    int argc = 1; // to satisfy glutInit()

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(20, 20);
    glutCreateWindow(windowTitle); // open the screen window
    setWindow(0, (float)width, 0, (float)height); //default world window
    setViewport(0, width, 0, height); //default viewport
    CP.set(0.0f, 0.0f); //initialize the CP to (0,0)
}//end Canvas constructor

void Canvas::setWindow(float l, float r, float b, float t)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(l, r, b, t); //set the world window
}// end setWindow

// Changed float to int in void Canvas
void Canvas::setViewport(int l, int r, int b, int t)
{
    glViewport(l, b, r - l, t - b);
} // end setViewport


void Canvas::clearScreen()
{
    glClear(GL_COLOR_BUFFER_BIT);
}// clearScreen

void Canvas::setBackgroundColor(float r, float g, float b)
{
    glClearColor(r, g, b, 0.0);
}// end setBackgroundColor

void Canvas::setColor(float r, float g, float b)
{
    glColor3f(r, g, b);
}//edn setColor

void Canvas::moveTo(float x, float y)
{
    CP.set(x, y); // Set the current position to the specified point
}

void Canvas::moveTo(Point2 p)
{
    CP = p; // Set the current position to the specified point
}

void Canvas::lineTo(float x, float y)
{
    glColor3f(0.0, 0.4, 0.6);
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glVertex2f(CP.getX(), CP.getY()); // Start from the current position
    glVertex2f(x, y); // Draw a line to the specified point
    glEnd();

    // Update the current position to the end of the line
    CP.set(x, y);
}

void Canvas::lineTo(Point2 p)
{
    glColor3f(0.0, 1.0, 0.7);
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glVertex2f(CP.getX(), CP.getY()); // Start from the current position
    glVertex2f(p.getX(), p.getY()); // Draw a line to the specified point
    glEnd();

    // Update the current position to the end of the line
    CP = p;
}



