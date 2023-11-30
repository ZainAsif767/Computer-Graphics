#include <iostream>
#include <GL/glut.h>
#include <cmath>

using namespace std;

int screenWidth = 500;
int screenHeight = 500;
double deg;

void tooth0() {
    glColor3f(1.0, 0.0, 0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.0, 0.0);
    glVertex2f(0.2, 0.2);
    glVertex2f(0.6, 0.2);
    glVertex2f(0.6, 0.8);
    glVertex2f(0.2, 0.8);
    glVertex2f(0, 1);
    glEnd();
}

void tooth1(double r) {
    double rad = 6.0 * 3.142 / 180.0;
    double sin6 = r * sin(rad);
    double cos6 = r * cos(rad);
    glPushMatrix();
    glTranslatef(cos6, -sin6, 0.0);
    glScalef(2.0 * sin6, 2.0 * sin6, 1.0);
    tooth0();
    glPopMatrix();
}

void drawCircle(float radius, int segments) {
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; ++i) {
        float theta = 2.0f * 3.14159265359f * float(i) / float(segments);
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();
}
void move() {
    float speed = .05;
    static int oldTime = clock(), newTime;
    newTime = clock();

    deg += (newTime - oldTime) * speed;
    oldTime = newTime;
}

void gear(double r) {

        glPushMatrix();
        for (int i = 1; i <= 30; i++)
        {
            tooth1(r);
        
            glRotatef(12.0, 0.0, 0.0, 1.0);
        }
        glPopMatrix();
    glutPostRedisplay();
    
}


void text()
{
    const char* text = "A gear Wheel";
    float textX = -5.0; // X-coordinate for the text position
    float textY = 5.0; // Y-coordinate for the text position

    glColor3f(0.0, 0.0, 0.0); // Set text color to white
    glRasterPos2f(textX, textY);

    // Loop through each character in the text and display it
    for (int i = 0; text[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }
}

void drawAxes() {
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(-10.0f, 0.0f);
    glVertex2f(10.0f, 0.0f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, -10.0f);
    glVertex2f(0.0f, 10.0f);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glLoadIdentity();
    glViewport(-1, 1, -1, 1);
    glPushMatrix();
    glRotatef(deg, 0.0, 0.0, 1.0);
    gear(4);
    glPopMatrix();
    drawCircle(0.5f, 36);
    drawAxes();
    text();
    cout << deg<<endl;

    glFlush();
}

void init() {
    glEnable(GL_COLOR_MATERIAL);
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-6, 6, -6, 6);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(200, 100);

    glutCreateWindow("Gear Wheel");
    glutIdleFunc(move);
    glutDisplayFunc(display);
    init();
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}
