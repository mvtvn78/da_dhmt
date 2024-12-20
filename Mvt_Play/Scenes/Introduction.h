#pragma once
#include"./Scene.h"
class Introduction : public Scene {
private:
	GLfloat text_anim_fade = 0;
	GLfloat text_anim_apper = 0;
	GLfloat trans_x = 0;
	TextRenderer titile_renderer;
	TextRenderer topic_renderer;
	TextRenderer member_renderer;
	TextRenderer teacher_renderer;
	GLfloat x_title;
public:
	Introduction()
	{
		x_title = (con.SCREEN_WIDTH >> 1) -430;
		titile_renderer.loadFont(con.PATH_FONT_REGULAR, 100);
		topic_renderer.loadFont(con.PATH_FONT_REGULAR, 50);
		member_renderer.loadFont(con.PATH_FONT_BOLD, 46);
		teacher_renderer.loadFont(con.PATH_FONT_BOLD, 48);
	}
	void display()  override{
		glClearColor(0.0f,0.0f,0.0f, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		titile_renderer.renderText(L"ĐỒ HỌA MÁY TÍNH", x_title, 550, 255,255,255, text_anim_fade);
		topic_renderer.renderText(L"HẠ - THU - ĐÔNG - XUÂN", x_title + 150, 450, 255, 255, 255, text_anim_apper);
		member_renderer.renderText(L"----------------------------------", x_title + 150, 400, 255, 255, 255, text_anim_fade);
		member_renderer.renderText(L"Mai Tiền", x_title + 320, 350, 255, 255, 255, text_anim_fade);
		member_renderer.renderText(L"Hoàng Tú", x_title + 100, 280, 255, 255, 255, text_anim_fade);
		topic_renderer.renderText(L"-", x_title + 370, 280, 255, 255, 255, text_anim_fade);
		member_renderer.renderText(L"Phương Nam", x_title + 420, 280, 255, 255, 255, text_anim_fade);
		member_renderer.renderText(L"----------------------------------", x_title + 150, 240, 255, 255, 255, text_anim_fade);
		teacher_renderer.renderText(L"GV Phụng Nguyễn", x_title + 200, 180, 255, 255, 255, text_anim_fade);
	}
	void update() override {
		if (text_anim_fade < 1)
			text_anim_fade += 0.005;
		else
		{
			text_anim_fade = 1;
			text_anim_apper = 1;
		}
		if (trans_x < 100)
			trans_x += 1;
	}
};