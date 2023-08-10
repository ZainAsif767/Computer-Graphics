// Lab Activity 10

#include <gl/glut.h>
#include <cmath>

int screenWidth = 640;
int screenHeight = 480;
float circleCenterX = 320;
float circleCenterY = 240;
float circleRadius = 100;

void drawCircle()
{
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++)
    {
        float angle = i * 3.14159 / 180;
        float x = circleCenterX + circleRadius * cos(angle);
        float y = circleCenterY + circleRadius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f); // Set color to red

    drawCircle();

    glFlush();
}

void myInit()
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0); // Set background color to white

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, screenWidth, 0.0, screenHeight);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Lab 3 - Circle Drawing");
    glutDisplayFunc(myDisplay);
    myInit();
    glutMainLoop();
    return 0;
}
