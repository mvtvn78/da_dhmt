#pragma once
#include"./Scene.h"
#include<math.h>

class FireWorks : public Scene {
private:
	float radius;    // Bán kính
	std::vector< Particle> paritcles;
	static const int particleCount = 250;
	const float angleIcrement = (PI * 2) / particleCount;
	const float power = 6;
public:
	FireWorks() {
		PlayMusicAsync();
	}
	void PlayMusicAsync() {
		bool played = PlaySound(TEXT("../music/fireworks.wav"), NULL, SND_ASYNC | SND_LOOP);
		if (played)
			std::wcout << L"Hiệu ứng Pháo hoa" << std::endl;
	}
	void display()  override {
		 // Bật blend để hỗ trợ alpha
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Vẽ hình vuông

		glBegin(GL_QUADS);
			glColor4f(0.0f, 0.0f, 0.0f, 0.1f); // Màu đỏ
			glVertex2f(0, 0); // Đỉnh dưới bên trái
			glVertex2f(con.SCREEN_WIDTH,0);  // Đỉnh dưới bên phải
			glVertex2f(con.SCREEN_WIDTH, con.SCREEN_HEIGHT);   // Đỉnh trên bên phải
			glVertex2f(0, con.SCREEN_HEIGHT);  // Đỉnh trên bên trái	
		glEnd();
		glDisable(GL_BLEND);
		
		for (int i = 0; i < paritcles.size(); ++i)
		{
			if (paritcles[i].getAlpha() > 0)
				paritcles[i].draw();
			else
				paritcles.erase(paritcles.begin() + i);
		}
	}
	void update() override {
		for (int i = 0; i < paritcles.size(); ++i)
		{
			if (paritcles[i].getAlpha() > 0)
				paritcles[i].update();
			else
				paritcles.erase(paritcles.begin() + i);
		}
	}
	void mousePress(int button, int state, int x, int y) override {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			std::wcout << x << " " << y << "\n";
			instanceParticle(x, y);
		}
	}
	void instanceParticle(int x , int y) {
		MyRGB temp = getRandomColor();
		for (int i = 0; i < particleCount; ++i)
		{
			Particle a(x, y, temp.R, temp.G, temp.B, 1,
				cos(angleIcrement * i) * randomNumber() * power,
				sin(angleIcrement * i) * randomNumber() * power,
				5);
			paritcles.push_back(a);
		}
	}
	// 0 to 1
	double randomNumber() {
		return ((double)rand()) / RAND_MAX;
	}
};
