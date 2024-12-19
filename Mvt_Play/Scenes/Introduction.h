#pragma once
#include"./Scene.h"
class Introduction : public Scene {		
	public:
	void display()  override{
		// Background
		glClearColor(0.05, 0.05, 0.05, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		//// Story Title
		//utl.print("The Epilogue of Education",
		//	1, 1, 1, title_fade, 280, 380, .3, .3, 2);

		//utl.print("by Raja Rajan A.",
		//	1, 1, 1, title_fade, 790, 345, .15, .15, 1);
		//utl.print("(1DS15CS417)",1, 1, 1, title_fade, 840, 320, .1, .1, 1);

		//utl.print("Press N to read the story...",1, 1, 1, intro_next_text_appear, 560, 10, .09, .09, 1);
	}
};