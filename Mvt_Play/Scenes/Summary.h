#pragma once
#include"./Scene.h"	
class Summary : public Scene
{
private:
	TextRenderer titile_renderer;
	TextRenderer text_summary;
	float y = 0;
	int maxHigh = 800;
	float speed = 0.75f;
	bool isEndAnimText = false;
public:
	Summary()
	{
		PlayMusicAsync();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		// định nghĩa khung vẽ
		gluOrtho2D(0, con.SCREEN_WIDTH, 0, con.SCREEN_HEIGHT);
		titile_renderer.loadFont(con.PATH_FONT_BOLD, 80);
		text_summary.loadFont(con.PATH_FONT_REGULAR, 40);
	}
	void PlayMusicAsync() {
		bool played = PlaySound(TEXT("../music/motnammoibinhan.wav"), NULL, SND_ASYNC | SND_LOOP);
		if (played)
			std::wcout << L"Nhạc Summary bật lên" << std::endl;
	}
	void display()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		handleDisplay();
	}
	void handleDisplay()
	{
		if (isEndAnimText)
		{
			titile_renderer.renderText(L"Một Năm Mới", 350, 500, 1, 1, 1, 1);
			titile_renderer.renderText(L"Thật là bình an nhé !", 200, 300, 1, 1, 1, 1);
			return;
		}
		titile_renderer.renderText(L"CHÚC MỪNG NĂM MỚI", 150, 700 + y - maxHigh, 1, 1, 1, 1);
		text_summary.renderText(L"Nhóm Thật Là Phong Cách", 420, 650 + y - maxHigh, 1, 1, 1, 1);
		text_summary.renderText(L"Xin gửi tặng.", 550, 600 + y - maxHigh, 1, 1, 1, 1);
		text_summary.renderText(L"Các thành viên :", 420, 550 + y - maxHigh, 1, 1, 1, 1);
		text_summary.renderText(L"Mai Văn Tiền", 450, 500 + y - maxHigh, 1, 1, 1, 1);
		text_summary.renderText(L"Hoàng Đức Công Tú", 450, 450 + y - maxHigh, 1, 1, 1, 1);
		text_summary.renderText(L"Chử Trần Phương Nam", 450, 400 + y - maxHigh, 1, 1, 1, 1);
		text_summary.renderText(L"Các cảnh đảm nhiệm :", 420, 350 + y - maxHigh, 1, 1, 1, 1);
		text_summary.renderText(L"Xuân - Tiền", 450, 300 + y - maxHigh, 1, 1, 1, 1);
		text_summary.renderText(L"Thu - Nam", 450, 250 + y - maxHigh, 1, 1, 1, 1);
		text_summary.renderText(L"Đông - Nam", 450, 200 + y - maxHigh, 1, 1, 1, 1);
		text_summary.renderText(L"Hạ - Tú", 450, 150 + y - maxHigh, 1, 1, 1, 1);
	}
	void update()
	{
		handleUpdate();
	}
	void mousePress(int, int, int, int)
	{

	}
	void handleUpdate()
	{
		//std::wcout << y << std::endl;
		if (y >= 1400)
		{
			isEndAnimText = true;
			return;
		}
		y += speed;
	}
};