#pragma once
#include"./Scene.h"
#define MAX_SNOWFLAKES 10000  // Số lượng hạt tuyết
struct Snowflake {
	float x, y; // Tọa độ của hạt tuyết
};
Snowflake snowflakes[MAX_SNOWFLAKES];
// Hàm khởi tạo tuyết
void init_snowflakes() {
	srand(time(0));
	for (int i = 0; i < MAX_SNOWFLAKES; i++) {
		snowflakes[i].x = rand() % 1000;  // X ngẫu nhiên trong khoảng [0, 1000]
		snowflakes[i].y = rand() % 600;  // Y ngẫu nhiên trong khoảng [0, 600]
	}
}
// Hàm vẽ tuyết
void draw_snowflakes() {
	glColor3f(1.0, 1.0, 1.0); // Màu trắng
	for (int i = 0; i < MAX_SNOWFLAKES; i++) {
		glBegin(GL_POINTS); // Vẽ từng điểm
		glVertex2f(snowflakes[i].x, snowflakes[i].y);
		glEnd();
	}
}

class Winter : public Scene {
private:
	int rad, x, y, a, b, h;
	int posx = 0, posy = 0;
	bool SE, E;
public:
	Winter()
	{
		PlayMusicAsync();
		// Thiết lập màu nền bầu trời
		glClearColor(0.6196078431372549, 0.9333333333333333, 0.996078431372549, 1.0);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0.0, 1200.0, 0, 1200.0); // Điều chỉnh tọa độ màn hình

		srand(time(0)); // Đảm bảo giá trị ngẫu nhiên
		for (int i = 0; i < MAX_SNOWFLAKES; i++) {
			snowflakes[i].x = rand() % 1200;  // X ngẫu nhiên trong khoảng [0, 1200]
			snowflakes[i].y = rand() % 1200;  // Y ngẫu nhiên trong khoảng [0, 1200]
		}
		
	}
	void PlayMusicAsync() {
		bool played = PlaySound(TEXT("../music/winter.wav"), NULL, SND_ASYNC);
		if (played)
			std::wcout << L"Nhạc Winter bật lên" << std::endl;
	}
	~Winter()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	///tree
	void drawCircle(int centerX, int centerY, int radius) {
		glBegin(GL_POLYGON);
		for (int i = 0; i < 360; i++) {
			float angle = i * 3.14159 / 180;  // Chuyển độ sang radian
			int x = centerX + radius * cos(angle);
			int y = centerY + radius * sin(angle);
			glVertex3i(x, y, 0);
		}
		glEnd();
	}
	void draw_circle2(float x, float y, float radius) {
		// Vẽ một vòng tròn
		int num_segments = 100;
		float angle;
		glBegin(GL_POLYGON);
		for (int i = 0; i < num_segments; i++) {
			angle = i * 2.0 * PI / num_segments;
			glVertex2f(x + cos(angle) * radius, y + sin(angle) * radius);
		}
		glEnd();
	}

	void draw_snowman(float x, float y,bool hasMouth=true,bool hasEye=true, bool hasHat = true) {
		// Thân người tuyết - ba hình tròn
		glColor3f(1.0, 1.0, 1.0);  // Màu trắng cho người tuyết
		draw_circle2(x, y, 50);  // Thân dưới
		draw_circle2(x, y + 60, 40);  // Thân giữa
		draw_circle2(x, y + 120, 30);  // Đầu

		// Vẽ mắt
		if (hasEye)
		{
			glColor3f(0.0, 0.0, 0.0);  // Màu đen cho mắt
			draw_circle2(x - 10, y + 130, 5);  // Mắt trái
			draw_circle2(x + 10, y + 130, 5);  // Mắt phải
			glColor3f(0.0, 0.0, 0.0);  // Màu đen cho mắt
			draw_circle2(x - 10, y + 130, 5);  // Mắt trái
			draw_circle2(x + 10, y + 130, 5);  // Mắt phải
		}

		if (hasMouth)
		{
			// Vẽ miệng
			glBegin(GL_LINES);
			glVertex2f(x - 15, y + 120);
			glVertex2f(x + 15, y + 120);
			glEnd();
		}
		
		if (hasHat)
		{
			// Vẽ mũ
			glColor3f(0.0, 0.0, 0.0);  // Màu đen cho mũ
			glBegin(GL_QUADS);
			glVertex2f(x - 25, y + 150); // Mũ dưới
			glVertex2f(x + 25, y + 150);
			glVertex2f(x + 20, y + 170); // Mũ trên
			glVertex2f(x - 20, y + 170);
			glEnd();
		}

		// Vẽ cái nút (hoặc cúc áo)
		glColor3f(0.0, 0.0, 0.0);  // Màu đen cho nút
		draw_circle2(x, y + 90, 5);  // Cúc áo trên
		draw_circle2(x, y + 70, 5);  // Cúc áo dưới
	}



	void drawCircle1(float cx, float cy, float radius, int num_segments) {
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(cx, cy); // Tâm của hình tròn
		for (int i = 0; i <= num_segments; i++) {
			float theta = 2.0f * PI * float(i) / float(num_segments); // Góc
			float x = radius * cosf(theta); // Tọa độ x
			float y = radius * sinf(theta); // Tọa độ y
			glVertex2f(x + cx, y + cy);
		}
		glEnd();
	}
	void drawStar(int x, int y, int radius) {
		glBegin(GL_POLYGON);
		for (int i = 0; i < 5; i++) {
			float angle = i * 2 * 3.1415926535 / 5; // Góc chia 5 phần đều
			float dx = radius * cos(angle);
			float dy = radius * sin(angle);
			glVertex2i(x + dx, y + dy);
		}
		glEnd();
	}
	void snowOnLand() {
		glColor3f(1.0, 1.0, 1.0); // Màu trắng cho tuyết

		// Khối tuyết 1
		drawCircle1(200, 350, 30, 50);  // Hình tròn lớn
		drawCircle1(220, 380, 20, 50);  // Hình tròn nhỏ
		drawCircle1(180, 370, 25, 50);  // Hình tròn trung bình

		// Khối tuyết 2
		drawCircle1(400, 320, 40, 50);
		drawCircle1(420, 350, 25, 50);
		drawCircle1(390, 370, 30, 50);

		// Khối tuyết 3
		drawCircle1(600, 330, 50, 50);
		drawCircle1(620, 370, 35, 50);
		drawCircle1(580, 360, 40, 50);

		// Khối tuyết 4
		drawCircle1(800, 310, 45, 50);
		drawCircle1(830, 350, 30, 50);
		drawCircle1(780, 340, 35, 50);

		// Khối tuyết 5
		drawCircle1(1000, 360, 50, 50);
		drawCircle1(1020, 400, 40, 50);
		drawCircle1(980, 390, 35, 50);

		// Khối tuyết 6
		drawCircle1(1100, 310, 60, 50);
		drawCircle1(1120, 360, 45, 50);
		drawCircle1(1070, 350, 40, 50);

		drawCircle1(1100, 360, 60, 50);
		drawCircle1(1120, 420, 45, 50);
		drawCircle1(1070, 400, 40, 50);

		drawCircle1(1100, 350, 60, 50);
		drawCircle1(1120, 400, 45, 50);
		drawCircle1(1070, 430, 40, 50);

		drawCircle1(1150, 550, 60, 50);
		drawCircle1(1120, 600, 45, 50);
		drawCircle1(1070, 570, 40, 50);

		drawCircle1(1100, 570, 60, 50);
		drawCircle1(1120, 620, 45, 50);
		drawCircle1(1070, 590, 40, 50);

		// Khối tuyết 7
		drawCircle1(100, 310, 40, 50);
		drawCircle1(120, 340, 25, 50);
		drawCircle1(80, 330, 30, 50);

		// Khối tuyết 8
		drawCircle1(250, 300, 35, 50);
		drawCircle1(270, 330, 20, 50);
		drawCircle1(230, 320, 25, 50);

		// Khối tuyết 9
		drawCircle1(150, 360, 50, 50);
		drawCircle1(170, 390, 30, 50);
		drawCircle1(130, 380, 35, 50);

		// Khối tuyết 10
		drawCircle1(50, 330, 30, 50);
		drawCircle1(70, 360, 20, 50);
		drawCircle1(30, 350, 25, 50);

		//    // Khối tuyết 11
		drawCircle1(300, 340, 45, 50);
		drawCircle1(320, 370, 35, 50);
		drawCircle1(280, 360, 40, 50);

		// Khối tuyết 12
		drawCircle1(100, 450, 30, 50);
		drawCircle1(120, 470, 25, 50);
		drawCircle1(80, 460, 35, 50);

		// Khối tuyết 13
		drawCircle1(200, 420, 40, 50);
		drawCircle1(220, 440, 30, 50);
		drawCircle1(190, 430, 35, 50);

		// Khối tuyết 14
		drawCircle1(250, 480, 35, 50);
		drawCircle1(270, 490, 25, 50);
		drawCircle1(240, 470, 30, 50);

		// Khối tuyết 15
		drawCircle1(50, 460, 30, 50);
		drawCircle1(70, 480, 20, 50);
		drawCircle1(30, 470, 35, 50);

		// Khối tuyết 16
		drawCircle1(300, 450, 45, 50);
		drawCircle1(320, 470, 35, 50);
		drawCircle1(280, 460, 40, 50);

		// Khối tuyết 17
		drawCircle1(350, 490, 30, 50);
		drawCircle1(370, 510, 25, 50);
		drawCircle1(340, 500, 35, 50);

		// Khối tuyết 18
		drawCircle1(400, 460, 40, 50);
		drawCircle1(420, 480, 30, 50);
		drawCircle1(390, 470, 35, 50);

		// Khối tuyết 19
		drawCircle1(450, 430, 35, 50);
		drawCircle1(470, 460, 25, 50);
		drawCircle1(440, 450, 30, 50);

		// Khối tuyết 20
		drawCircle1(500, 470, 45, 50);
		drawCircle1(520, 490, 30, 50);
		drawCircle1(490, 480, 35, 50);

		// Khối tuyết 21
		drawCircle1(550, 450, 40, 50);
		drawCircle1(570, 470, 25, 50);
		drawCircle1(540, 460, 30, 50);
	}
	void tree()
	{
		///tree2
		// Vẽ cây thông và bóng đèn
		glColor3f(0.6156863, 0, 0);  // Màu đỏ (gốc)
		glBegin(GL_POLYGON);
		glVertex3i(50 + 100, 350, 0);
		glVertex3i(70 + 100, 350, 0);
		glVertex3i(70 + 100, 400, 0);
		glVertex3i(50 + 100, 400, 0);
		glEnd();

		glColor3f(0.0, 0.5, 0.0); // Màu xanh lá cây (tán cây)

		glBegin(GL_POLYGON);
		glVertex3i(100, 400, 0);
		glVertex3i(120 + 100, 400, 0);
		glVertex3i(60 + 100, 500, 0);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3i(5 + 100, 450, 0);
		glVertex3i(115 + 100, 450, 0);
		glVertex3i(60 + 100, 550, 0);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3i(10 + 100, 500, 0);
		glVertex3i(110 + 100, 500, 0);
		glVertex3i(60 + 100, 600, 0);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3i(15 + 100, 550, 0);
		glVertex3i(105 + 100, 550, 0);
		glVertex3i(60 + 100, 650, 0);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3i(20 + 100, 600, 0);
		glVertex3i(100 + 100, 600, 0);
		glVertex3i(60 + 100, 700, 0);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3i(25 + 100, 650, 0);
		glVertex3i(95 + 100, 650, 0);
		glVertex3i(60 + 100, 750, 0);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3i(30 + 100, 700, 0);
		glVertex3i(90 + 100, 700, 0);
		glVertex3i(60 + 100, 800, 0);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3i(35 + 100, 750, 0);
		glVertex3i(85 + 100, 750, 0);
		glVertex3i(60 + 100, 850, 0);
		glEnd();
		// Bóng đỏ
		glColor3f(1.0, 0.0, 0.0);  // Màu đỏ
		drawCircle1(60 + 100, 400 + 20, 8, 50);  // Vị trí và kích thước của bóng đỏ

		// Bóng xanh dương
		glColor3f(0.0, 0.0, 1.0);  // Màu xanh dương
		drawCircle1(60 + 100 + 15, 450 + 30, 6, 50);  // Vị trí và kích thước của bóng xanh dương

		// Bóng vàng
		glColor3f(1.0, 1.0, 0.0);  // Màu vàng
		drawCircle1(60 + 100 + 30, 500 + 40, 7, 50);  // Vị trí và kích thước của bóng vàng

		// Bóng cam
		glColor3f(1.0, 0.647, 0.0);  // Màu cam
		drawCircle1(20 + 100 + 45, 550 + 50, 6, 50);  // Vị trí và kích thước của bóng cam

		// Bóng tím
		glColor3f(0.5, 0.0, 0.5);  // Màu tím
		drawCircle1(100 + 60, 600 + 60, 7, 50);  // Vị trí và kích thước của bóng tím

		// Bóng hồng
		glColor3f(1.0, 0.75, 0.8);  // Màu hồng
		drawCircle1(100 + 75, 650 + 70, 8, 50);  // Vị trí và kích thước của bóng hồng

		// Bóng trắng
		glColor3f(1.0, 1.0, 1.0);  // Màu trắng
		drawCircle1(100 + 70, 700 + 80, 6, 50);  // Vị trí và kích thước của bóng trắng

		// Bóng xanh đậm
		glColor3f(0.0, 0.0, 0.5);  // Màu xanh đậm
		drawCircle1(100 + 65, 750 + 70, 7, 50);  // Vị trí và kích thước của bóng xanh đậm

		// Ngôi sao đầu tiên (màu khác bóng đèn đỏ)
		glColor3f(0.0, 0.0, 1.0);  // Màu xanh dương
		drawStar(40 + 100, 400 + 20, 4);  // Vị trí ngôi sao, bán kính nhỏ hơn

		// Ngôi sao thứ hai (màu khác bóng đèn xanh dương)
		glColor3f(1.0, 0.0, 0.0);  // Màu đỏ
		drawStar(40 + 100 + 15, 450 + 30, 4);  // Vị trí ngôi sao, bán kính nhỏ hơn

		// Ngôi sao thứ ba (màu khác bóng đèn vàng)
		glColor3f(1.0, 1.0, 0.0);  // Màu vàng
		drawStar(30 + 100 + 30, 500 + 40, 4);  // Vị trí ngôi sao, bán kính nhỏ hơn

		// Ngôi sao thứ tư (màu khác bóng đèn cam)
		glColor3f(0.5, 0.0, 0.5);  // Màu tím
		drawStar(10 + 100 + 45, 550 + 50, 4);  // Vị trí ngôi sao, bán kính nhỏ hơn

		// Ngôi sao thứ năm (màu khác bóng đèn tím)
		glColor3f(1.0, 0.75, 0.8);  // Màu hồng
		drawStar(100 + 50, 600 + 60, 4);  // Vị trí ngôi sao, bán kính nhỏ hơn

		// Ngôi sao thứ sáu (màu khác bóng đèn hồng)
		glColor3f(1.0, 1.0, 0.0);  // Màu vàng
		drawStar(100 + 60, 650 + 70, 4);  // Vị trí ngôi sao, bán kính nhỏ hơn

		// Ngôi sao thứ bảy (màu khác bóng đèn trắng)
		glColor3f(0.0, 0.5, 0.0);  // Màu xanh lá cây
		drawStar(100 + 60, 700 + 80, 4);  // Vị trí ngôi sao, bán kính nhỏ hơn

		// Ngôi sao thứ tám (màu khác bóng đèn xanh đậm)
		glColor3f(1.0, 0.647, 0.0);  // Màu cam
		drawStar(100 + 50, 750 + 70, 4);  // Vị trí ngôi sao, bán kính nhỏ hơn

		///tree3
		glColor3f(0.6156863, 0, 0);  // Màu nâu cho thân cây thông

		glBegin(GL_POLYGON);
		glVertex3i(50 + 1100, 350, 0);
		glVertex3i(70 + 1100, 350, 0);
		glVertex3i(70 + 1100, 400, 0);
		glVertex3i(50 + 1100, 400, 0);
		glEnd();

		glColor3f(0.0, 0.5, 0.0);  // Màu xanh cho cây thông

		// Các nhánh cây thông
		glBegin(GL_POLYGON);
		glVertex3i(100 + 1100, 400, 0);
		glVertex3i(120 + 1100, 400, 0);
		glVertex3i(60 + 1100, 500, 0);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3i(5 + 1100, 450, 0);
		glVertex3i(115 + 1100, 450, 0);
		glVertex3i(60 + 1100, 550, 0);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3i(10 + 1100, 500, 0);
		glVertex3i(110 + 1100, 500, 0);
		glVertex3i(60 + 1100, 600, 0);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3i(15 + 1100, 550, 0);
		glVertex3i(105 + 1100, 550, 0);
		glVertex3i(60 + 1100, 650, 0);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3i(20 + 1100, 600, 0);
		glVertex3i(100 + 1100, 600, 0);
		glVertex3i(60 + 1100, 700, 0);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3i(25 + 1100, 650, 0);
		glVertex3i(95 + 1100, 650, 0);
		glVertex3i(60 + 1100, 750, 0);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3i(30 + 1100, 700, 0);
		glVertex3i(90 + 1100, 700, 0);
		glVertex3i(60 + 1100, 800, 0);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3i(35 + 1100, 750, 0);
		glVertex3i(85 + 1100, 750, 0);
		glVertex3i(60 + 1100, 850, 0);
		glEnd();

		glColor3f(1.0, 1.0, 1.0);  // Màu trắng cho tuyết

		drawCircle1(55 + 1100, 400, 10, 50);  // Tuyết ở thân cây
		drawCircle1(65 + 1100, 450, 8, 50);   // Tuyết ở nhánh dưới
		drawCircle1(75 + 1100, 470, 6, 50);   // Tuyết ở nhánh dưới
		//
		drawCircle1(100 + 1100, 470, 10, 50); // Tuyết ở nhánh thứ 2
		drawCircle1(110 + 1100, 520, 7, 50);  // Tuyết ở nhánh thứ 2

		drawCircle1(60 + 1100, 520, 8, 50);   // Tuyết ở nhánh thứ 3
		drawCircle1(70 + 1100, 570, 6, 50);   // Tuyết ở nhánh thứ 3

		drawCircle1(60 + 1100, 570, 7, 50);   // Tuyết ở nhánh thứ 4
		drawCircle1(40 + 1100, 620, 5, 50);   // Tuyết ở nhánh thứ 4

		drawCircle1(40 + 1100, 620, 8, 50);   // Tuyết ở nhánh thứ 5
		drawCircle1(60 + 1100, 670, 6, 50);   // Tuyết ở nhánh thứ 5

		drawCircle1(49 + 1100, 670, 9, 50);   // Tuyết ở nhánh thứ 6
		drawCircle1(55 + 1100, 720, 7, 50);   // Tuyết ở nhánh thứ 6
		//
		drawCircle1(45 + 1100, 720, 10, 50);  // Tuyết ở nhánh thứ 7
		drawCircle1(50 + 1100, 770, 8, 50);   // Tuyết ở nhánh thứ 7

		///tree4
		glColor3f(0.6156863, 0, 0);

		glBegin(GL_POLYGON);


		glVertex3i(50 + 800, 350 + 200, 0);
		glVertex3i(70 + 800, 350 + 200, 0);
		glVertex3i(70 + 800, 400 + 200, 0);
		glVertex3i(50 + 800, 400 + 200, 0);


		glEnd();

		glColor3f(0.0, 0.5, 0.0);

		glBegin(GL_POLYGON);
		glVertex3i(800, 400 + 200, 0);
		glVertex3i(120 + 800, 400 + 200, 0);
		glVertex3i(60 + 800, 500 + 200, 0);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3i(5 + 800, 450 + 200, 0);
		glVertex3i(115 + 800, 450 + 200, 0);
		glVertex3i(60 + 800, 550 + 200, 0);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3i(10 + 800, 500 + 200, 0);
		glVertex3i(110 + 800, 500 + 200, 0);
		glVertex3i(60 + 800, 600 + 200, 0);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3i(15 + 800, 550 + 200, 0);
		glVertex3i(105 + 800, 550 + 200, 0);
		glVertex3i(60 + 800, 650 + 200, 0);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3i(20 + 800, 600 + 200, 0);
		glVertex3i(100 + 800, 600 + 200, 0);
		glVertex3i(60 + 800, 700 + 200, 0);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3i(25 + 800, 650 + 200, 0);
		glVertex3i(95 + 800, 650 + 200, 0);
		glVertex3i(60 + 800, 750 + 200, 0);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3i(30 + 800, 700 + 200, 0);
		glVertex3i(90 + 800, 700 + 200, 0);
		glVertex3i(60 + 800, 800 + 200, 0);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3i(35 + 800, 750 + 200, 0);
		glVertex3i(85 + 800, 750 + 200, 0);
		glVertex3i(60 + 800, 850 + 200, 0);
		glEnd();
		glColor3f(1.0, 1.0, 1.0);
		drawCircle1(55 + 800, 400 + 200, 10, 50);  // Tuyết ở thân cây
		drawCircle1(65 + 800, 450 + 200, 8, 50);   // Tuyết ở nhánh dưới
		drawCircle1(75 + 800, 470 + 200, 6, 50);   // Tuyết ở nhánh dưới

		drawCircle1(100 + 800, 470 + 200, 10, 50); // Tuyết ở nhánh thứ 2
		drawCircle1(110 + 800, 520 + 200, 7, 50);  // Tuyết ở nhánh thứ 2

		drawCircle1(60 + 800, 520 + 200, 8, 50);   // Tuyết ở nhánh thứ 3
		drawCircle1(70 + 800, 570 + 200, 6, 50);   // Tuyết ở nhánh thứ 3

		drawCircle1(60 + 800, 570 + 200, 7, 50);   // Tuyết ở nhánh thứ 4
		drawCircle1(40 + 800, 620 + 200, 5, 50);   // Tuyết ở nhánh thứ 4

		drawCircle1(40 + 800, 620 + 200, 8, 50);   // Tuyết ở nhánh thứ 5
		drawCircle1(60 + 800, 670 + 200, 6, 50);   // Tuyết ở nhánh thứ 5

		drawCircle1(49 + 800, 670 + 200, 9, 50);   // Tuyết ở nhánh thứ 6
		drawCircle1(55 + 800, 720 + 200, 7, 50);   // Tuyết ở nhánh thứ 6

		drawCircle1(45 + 800, 720 + 200, 10, 50);  // Tuyết ở nhánh thứ 7
		drawCircle1(50 + 800, 770 + 200, 8, 50);   // Tuyết ở nhánh thứ 7

		/////tree5
		glColor3f(0.6156863, 0, 0);
		glBegin(GL_POLYGON);


		glVertex3i(50 + 950, 350 + 200, 0);
		glVertex3i(70 + 950, 350 + 200, 0);
		glVertex3i(70 + 950, 400 + 200, 0);
		glVertex3i(50 + 950, 400 + 200, 0);


		glEnd();

		glColor3f(0.0, 0.5, 0.0);

		glBegin(GL_POLYGON);
		glVertex3i(950, 400 + 200, 0);
		glVertex3i(120 + 950, 400 + 200, 0);
		glVertex3i(60 + 950, 500 + 200, 0);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3i(5 + 950, 450 + 200, 0);
		glVertex3i(115 + 950, 450 + 200, 0);
		glVertex3i(60 + 950, 550 + 200, 0);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3i(10 + 950, 500 + 200, 0);
		glVertex3i(110 + 950, 500 + 200, 0);
		glVertex3i(60 + 950, 600 + 200, 0);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3i(15 + 950, 550 + 200, 0);
		glVertex3i(105 + 950, 550 + 200, 0);
		glVertex3i(60 + 950, 650 + 200, 0);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3i(20 + 950, 600 + 200, 0);
		glVertex3i(100 + 950, 600 + 200, 0);
		glVertex3i(60 + 950, 700 + 200, 0);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3i(25 + 950, 650 + 200, 0);
		glVertex3i(95 + 950, 650 + 200, 0);
		glVertex3i(60 + 950, 750 + 200, 0);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3i(30 + 950, 700 + 200, 0);
		glVertex3i(90 + 950, 700 + 200, 0);
		glVertex3i(60 + 950, 800 + 200, 0);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3i(35 + 950, 750 + 200, 0);
		glVertex3i(85 + 950, 750 + 200, 0);
		glVertex3i(60 + 950, 850 + 200, 0);
		glEnd();

		glColor3f(1.0, 1.0, 1.0);  // Màu trắng cho tuyết
		drawCircle1(55 + 950, 400 + 200, 10, 50);  // Tuyết ở thân cây
		drawCircle1(65 + 950, 450 + 200, 8, 50);   // Tuyết ở nhánh dưới
		drawCircle1(75 + 950, 470 + 200, 6, 50);   // Tuyết ở nhánh dưới

		drawCircle1(100 + 950, 470 + 200, 10, 50); // Tuyết ở nhánh thứ 2
		drawCircle1(110 + 950, 520 + 200, 7, 50);  // Tuyết ở nhánh thứ 2

		drawCircle1(60 + 950, 520 + 200, 8, 50);   // Tuyết ở nhánh thứ 3
		drawCircle1(70 + 950, 570 + 200, 6, 50);   // Tuyết ở nhánh thứ 3

		drawCircle1(60 + 950, 570 + 200, 7, 50);   // Tuyết ở nhánh thứ 4
		drawCircle1(40 + 950, 620 + 200, 5, 50);   // Tuyết ở nhánh thứ 4

		drawCircle1(40 + 950, 620 + 200, 8, 50);   // Tuyết ở nhánh thứ 5
		drawCircle1(60 + 950, 670 + 200, 6, 50);   // Tuyết ở nhánh thứ 5

		drawCircle1(49 + 950, 670 + 200, 9, 50);   // Tuyết ở nhánh thứ 6
		drawCircle1(55 + 950, 720 + 200, 7, 50);   // Tuyết ở nhánh thứ 6

		drawCircle1(45 + 950, 720 + 200, 10, 50);  // Tuyết ở nhánh thứ 7
		drawCircle1(50 + 950, 770 + 200, 8, 50);   // Tuyết ở nhánh thứ 7

		// tree 6
		glColor3f(0.6156863, 0, 0); // Màu đỏ
		glBegin(GL_POLYGON);
		glVertex3i(50 + 850, 350 + 100, 0);  // Góc dưới bên trái
		glVertex3i(70 + 850, 350 + 100, 0);  // Góc dưới bên phải
		glVertex3i(70 + 850, 400 + 100, 0);  // Đỉnh tam giác bên phải
		glVertex3i(50 + 850, 400 + 100, 0);  // Đỉnh tam giác bên trái
		glEnd();

		// Tán cây thông màu xanh lá
		glColor3f(0.0, 0.5, 0.0); // Màu xanh lá cây

		glBegin(GL_POLYGON);
		glVertex3i(850, 400 + 100, 0);
		glVertex3i(120 + 850, 400 + 100, 0);
		glVertex3i(60 + 850, 500 + 100, 0);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3i(5 + 850, 450 + 100, 0);
		glVertex3i(115 + 850, 450 + 100, 0);
		glVertex3i(60 + 850, 550 + 100, 0);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3i(10 + 850, 500 + 100, 0);
		glVertex3i(110 + 850, 500 + 100, 0);
		glVertex3i(60 + 850, 600 + 100, 0);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3i(15 + 850, 550 + 100, 0);
		glVertex3i(105 + 850, 550 + 100, 0);
		glVertex3i(60 + 850, 650 + 100, 0);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3i(20 + 850, 600 + 100, 0);
		glVertex3i(100 + 850, 600 + 100, 0);
		glVertex3i(60 + 850, 700 + 100, 0);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3i(25 + 850, 650 + 100, 0);
		glVertex3i(95 + 850, 650 + 100, 0);
		glVertex3i(60 + 850, 750 + 100, 0);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3i(30 + 850, 700 + 100, 0);
		glVertex3i(90 + 850, 700 + 100, 0);
		glVertex3i(60 + 850, 800 + 100, 0);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3i(35 + 850, 750 + 100, 0);
		glVertex3i(85 + 850, 750 + 100, 0);
		glVertex3i(60 + 850, 850 + 100, 0);
		glEnd();
		glColor3f(1.0, 1.0, 1.0);  // Màu trắng cho tuyết
		drawCircle1(55 + 850, 400 + 100, 10, 50);  // Tuyết ở thân cây
		drawCircle1(65 + 850, 450 + 100, 8, 50);   // Tuyết ở nhánh dưới
		drawCircle1(75 + 850, 470 + 100, 6, 50);   // Tuyết ở nhánh dưới

		drawCircle1(100 + 850, 470 + 100, 10, 50); // Tuyết ở nhánh thứ 2
		drawCircle1(110 + 850, 520 + 100, 7, 50);  // Tuyết ở nhánh thứ 2

		drawCircle1(60 + 850, 520 + 100, 8, 50);   // Tuyết ở nhánh thứ 3
		drawCircle1(70 + 850, 570 + 100, 6, 50);   // Tuyết ở nhánh thứ 3

		drawCircle1(60 + 850, 570 + 100, 7, 50);   // Tuyết ở nhánh thứ 4
		drawCircle1(40 + 850, 620 + 100, 5, 50);   // Tuyết ở nhánh thứ 4

		drawCircle1(40 + 850, 620 + 100, 8, 50);   // Tuyết ở nhánh thứ 5
		drawCircle1(60 + 850, 670 + 100, 6, 50);   // Tuyết ở nhánh thứ 5

		drawCircle1(49 + 850, 670 + 100, 9, 50);   // Tuyết ở nhánh thứ 6
		drawCircle1(55 + 850, 720 + 100, 7, 50);   // Tuyết ở nhánh thứ 6

		drawCircle1(45 + 850, 720 + 100, 10, 50);  // Tuyết ở nhánh thứ 7
		drawCircle1(50 + 850, 770 + 100, 8, 50);   // Tuyết ở nhánh thứ 7

		// tree 7
		glColor3f(0.6156863, 0, 0); // Màu đỏ
		glBegin(GL_POLYGON);
		glVertex3i(50 + 750, 350 + 150, 0);  // Góc dưới bên trái
		glVertex3i(70 + 750, 350 + 150, 0);  // Góc dưới bên phải
		glVertex3i(70 + 750, 400 + 150, 0);  // Đỉnh tam giác bên phải
		glVertex3i(50 + 750, 400 + 150, 0);  // Đỉnh tam giác bên trái
		glEnd();

		// Tán cây thông màu xanh lá
		glColor3f(0.0, 0.5, 0.0); // Màu xanh lá cây

		glBegin(GL_POLYGON);
		glVertex3i(750, 400 + 150, 0);
		glVertex3i(120 + 750, 400 + 150, 0);
		glVertex3i(60 + 750, 500 + 150, 0);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3i(5 + 750, 450 + 150, 0);
		glVertex3i(115 + 750, 450 + 150, 0);
		glVertex3i(60 + 750, 550 + 150, 0);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3i(10 + 750, 500 + 150, 0);
		glVertex3i(110 + 750, 500 + 150, 0);
		glVertex3i(60 + 750, 600 + 150, 0);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3i(15 + 750, 550 + 150, 0);
		glVertex3i(105 + 750, 550 + 150, 0);
		glVertex3i(60 + 750, 650 + 150, 0);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3i(20 + 750, 600 + 150, 0);
		glVertex3i(100 + 750, 600 + 150, 0);
		glVertex3i(60 + 750, 700 + 150, 0);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3i(25 + 750, 650 + 150, 0);
		glVertex3i(95 + 750, 650 + 150, 0);
		glVertex3i(60 + 750, 750 + 150, 0);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3i(30 + 750, 700 + 150, 0);
		glVertex3i(90 + 750, 700 + 150, 0);
		glVertex3i(60 + 750, 800 + 150, 0);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3i(35 + 750, 750 + 150, 0);
		glVertex3i(85 + 750, 750 + 150, 0);
		glVertex3i(60 + 750, 850 + 150, 0);
		glEnd();
		glColor3f(1.0, 1.0, 1.0);  // Màu trắng cho tuyết
		drawCircle1(55 + 750, 400 + 150, 10, 50);  // Tuyết ở thân cây
		drawCircle1(65 + 750, 450 + 150, 8, 50);   // Tuyết ở nhánh dưới
		drawCircle1(75 + 750, 470 + 150, 6, 50);   // Tuyết ở nhánh dưới

		drawCircle1(100 + 750, 470 + 150, 10, 50); // Tuyết ở nhánh thứ 2
		drawCircle1(110 + 750, 520 + 150, 7, 50);  // Tuyết ở nhánh thứ 2

		drawCircle1(60 + 750, 520 + 150, 8, 50);   // Tuyết ở nhánh thứ 3
		drawCircle1(70 + 750, 570 + 150, 6, 50);   // Tuyết ở nhánh thứ 3

		drawCircle1(60 + 750, 570 + 150, 7, 50);   // Tuyết ở nhánh thứ 4
		drawCircle1(40 + 750, 620 + 150, 5, 50);   // Tuyết ở nhánh thứ 4

		drawCircle1(40 + 750, 620 + 150, 8, 50);   // Tuyết ở nhánh thứ 5
		drawCircle1(60 + 750, 670 + 150, 6, 50);   // Tuyết ở nhánh thứ 5

		drawCircle1(49 + 750, 670 + 150, 9, 50);   // Tuyết ở nhánh thứ 6
		drawCircle1(55 + 750, 720 + 150, 7, 50);   // Tuyết ở nhánh thứ 6

		drawCircle1(45 + 750, 720 + 150, 10, 50);  // Tuyết ở nhánh thứ 7
		drawCircle1(50 + 750, 770 + 150, 8, 50);   // Tuyết ở nhánh thứ 7

		// tree 8
		glColor3f(0.6156863, 0, 0); // Màu đỏ
		glBegin(GL_POLYGON);
		glVertex3i(50 + 1050, 350 + 70, 0);  // Góc dưới bên trái
		glVertex3i(70 + 1050, 350 + 70, 0);  // Góc dưới bên phải
		glVertex3i(70 + 1050, 400 + 70, 0);  // Đỉnh tam giác bên phải
		glVertex3i(50 + 1050, 400 + 70, 0);  // Đỉnh tam giác bên trái
		glEnd();

		// Tán cây thông màu xanh lá
		glColor3f(0.0, 0.5, 0.0); // Màu xanh lá cây

		glBegin(GL_POLYGON);
		glVertex3i(1050, 400 + 70, 0);
		glVertex3i(120 + 1050, 400 + 70, 0);
		glVertex3i(60 + 1050, 500 + 70, 0);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3i(5 + 1050, 450 + 70, 0);
		glVertex3i(115 + 1050, 450 + 70, 0);
		glVertex3i(60 + 1050, 550 + 70, 0);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3i(10 + 1050, 500 + 70, 0);
		glVertex3i(110 + 1050, 500 + 70, 0);
		glVertex3i(60 + 1050, 600 + 70, 0);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3i(15 + 1050, 550 + 70, 0);
		glVertex3i(105 + 1050, 550 + 70, 0);
		glVertex3i(60 + 1050, 650 + 70, 0);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3i(20 + 1050, 600 + 70, 0);
		glVertex3i(100 + 1050, 600 + 70, 0);
		glVertex3i(60 + 1050, 700 + 70, 0);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3i(25 + 1050, 650 + 70, 0);
		glVertex3i(95 + 1050, 650 + 70, 0);
		glVertex3i(60 + 1050, 750 + 70, 0);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3i(30 + 1050, 700 + 70, 0);
		glVertex3i(90 + 1050, 700 + 70, 0);
		glVertex3i(60 + 1050, 800 + 70, 0);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3i(35 + 1050, 750 + 70, 0);
		glVertex3i(85 + 1050, 750 + 70, 0);
		glVertex3i(60 + 1050, 850 + 70, 0);
		glEnd();

		glColor3f(1.0, 1.0, 1.0);  // Màu trắng cho tuyết
		drawCircle1(55 + 1050, 400 + 70, 10, 50);  // Tuyết ở thân cây
		drawCircle1(65 + 1050, 450 + 70, 8, 50);   // Tuyết ở nhánh dưới
		drawCircle1(75 + 1050, 470 + 70, 6, 50);   // Tuyết ở nhánh dưới

		drawCircle1(100 + 1050, 470 + 70, 10, 50); // Tuyết ở nhánh thứ 2
		drawCircle1(110 + 1050, 520 + 70, 7, 50);  // Tuyết ở nhánh thứ 2

		drawCircle1(60 + 1050, 520 + 70, 8, 50);   // Tuyết ở nhánh thứ 3
		drawCircle1(70 + 1050, 570 + 70, 6, 50);   // Tuyết ở nhánh thứ 3

		drawCircle1(60 + 1050, 570 + 70, 7, 50);   // Tuyết ở nhánh thứ 4
		drawCircle1(40 + 1050, 620 + 70, 5, 50);   // Tuyết ở nhánh thứ 4

		drawCircle1(40 + 1050, 620 + 70, 8, 50);   // Tuyết ở nhánh thứ 5
		drawCircle1(60 + 1050, 670 + 70, 6, 50);   // Tuyết ở nhánh thứ 5

		drawCircle1(49 + 1050, 670 + 70, 9, 50);   // Tuyết ở nhánh thứ 6
		drawCircle1(55 + 1050, 720 + 70, 7, 50);   // Tuyết ở nhánh thứ 6

		drawCircle1(45 + 1050, 720 + 70, 10, 50);  // Tuyết ở nhánh thứ 7
		drawCircle1(50 + 1050, 770 + 70, 8, 50);   // Tuyết ở nhánh thứ 7

	}
	///river
	void river()
	{
		glColor3f(0.9059, 0.9137, 1.0);
		glBegin(GL_POLYGON);
		glVertex3i(0, 0, 0);
		glVertex3i(1200, 0, 0);
		glVertex3i(1200, 300, 0);
		glVertex3i(0, 300, 0);
		glEnd();
	}
	//land
	void land() {
		glColor3f(0.5, 1.0, 0.5);
		glBegin(GL_POLYGON);
		glVertex3i(0, 300, 0);
		glVertex3i(1200, 300, 0);
		glVertex3i(1200, 600, 0);
		glVertex3i(0, 600, 0);
		glEnd();

		// Các khối tuyết trên đất
		snowOnLand();
	}
	void snowOnHill() {
		glColor3f(1.0, 1.0, 1.0); // Màu trắng cho tuyết

		// Khối tuyết 1, điều chỉnh vị trí sao cho nằm trên đồi
		drawCircle1(850, 760, 30, 50);  // Hình tròn lớn
		drawCircle1(870, 790, 20, 50);  // Hình tròn nhỏ
		drawCircle1(830, 780, 25, 50);  // Hình tròn trung bình

		// Khối tuyết 2, điều chỉnh vị trí sao cho nằm trên đồi
		drawCircle1(1000, 740, 40, 50);
		drawCircle1(1020, 770, 25, 50);
		drawCircle1(990, 790, 30, 50);

		// Khối tuyết 3, điều chỉnh vị trí sao cho nằm trên đồi
		drawCircle1(1150, 760, 50, 50);
		drawCircle1(1170, 800, 35, 50);
		drawCircle1(1130, 790, 40, 50);
	}
	///hill
	void hill() {
		glColor3f(0.50196, 0.25098, 0.0);
		glBegin(GL_POLYGON);

		glVertex3i(600, 600, 0);
		glVertex3i(800, 900, 0);
		glVertex3i(900, 650, 0);

		glColor3f(0.50196, 0.25098, 0.0);
		glBegin(GL_POLYGON);

		glVertex3i(900, 650, 0);
		glVertex3i(1000, 800, 0);
		glVertex3i(1100, 620, 0);

		glColor3f(0.50196, 0.25098, 0.0);
		glBegin(GL_POLYGON);

		glVertex3i(1050, 620, 0);
		glVertex3i(1200, 800, 0);
		glVertex3i(1200, 600, 0);

		snowOnHill();
		glEnd();
	}
	void draw_snow(float x_min, float x_max, float y_min, float y_max, int num_snowflakes) {
		srand(time(NULL));  // Đặt seed cho số ngẫu nhiên để có sự ngẫu nhiên khác nhau mỗi lần chạy

		for (int i = 0; i < num_snowflakes; i++) {
			// Sinh tọa độ ngẫu nhiên cho các hạt tuyết
			float x = x_min + (rand() % (int)(x_max - x_min));  // Tọa độ X ngẫu nhiên
			float y = y_min + (rand() % (int)(y_max - y_min));  // Tọa độ Y ngẫu nhiên
			float radius = 8 + (rand() % 5);  // Kích thước ngẫu nhiên cho tuyết (2 đến 5)

			glColor3f(1.0, 1.0, 1.1);  // Màu trắng cho tuyết
			draw_circle2(x, y, radius);  // Vẽ hạt tuyết
		}
	}

	void chimney() {
		glColor3f(0.55, 0.27, 0.07); // Màu nâu cho ống khói

		// Vẽ đáy ống khói (hình tròn)
		float radius = 20.0f;
		int segments = 60;

		// Vị trí của hình tròn: Đặt trung tâm của hình tròn ngay trên thân ống khói
		float centerX = 520.0f; // Tọa độ X của hình tròn (giữa thân ống khói)
		float centerY = 565.0f + radius; // Tọa độ Y của hình tròn, đặt trên phần trên cùng của hình chữ nhật

		// Vẽ đáy ống khói (hình tròn)
		draw_circle2(centerX, centerY, radius);

		// Vẽ thân ống khói (hình chữ nhật)
		glBegin(GL_QUADS);
		glVertex3i(500, 520, 0);  // Góc dưới trái
		glVertex3i(540, 520, 0);  // Góc dưới phải
		glVertex3i(540, 580, 0);  // Góc trên phải
		glVertex3i(500, 580, 0);  // Góc trên trái
		glEnd();

		// Vẽ hiệu ứng tuyết trên thân ống khói
		glColor3f(1.0, 1.0, 1.1);
		draw_snow(480, 570, 570, 730, 50);  // Hạt tuyết trên thân ống khói
	}

	///house
	void house() {
		// Nhà chính - khung gỗ
		glColor3f(0.55, 0.27, 0.07); // Màu nâu cho khung gỗ
		glBegin(GL_POLYGON); // Hình chữ nhật
		glVertex3i(200 + 250, 300, 0);
		glVertex3i(500 + 250, 300, 0);
		glVertex3i(500 + 250, 450, 0);
		glVertex3i(200 + 250, 450, 0);
		glEnd();

		// Vẽ đường thẳng có x lớn hơn tọa độ của hình chữ nhật 2 đơn vị và y bằng với tọa độ của hình chữ nhật
		glLineWidth(3.0f);
		glColor3f(0.0, 0.0, 0.0); // Màu đen cho đường thẳng
		glBegin(GL_LINES); // Vẽ đường thẳng
		glVertex3i(500 + 250, 300, 0); // Tọa độ x = 500 + 2, y = 300
		glVertex3i(500 + 250, 450, 0); // Tọa độ x = 500 + 2, y = 450
		glEnd();
		glLineWidth(3.0f);
		glColor3f(0.0, 0.0, 0.0); // Màu đen cho đường thẳng
		glBegin(GL_LINES); // Vẽ đường thẳng
		glVertex3i(200 + 250, 300, 0); // Tọa độ x = 500 + 2, y = 300
		glVertex3i(200 + 250, 450, 0); // Tọa độ x = 500 + 2, y = 450
		glEnd();

		glLineWidth(1.50f); // Giảm độ dày của đường thẳng (chọn giá trị nhỏ hơn 1.0 nếu bạn muốn đường thẳng mảnh hơn)

		// Điều chỉnh màu sắc của đường thẳng để làm giảm độ đậm
		glColor3f(0.0, 0.0, 0.0); // Màu xám nhạt cho đường thẳng
		glBegin(GL_LINES); // Vẽ đường thẳng
		glVertex3i(327 + 250, 300, 0); // Tọa độ x = 300, y = 300
		glVertex3i(327 + 250, 450, 0); // Tọa độ x = 300, y = 450
		glEnd();

		// Mái nhà - tam giác
		glColor3f(0.7, 0.2, 0.0); // Màu nâu đậm cho mái
		glBegin(GL_POLYGON); // Hình thang
		glVertex3i(180 + 250, 450, 0);   // Góc trái dưới
		glVertex3i(500 + 250, 450, 0);   // Góc phải dưới
		glVertex3i(470 + 250, 550, 0);   // Góc phải trên (thấp hơn đỉnh)
		glVertex3i(210 + 250, 550, 0);   // Góc trái trên (thấp hơn đỉnh)
		glEnd();

		// Lớp tuyết trên mái nhà
		glColor3f(1.0, 1.0, 1.0); // Màu trắng cho tuyết
		glBegin(GL_POLYGON); // Tuyết phủ dạng hình thang
		glVertex3i(180 + 250, 450, 0);   // Góc trái dưới
		glVertex3i(500 + 250, 450, 0);   // Góc phải dưới
		glVertex3i(470 + 250, 550, 0);   // Góc phải trên (thấp hơn đỉnh)
		glVertex3i(210 + 250, 550, 0); // Góc phải dưới
		glEnd();

		// Mở rộng nhà sang phải
		glColor3f(0.55, 0.27, 0.07);
		glBegin(GL_POLYGON);
		glVertex3i(500 + 250, 300, 0);
		glVertex3i(500 + 250, 300, 0);
		glVertex3i(500 + 250, 450, 0);
		glVertex3i(500 + 250, 450, 0);
		glEnd();

		// Cửa chính
		glColor3f(1.0, 0.8, 0.3); // Ánh sáng vàng
		glBegin(GL_POLYGON);
		glVertex3i(240 + 250, 300, 0);
		glVertex3i(280 + 250, 300, 0);
		glVertex3i(280 + 250, 400, 0);
		glVertex3i(240 + 250, 400, 0);
		glEnd();
		glColor3f(0.55, 0.27, 0.07); // Khung cửa
		glLineWidth(1);
		glBegin(GL_LINE_LOOP);
		glVertex3i(240 + 250, 300, 0);
		glVertex3i(280 + 250, 300, 0);
		glVertex3i(280 + 250, 400, 0);
		glVertex3i(240 + 250, 400, 0);
		glEnd();

		// Cửa sổ
		glColor3f(1.0, 0.9, 0.4); // Màu cam pha vàng
		glBegin(GL_POLYGON);
		glVertex3i(420 + 250, 350, 0); // Góc trái dưới
		glVertex3i(460 + 250, 350, 0); // Góc phải dưới
		glVertex3i(460 + 250, 400, 0); // Góc phải trên
		glVertex3i(420 + 250, 400, 0); // Góc trái trên
		glEnd();

		// Đường thẳng chia đôi cửa sổ
		glColor3f(0.0, 0.0, 0.0); // Màu cho đường chia đôi
		glLineWidth(1);
		glBegin(GL_LINES);
		glVertex3i(440 + 250, 350, 0); // Góc trái dưới của đường thẳng
		glVertex3i(440 + 250, 400, 0); // Góc phải trên của đường thẳng
		glEnd();

		// Khung cửa sổ (đổi màu thành đen)
		glColor3f(0.0, 0.0, 0.0); // Màu đen cho khung cửa sổ
		glLineWidth(2.5);
		glBegin(GL_LINE_LOOP);
		glVertex3i(420 + 250, 350, 0); // Góc trái dưới
		glVertex3i(460 + 250, 350, 0); // Góc phải dưới
		glVertex3i(460 + 250, 400, 0); // Góc phải trên
		glVertex3i(420 + 250, 400, 0); // Góc trái trên
		glEnd();

		// Cánh cửa trái mở vào trong (một phần của cửa sổ)
		glColor3f(1.0, 0.9, 0.4); // Cánh cửa trái (cam pha vàng)
		glBegin(GL_POLYGON);
		glVertex3i(420 + 250, 350, 0); // Góc trái dưới
		glVertex3i(440 + 250, 350, 0); // Góc phải dưới của cánh cửa trái
		glVertex3i(440 + 250, 400, 0); // Góc phải trên của cánh cửa trái
		glVertex3i(420 + 250, 400, 0); // Góc trái trên của cánh cửa trái
		glEnd();

		// Cánh cửa phải mở vào trong (một phần của cửa sổ)
		glColor3f(1.0, 0.9, 0.4); // Cánh cửa phải (cam pha vàng)
		glBegin(GL_POLYGON);
		glVertex3i(440 + 250, 350, 0); // Góc trái dưới của cánh cửa phải
		glVertex3i(460 + 250, 350, 0); // Góc phải dưới của cánh cửa phải
		glVertex3i(460 + 250, 400, 0); // Góc phải trên của cánh cửa phải
		glVertex3i(440 + 250, 400, 0); // Góc trái trên của cánh cửa phải
		glEnd();

		// Vẽ ống khói
		chimney();
	}
	//night
	void night_effect()
	{
		glColor3f(0, 0, 0);
		glBegin(GL_POLYGON);
		glVertex3i(0, 300, 0);
		glVertex3i(1200, 300, 0);
		glVertex3i(1200, 1200, 0);
		glVertex3i(0, 1200, 0);
		glEnd();

	}
	//mon
	void moon()
	{
		glColor3f(1, 1, 1);
		a = 500;
		b = 1000;
		x = 0;
		rad = 90;
		y = rad;
		h = 1 - rad;
		glVertex3i(x + a, y + b, 0);
		glBegin(GL_POLYGON);
		glVertex3i(x + a, y + b, 0);

		if (h >= 0)
		{
			SE = true;
			E = false;
		}
		else
		{
			E = true;
			SE = false;
		}

		while (y >= x)
		{
			if (SE)
			{
				h = h + 5 + 2 * (x - y);
				if (h >= 0)
				{
					SE = true;
					E = false;
				}
				else
				{
					E = true;
					SE = false;
				}
				x++;
				y--;
				glVertex3f(x + a, y + b, 0.0);
				glVertex3f(y + a, x + b, 0.0);
				glVertex3f(-y + a, x + b, 0.0);
				glVertex3f(-x + a, -y + b, 0.0);
				glVertex3f(-y + a, -x + b, 0.0);
				glVertex3f(y + a, -x + b, 0.0);
				glVertex3f(x + a, -y + b, 0.0);
				glVertex3f(x + a, y + b, 0.0);
				glVertex3f(-x + a, y + b, 0.0);
			}
			if (E)
			{
				h = h + 3 + 2 * x;
				if (h >= 0)
				{
					SE = true;
					E = false;
				}
				else
				{
					E = true;
					SE = false;
				}
				x++;
				glVertex3f(x + a, y + b, 0.0);

				glVertex3i(y + a, x + b, 0.0);
				glVertex3i(-y + a, x + b, 0.0);
				glVertex3i(-x + a, -y + b, 0.0);
				glVertex3i(-y + a, -x + b, 0.0);
				glVertex3i(y + a, -x + b, 0.0);
				glVertex3i(x + a, -y + b, 0.0);
				glVertex3i(x + a, y + b, 0.0);
				glVertex3i(-x + a, y + b, 0.0);
			}
		}
		glEnd();
	}
	void display() {
		glClear(GL_COLOR_BUFFER_BIT);
		night_effect();
		land();
		hill();
		tree();
		river();
		house();
		moon();
		draw_snowman(400, 300, false, true, true);  // Vẽ người tuyết ở vị trí cố định
		draw_snowman(800, 300, false, true, true);  // Vẽ người tuyết ở vị trí cố định
		draw_snowman(250, 100, false, true, false);  // Vẽ người tuyết ở vị trí cố định
		draw_snowman(270, 50, false, false, true);  // Vẽ người tuyết ở vị trí cố định
		draw_snowman(900, 350);  // Vẽ người tuyết ở vị trí khác
		draw_snowman(1100, 100,false,false,true);  // Vẽ người tuyết ở vị trí khác
		draw_snowman(1120, 50, false, true, false);  // Vẽ người tuyết ở vị trí khác
		glPushMatrix();
		glTranslatef(posx, 0, 0);
		glPopMatrix();
		draw_snowflakes(); // Vẽ tuyết
	}
	void update() {
		// Cập nhật vị trí của các hạt tuyết
		for (int i = 0; i < MAX_SNOWFLAKES; i++) {
			snowflakes[i].y -= 2; // Di chuyển hạt tuyết xuống dưới
			if (snowflakes[i].y < 0) {
				snowflakes[i].y = 1200; // Đặt lại ở phía trên màn hình
				snowflakes[i].x = rand() % 1200; // X ngẫu nhiên trong khoảng [0, 1200]
			}
		}
	}
	void mousePress(int, int, int, int) {

	}
};