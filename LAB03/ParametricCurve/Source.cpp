// Lab Activity 8

#include <gl/glut.h>
#include <cmath>

const double M_PI = 3.14159265358979323846;
// Function to draw the rose curve
void drawRoseCurve(int k) {
    glColor3f(0.0, 0.0, 0.0); // Set color to black
    glBegin(GL_LINE_STRIP);
    for (double angle = 0; angle <= 2 * M_PI; angle += 0.01) {
        double radius = sin(k * angle);            //Rose Cuves
        //double radius = k * angle;                 //Archimedian Spiral
        //double radius = k * (1 + cos(angle));        //Cardioid
        double x = radius * cos(angle);
        double y = radius * sin(angle);

        glVertex2d(x, y);
    }
    glEnd();
}

// Display callback function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0); // Set color to white
    glLoadIdentity();

    // Translate to the center of the window
    glTranslatef(0.0, 0.0, 0.0);

    // Scale the curve
    glScalef(0.5, 0.5, 1.0);

    drawRoseCurve(6); // You can adjust the value of 'k' here

    glFlush();
}

// Reshape callback function
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 400);
    glutCreateWindow("Lab 3 - Rose Curve using GLUT");
    glutInitWindowPosition(30,30);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glClearColor(1.0, 1.0, 1.0, 1.0); // Set clear color to white

    glutMainLoop();
    return 0;
}