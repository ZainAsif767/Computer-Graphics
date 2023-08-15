#include <GL/glut.h>
#include <iostream>
#include <ctime>
#include <cstdlib>

const int rows = 20; // Increase maze size
const int cols = 30; // Increase maze size
bool northWall[rows][cols];
bool southWall[rows][cols];
bool eastWall[rows][cols];
bool westWall[rows][cols];

int startX = 1;
int startY = 0;
int endX = cols - 2;
int endY = rows - 1;

void drawWall(int x1, int y1, int x2, int y2) {
    glColor3f(1.0f, 1.0f, 1.0f); // Set line color to white
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void renderMaze() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Draw the walls based on wall arrays

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (northWall[i][j])
                drawWall(j, i, j + 1, i);
            if (southWall[i][j])
                drawWall(j, i + 1, j + 1, i + 1);
            if (eastWall[i][j])
                drawWall(j + 1, i, j + 1, i + 1);
            if (westWall[i][j])
                drawWall(j, i, j, i + 1);
        }
    }

    // Draw start and end points
    glColor3f(0.0f, 1.0f, 0.0f); // Set color to green (start point)
    glRectf(startX, startY, startX + 1, startY + 1);

    glColor3f(1.0f, 0.0f, 0.0f); // Set color to red (end point)
    glRectf(endX, endY, endX + 1, endY + 1);

    glutSwapBuffers();
}

void generateMaze() {
    // Initialize random seed
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Generate maze walls (simplified for demonstration)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            northWall[i][j] = std::rand() % 2 == 0;
            southWall[i][j] = std::rand() % 2 == 0;
            eastWall[i][j] = std::rand() % 2 == 0;
            westWall[i][j] = std::rand() % 2 == 0;
        }
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Maze Program");

    glClearColor(1.0f, 0.0f, 0.0f, 0.0f); // Set background color to black
    generateMaze();

    glutDisplayFunc(renderMaze);
    glutMainLoop();

    return 0;
}
