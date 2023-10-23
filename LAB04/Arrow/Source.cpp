#include <gl/glut.h>
#include <iostream>
using namespace std;

class Canvas {
public:
    float x, y;
    Canvas() {
        this->x = 180;
        this->y = 200;
    }

    void moveTo(float x, float y) {
        this->x = x;
        this->y = y;
    }

    void lineToRel(float dx, float dy) {
        glBegin(GL_LINES);
        glVertex2f(x, y);
        x += dx;
        y += dy;
        glVertex2f(x, y);
        glEnd();
    }

    void drawMarker() {
        // Draw a marker at the current position (x, y)
        glBegin(GL_POLYGON);
        glVertex2f(x - 2, y - 2);
        glVertex2f(x + 2, y - 2);
        glVertex2f(x + 2, y + 2);
        glVertex2f(x - 2, y + 2);
        glEnd();
    }

    void arrow(float f, float h, float t, float w) {
        lineToRel(-w - t / 2, -f); // down the left side
        lineToRel(w, 0);
        lineToRel(0, -h);
        lineToRel(t, 0); // across
        lineToRel(0, h); // back up
        lineToRel(w, 0);
        lineToRel(-w - t / 2, f);
    }
};

int screenWidth = 640;
int screenHeight = 440;
Canvas CP;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    CP.moveTo(100, 200); // Move to the first data point

    // Draw an arrow at the current position (x, y)
     CP.arrow(60, 40, 40, 20);

     CP.moveTo(300, 300);
    // Draw a marker at the CP
    CP.drawMarker();

    CP.lineToRel(-60, -80);
    CP.drawMarker();

    CP.lineToRel(50, 0);
    CP.drawMarker();

    CP.lineToRel(0, -50);
    CP.drawMarker();

    CP.lineToRel(30, 0);
    CP.drawMarker();

    CP.lineToRel(0, 50);
    CP.drawMarker();

    CP.lineToRel(40, 0);
    CP.drawMarker();

    CP.lineToRel(-60, 80);
    CP.drawMarker();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Arrow Lab - 4");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, screenWidth, 0.0, screenHeight);
    glMatrixMode(GL_MODELVIEW);

    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
