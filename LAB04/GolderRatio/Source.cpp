#include <GL/glut.h>

// Function to draw the golden rectangle with a specified color
void drawGoldenRectangle(float centerX, float centerY, float rectWidth, float rectHeight, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex2f(centerX - rectWidth / 2, centerY - rectHeight / 2);
    glVertex2f(centerX + rectWidth / 2, centerY - rectHeight / 2);
    glVertex2f(centerX - rectWidth / 2, centerY + rectHeight / 2);
    glVertex2f(centerX + rectWidth / 2, centerY + rectHeight / 2);
    glEnd();
}

// Display callback function
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Calculate initial center and size for the golden rectangle
    float centerX = 0.0f;
    float centerY = 0.0f;
    float rectWidth = 0.5f;
    float rectHeight = 0.5f;

    // Draw the regression of golden rectangles with different colors
    for (int i = 0; i < 10; ++i)
    {
        float r = (i / 10.0f);      // Varies from 0.0 to 1.0
        float g = (1.0f - r);       // Varies from 1.0 to 0.0
        float b = (0.5f + r / 2);   // Varies from 0.5 to 1.0

        drawGoldenRectangle(centerX, centerY, rectWidth, rectHeight, r, g, b);

        // Update center and size for the next rectangle
        centerX *= 0.9f;
        centerY *= 0.9f;
        rectWidth *= 0.9f;
        rectHeight *= 0.9f;
    }

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 400);
    glutCreateWindow("Golden Rectangles");

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}