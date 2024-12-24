#pragma once
#include <GL/glut.h>
#include <time.h>
#include <math.h>
#include<iostream>
#include"../Utils/Constant.h"
#include"../Scenes/Scene.h"
#include"../Scenes/Introduction.h"
#include"../Scenes/FireWorks.h"
#include"../Scenes/Summer.h"
#include"../Scenes/Winter.h"
#include"../Scenes/Autumn.h"

class MainScene
{
private:
	CONSTANTS CONS;
	int SCENE_ID;
	Scene* current;
	static MainScene* instance;
public : 
	MainScene(int &argc, char** argv) {
		instance = this;
		//MAIN SCENE
		SCENE_ID = CONS.SCENE_INIT;
		sceneInit();
		// khởi  tạo
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE  | GLUT_RGBA | GLUT_ALPHA | GLUT_DEPTH);
		glutInitWindowSize(CONS.SCREEN_WIDTH, CONS.SCREEN_HEIGHT);
		glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - CONS.SCREEN_WIDTH) >> 1, (glutGet(GLUT_SCREEN_HEIGHT) - CONS.SCREEN_HEIGHT - 50) >> 1);
		// Tạo cửa sổ
		glutCreateWindow(CONS.TITLE);
		// Khởi tạo thông số đầu tiên
		init();
		#pragma region Đăng ký hàm xử lý
				glutReshapeFunc(reshape);
				glutKeyboardFunc(keyboard);
				// Đăng ký callback cho phím đặc biệt (mũi tên)
				glutSpecialFunc(specialKey);
				glutDisplayFunc(display);
				glutMouseFunc(mouseEvent);
				glutTimerFunc(CONS.FPS_ML, update, 0);
		#pragma endregion
		glutMainLoop();
	}

	static void reshape(int w, int h) {
		instance->handleReshape(w, h);
	}
	void handleReshape(int w, int h) {
		glViewport(0, 0, (GLsizei)w, (GLsizei)h);
		glMatrixMode(GL_MODELVIEW);
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
		int yReal = ( CONS.SCREEN_HEIGHT - y);
		current->mousePress(button,state, x, yReal);
	}
	static void update(int x)
	{
		instance->handleUpdate();
	}
	void handleUpdate()
	{
		current->update();
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
		current->display();
		//Gọi Vẽ
		glutSwapBuffers();
	}
	static void specialKey(int key, int x, int y)
	{
		instance->handleSpecialKey(key, x, y);
	}
	void handleSpecialKey(int key, int x, int y)
	{
		switch (key) {
		case GLUT_KEY_LEFT:  // Mũi tên trái
			if (SCENE_ID == 0)
				break;
			SCENE_ID--;
			// init Scene
			sceneInit();
			break;
		case GLUT_KEY_RIGHT:  // Mũi tên trái
			if (SCENE_ID == 4)
				break;
			SCENE_ID++;
			// init Scene
			sceneInit();
			break;
		default:
			break;
		}
		
		// callback lại hàm đăng ký display
		glutPostRedisplay();
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
				// init Scene
				sceneInit();
				break;
			// cảnh sau
			case 'd':
			case 'D':
				if (SCENE_ID == 4)
					break;
				SCENE_ID++;
				// init Scene
				sceneInit();
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
	void sceneInit()
	{
		
		PlaySound(NULL, NULL, 0);
		switch (SCENE_ID)
		{
			case 0: 
				current = new Introduction();
				break;
			case 1 :
				current = new Summer();
				break;
			case 2:
				current = new Autumn();
				break;
			case 3 :
				current = new Winter();
				break;
			case 4:
				current = new FireWorks();
				break;
			default:
				SCENE_ID = CONS.SCENE_INIT;
				sceneInit();
				break;
		}	
		
	}
};
// gán nullptr cho instance 
MainScene* MainScene::instance = nullptr;