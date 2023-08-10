// Parametrized Regular Polygon

#include <gl/glut.h>
#include <cmath>

const double PI = 3.14159265358979323846;

class Point2 {
public:
    float x, y;

    Point2(float x = 0.0, float y = 0.0) : x(x), y(y) {}
};

void moveTo(const Point2& p) {
    glVertex2f(p.x, p.y);
}

void lineTo(const Point2& p) {
    glVertex2f(p.x, p.y);
}

void ngon(int n, double cx, double cy, double radius, double rotAngle) {
    if (n < 3) {
        return;
    }

    glBegin(GL_LINE_LOOP);

    double angle = rotAngle * PI / 180;
    double angleInc = 2 * PI / n;

    Point2 startPoint(cx + radius * cos(angle), cy + radius * sin(angle));
    moveTo(startPoint);

    for (int i = 0; i < n; ++i) {
        angle += angleInc;
        Point2 vertex(cx + radius * cos(angle), cy + radius * sin(angle));
        lineTo(vertex);
    }

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 0.0, 0.0); // Set color to red

    int sides = 6;          // Number of sides in the polygon
    double centerX = 0.0;   // X-coordinate of the center
    double centerY = 0.0;   // Y-coordinate of the center
    double radius = 0.5;    // Radius of the polygon
    double rotation = 30.0; // Rotation angle in degrees

    ngon(sides, centerX, centerY, radius, rotation);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(30, 30);
    glutCreateWindow("Lab 3 - Ngon & Polygon");
    glClearColor(1.0, 1.0, 1.0, 1.0); // Set clear color to white
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}