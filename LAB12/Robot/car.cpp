#include <GL/glut.h>
#include<cmath>
#include<iostream>

using namespace std;
float speed = 0;
float deg = 0;
const double M_PI = 3.14159265358979323846;
bool isMoving = false;

void circles(float rad, float x, float r, float g , float b) {
    float radius = rad;
    int segments = 100;
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; ++i) {
        float theta = x * 3.14159265359f * float(i) / float(segments);
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();
}
void drawRoof() {
    circles(4.04f, 1.0f, 0.0, 1.0, 1.0);
}

void drawRoad() {
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(3.0);
    glBegin(GL_LINES);
    glVertex2f(-20.0f, -2.0f);
    glVertex2f(20.0f, -2.0f);
    glEnd();
}

void drawBody() {

    glPushMatrix();
    glTranslatef(-4, -2, 0);
    circles(3.01f, 1.0f, 0.0, 1.0, 1.0);

    glPushMatrix();
    glTranslatef(8, 0, 0);
    circles(3.01f, 1.0f, 0.0, 1.0, 1.0);
    
    glPopMatrix();
    glPopMatrix();

    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(-4.0f, -3.0f); 
    glColor3f(1.0f, 0.0f, 0.5f); 
    glVertex2f(-4.0f, 3.0f); 

    glColor3f(0.0f, 0.0f, 1.0f); 
    glVertex2f(4.0f, 3.0f); 
    glColor3f(1.0f, 0.0f, 1.0f); 
    glVertex2f(4.0f, -3.0f); 
    glEnd();
}

void drawTyre() {

    // Draw the outer circle of the tire
    glBegin(GL_POLYGON);
    glColor3f(0.1f, 0.1f, 0.1f); // Set color to dark gray
    for (int i = 0; i < 360; i++) {
        float radian = i * 3.14159265358979323846 / 180;
        float x = cos(radian) * 2.0f;
        float y = sin(radian) * 2.0f;
        glVertex2f(x, y);
    }
    glEnd();


    // Draw the inner circle of the tire
    glBegin(GL_POLYGON);
    glColor3f(0.3f, 0.3f, 0.3f); // Set color to light gray
    for (int i = 0; i < 360; i++) {
        float radian = i * 3.14159265358979323846 / 180;
        float x = cos(radian) * 1.5f;
        float y = sin(radian) * 1.5f;
        glVertex2f(x, y);
    }
    glEnd();
    
    glPushMatrix();
    glRotatef(deg, 0, 0, 1);
    glPushMatrix();
    glTranslatef(-0.5, -0.5, 0.0);
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f); // Set color to light gray
    for (int i = 0; i < 360; i++) {
        float radian = i * 3.14159265358979323846 / 180;
        float x = cos(radian) * 0.3f;
        float y = sin(radian) * 0.3f;
        glVertex2f(x, y);
    }
    glEnd();
    glTranslatef(0.0, 0.0, 0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5, 0.5, 0.0);
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f); // Set color to light gray
    for (int i = 0; i < 360; i++) {
        float radian = i * 3.14159265358979323846 / 180;
        float x = cos(radian) * 0.3f;
        float y = sin(radian) * 0.3f;
        glVertex2f(x, y);
    }
    glEnd();
    glTranslatef(0.0, 0.0, 0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5, -0.5, 0.0);
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f); // Set color to light gray
    for (int i = 0; i < 360; i++) {
        float radian = i * 3.14159265358979323846 / 180;
        float x = cos(radian) * 0.3f;
        float y = sin(radian) * 0.3f;
        glVertex2f(x, y);
    }
    glEnd();
    glTranslatef(0.0, 0.0, 0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5, 0.5, 0.0);
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f); // Set color to light gray
    for (int i = 0; i < 360; i++) {
        float radian = i * 3.14159265358979323846 / 180;
        float x = cos(radian) * 0.3f;
        float y = sin(radian) * 0.3f;
        glVertex2f(x, y);
    }
    glEnd();
    glTranslatef(0.0, 0.0, 0.0);
    glPopMatrix();
    glPopMatrix();
}

void processMenuEvents(int option)
{
    switch (option) {
    case 1:
        isMoving = true;
        break;

    case 2:
        isMoving = false;
        speed = 0;
        deg = 0;
        break;

    case 101:
        exit(0);
        break;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if (speed >= 27) {
        speed = -27;
    }
    glPushMatrix();
    glTranslatef(speed, 4, 0);
    drawRoof();
    glPushMatrix();
    glTranslatef(0, -2, 0);
    drawBody();
    glPushMatrix();
    glTranslatef(-4, -2, 0);
    drawTyre();
    glPushMatrix();
    glTranslatef(8, 0, 0);
    drawTyre();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    drawRoad();
    glFlush();
}
void Timer(int value)
{
    if (isMoving)
    {
        speed += 0.25;
        deg += 10;
    }
    display();
    glutTimerFunc(30, Timer, 1);
}
void reshape(GLsizei w, GLsizei h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-20, 20, -20, 20);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-20, 20, -20, 20);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glShadeModel(GL_FLAT);

}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1366, 720);
    glutCreateWindow("Car");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(30, Timer, 1);

    glutCreateMenu(processMenuEvents);

    glutAddMenuEntry("start", 1);
    glutAddMenuEntry("Reset", 2);
    glutAddMenuEntry("Exit", 101);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();
    return 0;
}