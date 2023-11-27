#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <gl/glut.h>
#include "pixMap.h"
#include "Bhoot.h"
#include "walls.h"
#include "collision.h"
#include <Windows.h>

RGBApixmap pix;
RGBApixmap Flagpix1;
RGBApixmap Flagpix2;
RGBApixmap Finishpix;
RGBApixmap GameOver, YouWin;

int route_1_x_max = 17, route_1_min = 0;
int route_2_x_max = 95, route_2_min = 0;
int route_3_x_max = 17, route_3_min = 0;
int route_4_x_max = 93, route_4_min = 17;
int route_5_x_max = 30, route_5_min = 0;
int route_6_x_max = 100, route_6_min = 30;
int route_7_x_max = 93, route_7_min = 17;
int route_8_x_max = 64, route_8_min = 30;
int route_9_x_max = 95, route_9_min = 64;

int current_route = 1;
void setRouteNumber() {
	if (mario_x == 16 && mario_y >= route_1_min && mario_y < route_1_x_max) {
		current_route = 1;
	}
	else
		if (mario_y == 17 && mario_x > route_2_min && mario_x < route_2_x_max) {
			current_route = 2;
		}
		else
			if (mario_x == 30 && mario_y<route_4_x_max && mario_y>route_4_min) {
				current_route = 4;
			}
			else
				if (mario_x == 42 && mario_y < 17 && mario_y>0) {
					current_route = 3;
				}
				else
					if (mario_y == 59 && mario_x<route_5_x_max && mario_x>route_5_min) {
						current_route = 5;
					}
					else
						if (mario_y == 83 && mario_x<route_6_x_max && mario_x>route_6_min) {
							current_route = 6;
						}
						else
							if (mario_x == 64 && ((mario_y < route_7_x_max && mario_y>83) || (mario_y > route_7_min && mario_y < 83))) {
								current_route = 7;
							}
							else
								if (mario_y == 51 && mario_x<route_9_x_max && mario_x>route_9_min) {
									current_route = 9;
								}
								else
									if (mario_y == 43 && mario_x<route_8_x_max && mario_x>route_8_min) {
										current_route = 8;
									}

}


void display(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
	drawWalls();

	setRouteNumber();
	if (mario_x > 99) {
		glRasterPos2f(0, 40);
		game_stop = true;
		YouWin.mDraw();
	}
	if (game_over == true) {
		glRasterPos2f(20, 20);
		GameOver.mDraw();
	}
	drawBhoot(bhoot_1_x, bhoot_1_y);
	drawBhoot(bhoot_2_x, bhoot_2_y);
	drawBhoot(bhoot_3_x, bhoot_3_y);
	drawBhoot(bhoot_4_x, bhoot_4_y);
	drawBhoot(bhoot_5_x, bhoot_5_y);

	glRasterPos2f(mario_x, mario_y);
	pix.mDraw();

	glRasterPos2f(23, 0);
	Flagpix1.mDraw();
	glRasterPos2f(8.5, 0);
	Flagpix2.mDraw();
	glRasterPos2f(92, 91);
	Finishpix.mDraw();

	checkBhootCollision();
	glFlush();
}

//void myKeyboard(unsigned char key, int x, int y) {
//	if (game_stop == false) {
//		if (key == 'r') {
//			game_stop = false;
//			mario_x = 16;
//			mario_y = 1;
//			game_over = false;
//		}
//		glutPostRedisplay();
//	}
//}

void pressKeySpecial(int key, int x, int y) {
	if (game_stop == false) {
		if (key == GLUT_KEY_LEFT) {
			if (current_route == 2 && mario_x > route_2_min && mario_x <= route_2_x_max) {
				mario_x--;
			}
			else if (current_route == 4 && mario_y == 59) {
				mario_x--;
			}
			else if (current_route == 5 && mario_x <= route_5_x_max && mario_x > route_5_min) {
				mario_x--;
			}
			else if (current_route == 6 && mario_x <= route_6_x_max && mario_x > route_6_min) {
				mario_x--;
			}
			else if (current_route == 9 && mario_x <= route_9_x_max && mario_x >= route_9_min) {
				mario_x--;
			}
			else if (current_route == 8 && mario_x < route_8_x_max && mario_x >= route_8_min) {
				mario_x--;
			}
			else if (current_route == 7 && mario_y == 43) {
				mario_x--;
			}
			/*std::cout << "next line" << std::endl;
			std::cout << mario_x << std::endl;
			std::cout << mario_y << std::endl;*/

		}
		else if (key == GLUT_KEY_RIGHT)
		{
			if (current_route == 2 && mario_x >= route_2_min && mario_x < route_2_x_max) {
				mario_x++;
			}
			else if (current_route == 5 && mario_x < route_5_x_max && mario_x >= route_5_min) {
				mario_x++;
			}
			else if (current_route == 6 && mario_x < route_6_x_max && mario_x >= route_6_min) {
				mario_x++;
			}
			else if (current_route == 4 && mario_y == 83) {
				mario_x++;
			}
			else if (current_route == 7 && mario_y == 51) {
				mario_x++;
			}
			else if (current_route == 9 && mario_x < route_9_x_max && mario_x >= route_9_min) {
				mario_x++;
			}
			else if (current_route == 4 && mario_y == 43) {
				mario_x++;
			}
			else if (current_route == 8 && mario_x < route_8_x_max && mario_x >= route_8_min) {
				mario_x++;
			}

			/*std::cout << "next line" << std::endl;
			std::cout << mario_x << std::endl;
			std::cout << mario_y << std::endl;*/
		}
		else if (key == GLUT_KEY_UP)
		{
			if (current_route == 1 && mario_y < route_1_x_max) {
				mario_y++;
			}
			else if (current_route == 2 && mario_x == 30) {
				mario_y++;
			}
			else if (current_route == 4 && mario_y < route_4_x_max) {
				mario_y++;
			}
			else if (current_route == 3 && mario_y < route_4_x_max) {
				mario_y++;
			}
			else if (current_route == 6 && mario_x == 64) {
				mario_y++;
			}
			else if (current_route == 7 && mario_y < route_7_x_max && mario_y >= route_7_min) {
				mario_y++;
			}
			else if (current_route == 2 && mario_x == 64) {
				mario_y++;
			}
			/*std::cout << "next line" << std::endl;
			std::cout << mario_x << std::endl;
			std::cout << mario_y << std::endl;*/

		}
		else if (key == GLUT_KEY_DOWN)
		{
			if (current_route == 1 && mario_y > route_1_min) {

				mario_y--;

			}
			else if (current_route == 2 && mario_y == 17 && mario_x == 16) {
				mario_y--;
			}
			else if (current_route == 2 && mario_y < route_2_x_max && mario_x == 42) {
				mario_y--;
			}
			else if (current_route == 4 && mario_y > route_4_min) {
				mario_y--;
			}
			else if (current_route == 3 && mario_y > route_3_min) {
				mario_y--;
			}
			else if (current_route == 6 && mario_x == 64) {
				mario_y--;
			}
			else if (current_route == 7 && mario_y <= route_7_x_max && mario_y > route_7_min) {
				mario_y--;
			}

		/*	std::cout << "next line" << std::endl;
			std::cout << mario_x << std::endl;
			std::cout << mario_y << std::endl;*/
		}

	}
	if (key == 'r') {
		game_stop = false;
		mario_x = 16;
		mario_y = 1;
		game_over = false;
	}
	glutPostRedisplay();
}

void myTimer(int t)
{
	if (game_stop == false) {
		moveBhoots();
	}
	glutPostRedisplay();
	glutTimerFunc(100, myTimer, t);

}
void myInit(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_EQUAL, 1.0); // accept fragment if fragment alpha = reference alpha i.e. 1.0
	//or glAlphaFunc(GL_NOTEQUAL,0.0);// accept fragment if fragment alpha not= reference alpha i.e. 1.0

	glViewport(0, 0, 640, 480);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Mario Escape Game");
	myInit();

	pix.readBMPFile("m1.bmp", 1);
	pix.setChromaKey(255, 255, 255);
	Flagpix1.readBMPFile("S1.bmp", 1);
	Flagpix1.setChromaKey(255, 255, 255);
	Flagpix2.readBMPFile("S2.bmp", 1);
	Flagpix2.setChromaKey(255, 255, 255);
	Finishpix.readBMPFile("Finish.bmp", 1);
	Finishpix.setChromaKey(255, 255, 255);
	GameOver.readBMPFile("gameover.bmp", 1);
	GameOver.setChromaKey(255, 255, 255);
	YouWin.readBMPFile("youwin.bmp", 1);
	YouWin.setChromaKey(255, 255, 255);

	glutDisplayFunc(display);
	PlaySound(L"MarioSong.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	glutTimerFunc(500, myTimer, 1);
	//glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(pressKeySpecial);
	glutMainLoop();
}

