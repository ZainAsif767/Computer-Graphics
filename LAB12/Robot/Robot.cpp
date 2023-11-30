//#include <iostream>
//#include <GL/glut.h>
//#include <cmath>
//
//using namespace std;
//
//int screenWidth = 500;
//int screenHeight = 500;
//
//void xlate(float x, float y) {
//    glTranslatef(x, y, 0.0);
//}
//
//void drawBody() {
//    glBegin(GL_LINE_LOOP);
//    glColor3f(0.0, 0.0, 0.0);
//    glVertex2f(-2.0, 2.0);
//    glVertex2f(2.0, 2.0);
//    glVertex2f(1.0, 0.0);
//    glVertex2f(2.0, -2.0);
//    glVertex2f(-2.0, -2.0);
//    glVertex2f(-1.0, 0.0);
//    //glVertex2f(-2.0, 2.0);
//    glEnd();
//}
//
//void drawShoulder() {
//    glBegin(GL_QUADS);
//    glVertex2f(-3.0, 0.0);
//    glVertex2f(3.0, 0.0);
//    glVertex2f(3.0, 0.5);
//    glVertex2f(-3.0, 0.5);
//    glColor3f(1.0f, 0.0f, 0.0f);
//    glEnd();
//}
//
//void drawArm() {
//    glBegin(GL_QUADS);
//    glVertex2f(0.0, 0.0);
//    glVertex2f(0.5, 0.0);
//    glVertex2f(0.5, -1.5);
//    glVertex2f(0.0, -1.5);
//    glColor3f(1.0f, 0.0f, 0.0f);
//    glEnd();
//}
//
//void drawHead() {
//    float radius = 0.7f;
//    int segments = 360;
//    glColor3f(0.0, 1.0, 0.0);
//    glBegin(GL_POLYGON);
//    for (int i = 0; i < segments; ++i) {
//        float theta = 2.0f * 3.14159265359f * float(i) / float(segments);
//        float x = radius * cos(theta);
//        float y = radius * sin(theta);
//        glVertex2f(x, y);
//    }
//    glEnd();
//}
////~~~~~~~~~~~~~SOLUTION 1~~~~~~~~~~~~~~~~`
//// Independent / Non Hierarchical
////void drawRobot() {
////    glMatrixMode(GL_MODELVIEW);
////    glLoadIdentity();
////    glPushMatrix();
////    xlate(0, 0);
////    drawBody();
////    glPopMatrix();
////
////    glPushMatrix();
////    xlate(0, 2);
////    drawShoulder();
////    glPopMatrix();
////
////    glPushMatrix();
////    xlate(-3, 2);
////    drawArm();
////    glPopMatrix();
////
////    glPushMatrix();
////    xlate(2.5, 2);
////    drawArm();
////    glPopMatrix();
////
////    glPushMatrix();
////    xlate(0, 3.2);
////    drawHead();
////    glPopMatrix();
////}
//
////~~~~~~~~SOLUTION 2~~~~~~~~~~~
// //Dependent / Hierarchical
//
//void drawRobot() {
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    glPushMatrix();
//    xlate(0, 0);
//    glPushMatrix();
//    drawBody();
//    xlate(0, 2);
//    glPushMatrix();
//    drawShoulder();
//    xlate(-3, 0);
//    drawArm();
//    glPushMatrix();
//    xlate(5.5, 0);
//    drawArm();
//    glPopMatrix();
//    glPopMatrix();
//    glPushMatrix();
//    xlate(0, 1.2);
//    drawHead();
//    glPopMatrix();
//    glPopMatrix();
//    glPopMatrix();
//}
//
////void drawAxes() {
////    glColor3f(1.0f, 1.0f, 1.0f);
////    glBegin(GL_LINES);
////    glVertex2f(-10.0f, 0.0f);
////    glVertex2f(10.0f, 0.0f);
////    glEnd();
////
////    glColor3f(1.0f, 1.0f, 1.0f);
////    glBegin(GL_LINES);
////    glVertex2f(0.0f, -10.0f);
////    glVertex2f(0.0f, 10.0f);
////    glEnd();
////}
//
//void display() {
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glLoadIdentity();
//    glViewport(-1, 1, -1, 1);
//    //drawAxes();
//    drawRobot();
//    glFlush();
//}
//
//void init() {
//    glEnable(GL_COLOR_MATERIAL);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glClearColor(1.0, 1.0, 1.0, 1.0);
//}
//
//void reshape(int w, int h) {
//    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluOrtho2D(-6, 6, -6, 6);
//    glMatrixMode(GL_MODELVIEW);
//}
//
//int main(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutInitWindowSize(screenWidth, screenHeight);
//    glutInitWindowPosition(200, 100);
//
//    glutCreateWindow("Robot");
//    glutDisplayFunc(display);
//    glutReshapeFunc(reshape);
//
//    init();
//    glutMainLoop();
//
//    return 0;
//}