#pragma once
#include"../Utils/Utils.h"
#include <Windows.h>
#include <mmsystem.h>
class Scene {
public: 
	CONSTANTS con;
	// định nghĩa hàm thuần ảo
	virtual void display() = 0; 
	virtual void update() = 0; 
};