#pragma once
#include <GL/glut.h>
#include <time.h>
#include <math.h>
#include<iostream>
#include"../Utils/Constant.h"
#include"../Scenes/Scene.h"
#include"../Scenes/Introduction.h"
class MainScene
{
private:
	CONSTANTS CONS;
	int SCENE_ID;
	Scene* itScene = new Introduction();
	static MainScene* instance;
public : 
	MainScene(int &argc, char** argv) {
		instance = this;
		//MAIN SCENE
		SCENE_ID = 0;
		// khởi  tạo
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
		glutInitWindowSize(CONS.SCREEN_WIDTH, CONS.SCREEN_HEIGHT);
		glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - CONS.SCREEN_WIDTH) >> 1, (glutGet(GLUT_SCREEN_HEIGHT) - CONS.SCREEN_HEIGHT - 50) >> 1);
		glutCreateWindow(CONS.TITLE);
		init();
		#pragma region Đăng ký hàm xử lý
				/*glutReshapeFunc(reshape);*/
				glutTimerFunc(FPS, update, 0);
				glutKeyboardFunc(keyboard);
				glutDisplayFunc(display);
		#pragma endregion
		glutMainLoop();
	}
	void init()
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, 1400, 0, 800);
	}
	static void update(int x)
	{
		std::cout << x << std:: endl;
	}
	static void display()
	{
		instance->renderScene();
	}
	void renderScene() {
		switch (SCENE_ID) {
		case 0:
			itScene->display();
			break;
		default:
			break;
		}
		//Ép display
		glFlush();
	}
	static void keyboard(unsigned char key, int x, int y)
	{
		// xử lý không chấp nhận đăng ký hàm 
		instance->keypress(key,x,y);
	}
	void keypress(unsigned char key, int x, int y) {
		switch (key) {
			// cảnh trước
			case 'a':
			case 'A':
				if (SCENE_ID == 0)
					break;
				SCENE_ID--;
				break;
			// cảnh sau
			case 'd':
			case 'D':
				if (SCENE_ID == 15)
					break;
				SCENE_ID++;
				break;
			// thoát chương trình
			case 'q':
			case 'Q':
				exit(0);
				break;
			default:
				break;
			}
		// callback lại hàm đăng ký display
		glutPostRedisplay();
	}
};
// gán nullptr cho instance 
MainScene* MainScene::instance = nullptr;