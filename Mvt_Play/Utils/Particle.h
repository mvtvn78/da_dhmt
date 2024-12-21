#pragma once
#include"./Utils.h"
class Particle {
private :
	GLfloat x;
	GLfloat y;
	//color
	GLfloat r; 
	GLfloat g; 
	GLfloat b;
	GLfloat a;
	GLfloat gravity = 0.005;
	GLfloat friction = 0.99;
	GLfloat velocity_x;
	GLfloat velocity_y;
	GLfloat radius;
public : 
	Particle(GLfloat x, GLfloat y,
		GLfloat r, GLfloat g, GLfloat b, GLfloat a,
		GLfloat velocity_x, GLfloat velocity_y,
		GLfloat radius)  {
		this->x = x;
		this->y = y;
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
		this->velocity_x = velocity_x;
		this->velocity_y = velocity_y;
		this->radius = radius;
	}
	
	GLfloat getAlpha()
	{
		return this->a;
	}
	void draw() {
		
		glPushMatrix();
		glTranslatef(x, y, 0);
		glColor4f(r,g,b, a);
		glBegin(GL_POLYGON);
		for (GLfloat i = 0; i < 360; i += 5)
			glVertex2f(radius * sin(i * PI / 180), radius * cos(i * PI / 180));
		glEnd();
		glPopMatrix();
	}
	void update() {
		this->velocity_x *= friction; // 10 * 0.99 = 9.99 , 9.99 *0.99 = smaller (slower)
		this->velocity_y *= friction;
		this->velocity_y += gravity;
		this->x += this->velocity_x;
		this->y -= this->velocity_y;
		this->a -= 0.007;
	}
};
