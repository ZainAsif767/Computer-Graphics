#include "canvas.h"

#include <gl/glut.h>
#include <iostream>
#include <fstream>
#include <math.h>


#define M_PI  3.14157

// display

//using namespace std;

Canvas cvs(640, 480, "Test Canvas by Zain 172");

void drawSun()
{
    // Draw the sun (a yellow circle)
    cvs.setColor(1.0, 1.0, 0.0); // Yellow color for the sun
    cvs.moveTo(0.0, 0.0);
    const float sunRadius = 4.0;
    const int numSegments = 100;
    for (int i = 0; i <= numSegments; ++i) {
        float theta = 2.0 * M_PI * float(i) / float(numSegments);
        float x = sunRadius * cos(theta);
        float y = sunRadius * sin(theta);
        cvs.lineTo(x, y);
    }

    // Draw the smiling face (two black dots for eyes and a curved line for the mouth)
    cvs.setColor(0.0, 0.0, 0.0); // Black color for the eyes and mouth

    // Left eye
    cvs.moveTo(-1.0, 1.0);
    cvs.lineTo(-0.5, 1.5);

    // Right eye
    cvs.moveTo(1.0, 1.0);
    cvs.lineTo(0.5, 1.5);

    // Mouth (a simple smile)
    cvs.moveTo(-1.5, -1.0);
    for (int i = 0; i <= 180; ++i) {
        float theta = i * M_PI / 180.0;
        float x = -1.5 + 0.5 * cos(theta);
        float y = -1.0 + 0.5 * sin(theta);
        cvs.lineTo(x, y);
    }
}

void drawSmiley()
{
    // Draw the face (a circle)
    cvs.setColor(1.0, 1.0, 0.0); // Yellow color for the face
    cvs.moveTo(0.0, 0.0);
    const float radius = 5.0;
    const int numSegments = 100;
    for (int i = 0; i <= numSegments; ++i) {
        float theta = 2.0 * M_PI * float(i) / float(numSegments);
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        cvs.lineTo(x, y);
    }

    // Draw the left eye (a smaller circle)
    cvs.moveTo(-2.0, 3.0);
    cvs.setColor(0.0, 0.0, 0.0); // Black color for the eyes
    const float eyeRadius = 0.5;
    for (int i = 0; i <= numSegments; ++i) {
        float theta = 2.0 * M_PI * float(i) / float(numSegments);
        float x = -2.0 + eyeRadius * cos(theta);
        float y = 3.0 + eyeRadius * sin(theta);
        cvs.lineTo(x, y);
    }

    // Draw the right eye (another smaller circle)
    cvs.moveTo(2.0, 3.0);
    for (int i = 0; i <= numSegments; ++i) {
        float theta = 2.0 * M_PI * float(i) / float(numSegments);
        float x = 2.0 + eyeRadius * cos(theta);
        float y = 3.0 + eyeRadius * sin(theta);
        cvs.lineTo(x, y);
    }

    // Draw the mouth 
    cvs.moveTo(-2.0, -1.0);
    const float mouthRadius = 2.0;
    for (int i = -45; i <= 45; ++i) {
        float theta = i * M_PI / 180.0;
        float x = mouthRadius * cos(theta);
        float y = -1.0 + mouthRadius * sin(theta);
        cvs.lineTo(x, y);
    }
}

void drawStar()
{
    // Set drawing color to blue
    cvs.setColor(0.0, 1.0, 1.0);

    // Move to the starting point
    cvs.moveTo(0.0, 0.0);

    // Draw the star
    for (int i = 0; i < 5; ++i) {
        cvs.lineTo(cos(72 * i * M_PI / 180) * 5, sin(72 * i * M_PI / 180) * 5);
        cvs.lineTo(cos((72 * i + 36) * M_PI / 180) * 2, sin((72 * i + 36) * M_PI / 180) * 2);
    }
}


void display(void)
{
    cvs.setBackgroundColor(1.0, 1.0, 1.0); //background color is white 
    cvs.clearScreen(); //clear screen

    cvs.setColor(0.0, 1.0, 0.0); //drawing color is red 
    cvs.setWindow(-10.0, 10.0, -10.0, 10.0);
    cvs.setViewport(10, 460, 10, 460);

    // ***************PRACTICING Simple Line DRAWING************//
     drawStar();
    drawSmiley();
   //drawSun();

     // ***************END RELATIVE DRAWING*********************//

    glFlush();
}// end display

int main(int argc, char** argv)
{
    // the window is opened in the Canvas constructor
    glutDisplayFunc(display);
    glutMainLoop();
}//end main