#pragma once
#include <GL/glut.h>
#include <time.h>
#include <math.h>
class Utils {
public :
	// Function to Print Text
	static void print(char* string, GLfloat r, GLfloat g, GLfloat b, GLfloat a,  GLint x, GLint y,GLfloat w, GLfloat h,GLfloat strokeSize) {
		glPushMatrix();
		glColor4f(r, g, b, a);
		glTranslatef(x, y, 0);
		glScalef(w, h, 0);

		glPointSize(strokeSize);
		glLineWidth(strokeSize);

		while (*string)
			glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, *string++);

		glPopMatrix();

		glLineWidth(1);
		glPointSize(1);
	}
};