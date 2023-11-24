//#include <iostream>
//#include <cstdlib>
//#include <cmath>
//#include <gl/glut.h>
//#include "function.h"
//
//const int screenWidth = 800;
//const int screenHeight = 600;
//int heightOfOneGrid, widthOfOneGrid;
//
//// -------------------- QUE FUNCTIONS ---------------------
//struct Node {
//    GLfloatPoint point;
//    Node* next;
//};
//
//typedef Node node;
//
//node* createQueue() {
//    node* ptr = new node;
//    ptr->point.x = 0;
//    ptr->point.y = 0;
//    ptr->next = nullptr;
//    return ptr;
//}
//
//void pushPoint(node* ptr, GLfloatPoint point) {
//    node* newPoint = new node;
//    ptr->point.x++;
//    ptr->point.y++;
//    while (ptr->next != nullptr) {
//        ptr = ptr->next;
//    }
//    newPoint->point = point;
//    newPoint->next = nullptr;
//    ptr->next = newPoint;
//}
//
//GLfloatPoint popPoint(node* ptr) {
//    GLfloatPoint point;
//    point = ptr->next->point;
//    node* temp = ptr->next;
//    ptr->next = ptr->next->next;
//    delete temp;
//    return point;
//}
//// -------------------- End of linked list function ------------
//
//void myInit(void) {
//    glClearColor(1.0, 1.0, 0.0, 0.0);
//    glColor3f(0.0f, 0.0f, 0.0f);
//    glPointSize(1.0);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluOrtho2D(0.0, screenWidth, 0.0, screenHeight);
//}
//
//// -------------------- Matrix Function --------------------
//node* gridDraw(int row, int column) {
//    int i, j;
//    node* head = createQueue();
//    widthOfOneGrid = screenWidth / row;
//    heightOfOneGrid = screenHeight / column;
//    GLfloatPoint point;
//    for (i = 0; i < screenHeight; i += heightOfOneGrid) {
//        for (j = 0; j < screenWidth; j += widthOfOneGrid) {
//            point.x = j;
//            point.y = i;
//            pushPoint(head, point);
//        }
//    }
//    return head;
//}
//
//node* matrixDraw(int row, int column) {
//    GLfloatPoint point1, point2, point3;
//    int i = 0;
//    node* head = gridDraw(row, column);
//    node* head1 = gridDraw(row, column);
//    for (i = 0; i < head->point.x; i++) {
//        point1 = popPoint(head);
//        point2.x = point1.x;
//        point2.y = point1.y + heightOfOneGrid;
//        point3.x = point1.x + widthOfOneGrid;
//        point3.y = point1.y;
//        drawLine(point1, point2);
//        drawLine(point1, point3);
//        glFlush();
//    }
//    return head1;
//}
//// -------------------- End of Matrix Function ------------
//
//void renderMaze(void) {
//    glClear(GL_COLOR_BUFFER_BIT);
//    drawMargin(screenWidth, screenHeight);
//    node* head = matrixDraw(6, 6);
//    std::cout << head->point.x << std::endl;
//    glFlush();
//}
//
//int main(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//    glutInitWindowSize(screenWidth, screenHeight);
//    glutInitWindowPosition(100, 150);
//    glutCreateWindow("maze");
//    glutDisplayFunc(renderMaze);
//    myInit();
//    glutMainLoop();
//    return 0;
//}
