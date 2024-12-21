#pragma once
#include"./Scene.h"
class Introduction : public Scene {
private:
	GLfloat text_anim_fade1 = 0;
	GLfloat text_anim_fade2 = 0;
	GLfloat text_anim_fade3 = 0;
	GLfloat text_anim_apper = 0;
	GLfloat trans_x = 0;
	GLfloat injection = 0.01;
	TextRenderer titile_renderer;
	TextRenderer topic_renderer;
	TextRenderer member_renderer;
	TextRenderer teacher_renderer;
	GLfloat x_title;
public:
	void PlayMusicAsync() {
		bool played = PlaySound(TEXT("../music/introduction.wav"), NULL, SND_ASYNC );
		if (played)
			std::wcout << L"Nhạc Intro bật lên" << std::endl;
	}
	Introduction()
	{
		x_title = (con.SCREEN_WIDTH >> 1) -430;
		titile_renderer.loadFont(con.PATH_FONT_REGULAR, 100);
		topic_renderer.loadFont(con.PATH_FONT_REGULAR, 50);
		member_renderer.loadFont(con.PATH_FONT_BOLD, 46);
		teacher_renderer.loadFont(con.PATH_FONT_BOLD, 48);
		PlayMusicAsync();
	}
	void display()  override{
		glClearColor(0.0f,0.0f,0.0f, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		titile_renderer.renderText(L"ĐỒ HỌA MÁY TÍNH", x_title, 550, 255,255,255, text_anim_fade1);
		topic_renderer.renderText(L"HẠ - THU - ĐÔNG - XUÂN", x_title + 150, 450, 255, 255, 255, text_anim_apper);
		member_renderer.renderText(L"----------------------------------", x_title + 150, 400, 255, 255, 255, text_anim_fade2);
		member_renderer.renderText(L"Mai Tiền", x_title + 320, 350, 255, 255, 255, text_anim_fade2);
		member_renderer.renderText(L"Hoàng Tú", x_title + 100, 280, 255, 255, 255, text_anim_fade3);
		topic_renderer.renderText(L"-", x_title + 370, 280, 255, 255, 255, text_anim_fade3);
		member_renderer.renderText(L"Phương Nam", x_title + 420, 280, 255, 255, 255, text_anim_fade3);
		member_renderer.renderText(L"----------------------------------", x_title + 150, 240, 255, 255, 255, text_anim_fade3);
		teacher_renderer.renderText(L"GV Phụng Nguyễn", x_title + 200, 180, 255, 255, 255, text_anim_apper);
	}
	void animText()
	{
		if (text_anim_fade1 < 1)
		{
			text_anim_fade1 += injection;
			return;
		}
		if (text_anim_fade2 < 1)
		{
			text_anim_fade2 += injection ;
			return;
		}
		if (text_anim_fade3 < 1)
		{
			text_anim_fade3 += injection;
			return;
		}
		text_anim_apper = 1;
	}
	void update() override {
		animText();
	}
	void mousePress(int button, int state, int x, int y) override {

	}
};