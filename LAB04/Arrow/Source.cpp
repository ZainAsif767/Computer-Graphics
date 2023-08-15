#include <gl/glut.h>

using namespace std;

class Point {
public:
    float x, y;

    void moveToRel(float dx, float dy) {
        this->x = this->x + dx;
        this->y = this->y + dy;
    }

    void lineToRel(float dx, float dy) {
        float x = this->x + dx;
        float y = this->y + dy;

        //glColor3f(1.0, 0.0, 0.0);
        glLineWidth(2.0);

        glBegin(GL_LINES);
        glVertex2f(this->x, this->y);
        glVertex2f(x, y);
        glEnd();
        glFlush();

        this->x = x;
        this->y = y;
    }

    Point() {
        this->x = 300;
        this->y = 300;
    }
};

int screenWidth = 640;
int screenHeight = 440;
Point CP;



void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    CP.lineToRel(-50, -80);
    CP.lineToRel(40, 0);
    CP.lineToRel(0, -50);
    CP.lineToRel(40, 0);
    CP.lineToRel(0, 50);
    CP.lineToRel(30, 0);
    CP.lineToRel(-60, 80);
    //glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Arrow");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, screenWidth, 0.0, screenHeight);
    glMatrixMode(GL_MODELVIEW);

    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}