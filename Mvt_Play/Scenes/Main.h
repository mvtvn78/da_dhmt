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
		glutInitDisplayMode(GLUT_DOUBLE  | GLUT_RGBA);
		glutInitWindowSize(CONS.SCREEN_WIDTH, CONS.SCREEN_HEIGHT);
		glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - CONS.SCREEN_WIDTH) >> 1, (glutGet(GLUT_SCREEN_HEIGHT) - CONS.SCREEN_HEIGHT - 50) >> 1);
		// Tạo cửa sổ
		glutCreateWindow(CONS.TITLE);
		// Khởi tạo thông số đầu tiên
		init();
		#pragma region Đăng ký hàm xử lý
				/*glutReshapeFunc(reshape);*/
				glutKeyboardFunc(keyboard);
				glutDisplayFunc(display);
				glutMouseFunc(mouseEvent);
				glutTimerFunc(CONS.FPS_ML, update, 0);
		#pragma endregion
		glutMainLoop();
	}
	void init()
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		// định nghĩa khung vẽ
		gluOrtho2D(0, CONS.SCREEN_WIDTH, 0, CONS.SCREEN_HEIGHT);
	}
	static void mouseEvent(int button, int state, int x, int y)
	{
		instance->handleMouseEvent(button, state, x, y);
	}
	void handleMouseEvent(int button, int state, int x, int y)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			std::wcout << x << " " << y << "\n";
		}
	}
	static void update(int x)
	{
		instance->handleUpdate();
	}
	void handleUpdate()
	{
		switch (SCENE_ID) {
			case 0:
				itScene->update();
				break;
			default:
				break;
		}
		// callback
		glutPostRedisplay();

		// callback
		glutTimerFunc(CONS.FPS_ML, update, 0);
	}
	static void display()
	{
		instance->handleRenderer();
	}
	void handleRenderer() {
		switch (SCENE_ID) {
		case 0:
			itScene->display();
			break;
		default:
			break;
		}
		//Gọi Vẽ
		glutSwapBuffers();
	}
	static void keyboard(unsigned char key, int x, int y)
	{
		// xử lý không chấp nhận đăng ký hàm 
		instance->handleKeyPress(key,x,y);
	}
	void handleKeyPress(unsigned char key, int x, int y) {
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