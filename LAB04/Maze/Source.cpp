#include <GL/glut.h> 
#include <iostream> 
#include <vector> 
#include <random> 
#include <ctime> 
#include <stack> 
#include <cmath> 
#include <chrono> 
#include <sstream>

const int ROWS = 35; 
const int COLS = 35; 
const int CELL_SIZE = 35; 


struct Cell {
    bool visited; 
    bool wallTop, wallRight, wallBottom, wallLeft; 
};
const int TIMER_DURATION = 120;
const int TIMER_INTERVAL = 1;  

std::vector<Cell> maze(ROWS* COLS); 
int startRow, startCol, endRow, endCol, playerRow, playerCol; 

bool gameWon = false; 
bool gameLost = false;

std::chrono::time_point<std::chrono::system_clock> startTime; 

// Function to check if a given row and column are within valid maze bounds
bool isValid(int row, int col) {
    return (row >= 0 && row < ROWS && col >= 0 && col < COLS);
}

void generateMaze() {
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            maze[row * COLS + col].visited = false;
            maze[row * COLS + col].wallTop = true;
            maze[row * COLS + col].wallRight = true;
            maze[row * COLS + col].wallBottom = true;
            maze[row * COLS + col].wallLeft = true;
        }
    }

    std::stack<std::pair<int, int>> stack;
    startRow = std::rand() % ROWS;
    startCol = std::rand() % COLS;
    stack.push(std::make_pair(startRow, startCol));
    maze[startRow * COLS + startCol].visited = true;

    while (!stack.empty()) {
        int currentRow = stack.top().first;
        int currentCol = stack.top().second;
        stack.pop();

        std::vector<int> neighbors = { 0, 1, 2, 3 };
        std::shuffle(neighbors.begin(), neighbors.end(), std::mt19937(std::random_device()()));

        for (int dir : neighbors) {
            int newRow = currentRow;
            int newCol = currentCol;
            switch (dir) {
            case 0: newRow--; break; // Up
            case 1: newCol++; break; // Right
            case 2: newRow++; break; // Down
            case 3: newCol--; break; // Left
            }

            if (isValid(newRow, newCol) && !maze[newRow * COLS + newCol].visited) {
                if (dir == 0) {
                    maze[currentRow * COLS + currentCol].wallTop = false;
                    maze[newRow * COLS + newCol].wallBottom = false;
                }
                if (dir == 1) {
                    maze[currentRow * COLS + currentCol].wallRight = false;
                    maze[newRow * COLS + newCol].wallLeft = false;
                }
                if (dir == 2) {
                    maze[newRow * COLS + newCol].wallTop = false;
                    maze[currentRow * COLS + currentCol].wallBottom = false;
                }
                if (dir == 3) {
                    maze[newRow * COLS + newCol].wallRight = false;
                    maze[currentRow * COLS + currentCol].wallLeft = false;
                }

                stack.push(std::make_pair(newRow, newCol));
                maze[newRow * COLS + newCol].visited = true;
            }
        }
    }

    startRow = 0;
    startCol = 0;
    maze[startRow * COLS + startCol].wallLeft = false;

    // Set the ending point
    endRow = ROWS - 1;
    endCol = COLS - 1;
    maze[endRow * COLS + endCol].wallRight = false;

    // Set the player's initial position to the starting point
    playerRow = startRow;
    playerCol = startCol;
}
void drawTimer(int minutes, int seconds) {
    glColor3f(0.0f, 0.0f, 0.0f); 
    glRasterPos2i(10, ROWS * CELL_SIZE - 20); 
    std::stringstream timerText; 
    timerText << minutes << " min " << seconds << " sec left"; 
    for (char c : timerText.str()) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c); 
    }
}
void drawGameOverWindow(const std::string& message) {
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    glColor3f(0.0f, 0.0f, 0.0f);
    int messageWidth = 400; 
    int messageHeight = 200; 
    int messageX = (windowWidth - messageWidth) / 2;
    int messageY = (windowHeight - messageHeight) / 2;
    glRectf(messageX, messageY, messageX + messageWidth, messageY + messageHeight);

    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2i(messageX + 50, messageY + 140);
    for (char c : message) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    glRasterPos2i(messageX + 100, messageY + 100);
    std::string options = "Press 1 to play again, 2 to exit.";
    for (char c : options) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

void drawTrajectory(float x, float y) {
    static std::vector<std::pair<float, float>> trajectoryPoints; // Store trajectory points

    // Store current position in the trajectoryPoints vector
    trajectoryPoints.push_back(std::make_pair(x, y));

    if (gameWon == true) {
        trajectoryPoints.clear();
        return;
    }

    // Limit the number of points to prevent excessive memory usage
    if (trajectoryPoints.size() > 10000) {
        std::cout << x << y;
        trajectoryPoints.erase(trajectoryPoints.begin());
    }

    // Draw the trajectory as a line
    glColor3f(1.0, 0.0, 0.0); 
    glBegin(GL_LINE_STRIP);
    for (const auto& point : trajectoryPoints) {
        glVertex2f(point.first, point.second);
    }
    glEnd();
    //glutPostRedisplay();
}

void checkGameStatus() {
    glClear(GL_COLOR_BUFFER_BIT);
    if (!gameWon && !gameLost) {
        auto currentTime = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsedSeconds = currentTime - startTime;
        int remainingTime = TIMER_DURATION - static_cast<int>(elapsedSeconds.count());

        int minutes = remainingTime / 60;
        int seconds = remainingTime % 60;

        drawTimer(minutes, seconds);

        if (remainingTime <= 0) {
            gameLost = true;
        }

    }
    // Draw the maze walls
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            const Cell& cell = maze[row * COLS + col];
            int x = col * CELL_SIZE;
            int y = row * CELL_SIZE;

            glColor3f(0.0f, 0.0f, 0.0f);
            if (cell.wallTop) {
                glBegin(GL_LINES);
                glVertex2i(x, y);
                glVertex2i(x + CELL_SIZE, y);
                glEnd();
            }
            if (cell.wallRight) {
                glBegin(GL_LINES);
                glVertex2i(x + CELL_SIZE, y);
                glVertex2i(x + CELL_SIZE, y + CELL_SIZE);
                glEnd();
            }
            if (cell.wallBottom) {
                glBegin(GL_LINES);
                glVertex2i(x, y + CELL_SIZE);
                glVertex2i(x + CELL_SIZE, y + CELL_SIZE);
                glEnd();
            }
            if (cell.wallLeft) {
                glBegin(GL_LINES);
                glVertex2i(x, y);
                glVertex2i(x, y + CELL_SIZE);
                glEnd();
            }
        }
    }

    // Draw the starting point
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2i(startCol * CELL_SIZE, startRow * CELL_SIZE);
    glVertex2i((startCol + 1) * CELL_SIZE, startRow * CELL_SIZE);
    glVertex2i((startCol + 1) * CELL_SIZE, (startRow + 1) * CELL_SIZE);
    glVertex2i(startCol * CELL_SIZE, (startRow + 1) * CELL_SIZE);
    glEnd();

    // Draw the ending point 
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2i(endCol * CELL_SIZE, endRow * CELL_SIZE);
    glVertex2i((endCol + 1) * CELL_SIZE, endRow * CELL_SIZE);
    glVertex2i((endCol + 1) * CELL_SIZE, (endRow + 1) * CELL_SIZE);
    glVertex2i(endCol * CELL_SIZE, (endRow + 1) * CELL_SIZE);
    glEnd();

    // Draw the player's icon 
    glColor3f(1.0f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLE_FAN);
    float playerX = playerCol * CELL_SIZE + CELL_SIZE / 2.0f;
    float playerY = playerRow * CELL_SIZE + CELL_SIZE / 2.0f;
    glVertex2f(playerX, playerY);
    for (int i = 0; i <= 360; i++) {
        float angle = 3.1415926f * i / 180.0f;
        glVertex2f(playerX + cos(angle) * CELL_SIZE / 4.0f, playerY + sin(angle) * CELL_SIZE / 4.0f);
    }
    glEnd();

    drawTrajectory(playerX, playerY);

    if (gameWon) {
        drawGameOverWindow("Congratulations! You won the game.");
    }
    else if (gameLost) {
        drawGameOverWindow("Time's up! Game over.");
    }

    glutSwapBuffers();
}


void timerCallback(int value) {

    checkGameStatus();
    glutPostRedisplay();
    if (!gameWon && !gameLost) {
        glutTimerFunc(TIMER_INTERVAL * 1000, timerCallback, 0); // Update timer
    }
}
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, COLS * CELL_SIZE, 0, ROWS * CELL_SIZE);
    glMatrixMode(GL_MODELVIEW);
}

void movePlayer(int key, int x, int y) {
    if (!gameWon && !gameLost) {
        switch (key) {
        case GLUT_KEY_DOWN:
            if (!maze[playerRow * COLS + playerCol].wallTop && isValid(playerRow - 1, playerCol)) {
                playerRow--;
            }
            break;
        case GLUT_KEY_UP:
            if (!maze[playerRow * COLS + playerCol].wallBottom && isValid(playerRow + 1, playerCol)) {
                playerRow++;
            }
            break;
        case GLUT_KEY_LEFT:
            if (!maze[playerRow * COLS + playerCol].wallLeft && isValid(playerRow, playerCol - 1)) {
                playerCol--;
            }
            break;
        case GLUT_KEY_RIGHT:
            if (!maze[playerRow * COLS + playerCol].wallRight && isValid(playerRow, playerCol + 1)) {
                playerCol++;
            }
            break;
        default:
            break;
        }

        // Check if the player has reached the ending point
        if (playerRow == endRow && playerCol == endCol) {
            gameWon = true;
        }

        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y) {
    if (gameWon || gameLost) {
        if (key == '1') {
            generateMaze();
            gameWon = false;
            gameLost = false;
            startTime = std::chrono::system_clock::now(); 
        }
        else if (key == '2') {
            exit(0);
        }
    }
    // Check if the player has reached the ending point
    if (playerRow == endRow && playerCol == endCol) {
        gameWon = true;
    }

    glutPostRedisplay();
}
int main(int argc, char** argv) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    generateMaze(); // Generate the maze

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(COLS * CELL_SIZE, ROWS * CELL_SIZE);
    glutCreateWindow("Maze Game");
    glutDisplayFunc(checkGameStatus); 
    glutReshapeFunc(reshape);

    glutKeyboardFunc(keyboard);
    glutSpecialFunc(movePlayer);

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

    startTime = std::chrono::system_clock::now();

    glutTimerFunc(0, timerCallback, 0);

    glutMainLoop(); 

    return 0;
}