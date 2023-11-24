#include "Canvas.h"

#include <gl/glut.h>
#include <iostream>
#include <fstream>
#include <math.h>


#define M_PI  3.14157
using namespace std;

// display

Canvas cvs(800, 600, "Motifs drawing");

//void starmotif()
//{
//    glPushMatrix();
//    glBegin(GL_LINE_STRIP);
//    glLineWidth(2.0);
//    glVertex2i(3,3);
//    glVertex2i(0,8);
//    glVertex2i(-3, 0);
//    glVertex2i(-2, -1);
//    glVertex2i(0, 5);
//    glVertex2i(2, 3);
//    glVertex2i(3, 3);
//    glEnd();
//    glPopMatrix();
//}
//
//void flakeMotif()
//{
//    glPushMatrix();
//    glBegin(GL_LINE_STRIP);
//    glVertex2f(0.0f ,5.0f);
//    glVertex2f(20.0f, 5.0f);
//    glVertex2f(30.0f, 25.0f);
//    glVertex2f(35.0f,18.0f);
//    glVertex2f(25.0f, 5.0f);
//    glVertex2f(30.0f, 5.0f);
//    glVertex2f(45.0f, 15.0f);
//    glVertex2f(50.0f, 13.0f);
//    glVertex2f(35.0f, 5.0f);
//    glVertex2f(55.0f, 5.0f);
//    glVertex2f(60.0f, 0.0f);
//    glEnd();
//    glPopMatrix();
//}

void flakeMotif(Canvas& cvs) {

    // Move to the starting point.
    cvs.moveTo(8.0f, 5.0f);

    // Draw the flake motif using the Canvas's lineTo function.
    cvs.lineTo(20.0f, 5.0f);
    cvs.lineTo(30.0f, 25.0f);
    cvs.lineTo(35.0f, 18.0f);
    cvs.lineTo(25.0f, 5.0f);
    cvs.lineTo(30.0f, 5.0f);
    cvs.lineTo(45.0f, 15.0f);
    cvs.lineTo(50.0f, 13.0f);
    cvs.lineTo(35.0f, 5.0f);
    cvs.lineTo(55.0f, 5.0f);
    cvs.lineTo(60.0f, 0.0f);

}

void drawFlake() {
    for (int i = 0; i < 6; i++) {
        flakeMotif(cvs);
        cvs.scale2D(1.0, -1.0);
        flakeMotif(cvs);
        cvs.scale2D(1.0, -1.0);
        cvs.rotate2D(60.0);
    }
}

void starmotif() {

    cvs.moveTo(3.0f, 3.0f); // Move to the starting point
    cvs.lineTo(0.0f, 8.0f);
    cvs.lineTo(-3.0f, 0.0f);
    cvs.lineTo(-2.0f, -1.0f);
    cvs.lineTo(0.0f, 5.0f);
    cvs.lineTo(2.0f, 3.0f);
    cvs.lineTo(3.0f, 3.0f);
}

void drawStar()
{
    for (int i = 0; i < 5; i++)
    {
        starmotif();
        cvs.rotate2D(72.0);
    }
}

//>>>>>>>>>USE THIS DISPLAY FOR SNOWFLAKE<<<<<<<<<<<<<<
//void display(void)
//{
//    cvs.setBackgroundColor(1.0, 1.0, 1.0); //background color is white 
//    cvs.clearScreen(); //clear screen
//    cvs.setColor(1.0, 0.0, 0.0); //drawing color is red 
//    cvs.setWindow(-80.0, 80.0, -80.0, 80.0);
//    cvs.setViewport(20, 580, 20, 580);
//
//    drawFlake();
//    glFlush();
//}

//>>>>>>>>>USE THIS DISPLAY FOR STAR<<<<<<<<<<<<
void display(void)
{
    cvs.setBackgroundColor(1.0, 1.0, 1.0); //background color is white 
    cvs.clearScreen(); //clear screen
    cvs.setColor(1.0, 0.0, 0.0); //drawing color is red 
    cvs.setWindow(-10.0, 10.0, -10.0, 10.0);
    cvs.setViewport(10, 480, 10, 480);

    drawStar();
    glFlush();
}// end display

int main(int argc, char** argv)
{
    // the window is opened in the Canvas constructor
    glutDisplayFunc(display);
    glutMainLoop();
}//end main