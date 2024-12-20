#pragma once
#include"../Utils/Utils.h"
class Scene {
public: 
	CONSTANTS con;
	// định nghĩa hàm thuần ảo
	virtual void display() = 0; 
	virtual void update() = 0; 
};