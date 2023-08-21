#include <gl/glut.h>
#include <vector>
#include <math.h>
#include <string>

using namespace std;

class Shape {
public:
    virtual void draw() = 0;
};

class Triangle : public Shape {
public:
    void draw() override {
        glBegin(GL_TRIANGLES);
        glVertex2f(150, 50);
        glVertex2f(100, 150);
        glVertex2f(200, 150);
        glEnd();
    }
};

class Circle : public Shape {
public:
    void draw() override {
        const float PI = 3.14159;
        int segments = 50;
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(320, 240);
        for (int i = 0; i <= segments; i++) {
            float angle = 2.0f * PI * float(i) / float(segments);
            float x = 50 * cos(angle);
            float y = 50 * sin(angle);
            glVertex2f(x + 320, y + 240);
        }
        glEnd();
    }
};

int screenWidth = 640;
int screenHeight = 480;
vector<Shape*> shapes;
Shape* currentShape = nullptr;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    for (Shape* shape : shapes) {
        shape->draw();
    }

    glFlush();
}

void myKeys(unsigned char key, int x, int y) {
    switch (key) {
    case 't':
        currentShape = new Triangle();
        shapes.push_back(currentShape);
        glutPostRedisplay();
        break;
    case 'c':
        currentShape = new Circle();
        shapes.push_back(currentShape);
        glutPostRedisplay();
        break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Simple Drawing Program");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, screenWidth, 0.0, screenHeight);
    glMatrixMode(GL_MODELVIEW);

    glutDisplayFunc(display);
    glutKeyboardFunc(myKeys);

    glutMainLoop();

    for (Shape* shape : shapes) {
        delete shape;
    }

    return 0;
}
