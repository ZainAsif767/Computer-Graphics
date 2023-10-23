#include <gl/glut.h>
#include <cmath>

const double PI = 3.14159265358979323846;

class Point2 {
public:
    float x, y;

    Point2(float x = 0.0, float y = 0.0) : x(x), y(y) {}

    float getX() const {
        return x;
    }

    float getY() const {
        return y;
    }
};

void moveTo(const Point2& p) {
    glBegin(GL_LINE_STRIP);
    glVertex2f(p.x, p.y);
}

void lineTo(const Point2& p) {
    glVertex2f(p.x, p.y);
}

void drawArc(const Point2& center, float radius, float startAngle, float sweep) {
    const int n = 20; // number of intermediate segments in arc
    float angle = startAngle * PI / 180; // initial angle in radians
    float angleInc = sweep * PI / (180 * n); // angle increment
    float cx = center.getX(), cy = center.getY();

    moveTo(Point2(cx + radius * cos(angle), cy + radius * sin(angle)));

    for (int k = 1; k < n; ++k, angle += angleInc) {
        lineTo(Point2(cx + radius * cos(angle), cy + radius * sin(angle)));
    }

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.1, 0.0, 0.0); // Set color to red

    Point2 center(0.0, 0.0);  // Center of the arc
    float radius = 0.5;       // Radius of the arc
    float startAngle = 30.0;  // Starting angle in degrees
    float sweepAngle = 120.0; // Sweep angle in degrees

    drawArc(center, radius, startAngle, sweepAngle);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(30, 30);
    glutCreateWindow("Drawing an Arc");
    glClearColor(1.0, 1.0, 1.0, 1.0); // Set clear color to white
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}