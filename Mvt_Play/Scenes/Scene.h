#pragma once
#include"../Utils/Utils.h"
#include <Windows.h>
#include <mmsystem.h>
#include<math.h>
class Scene {
public: 
	CONSTANTS con;
	// định nghĩa hàm thuần ảo
	virtual void display() = 0; 
	virtual void update() = 0; 
	virtual void mousePress(int , int , int , int ) = 0;
};