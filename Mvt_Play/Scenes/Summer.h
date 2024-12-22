#pragma once
#include "./Scene.h"
class Summer : public Scene
{
	private:
		//Biến toàn cục vẽ mây
		float cloudX1 = 0; // Tọa độ X cho các đám mây

		//Biến toàn cục vẽ nhân vật Nam
		float characterX = 140; // Tọa độ X trung tâm nhân vật
		float characterY = 60; // Tọa độ Y trung tâm nhân vật

		//Biến toàn cục vẽ nhân vật nữ
		float characterX1 = 50; // Tọa độ X trung tâm nhân vật
		float characterY1 = 130; // Tọa độ Y trung tâm nhân vật

		// Biến toàn cục để điều khiển vị trí của con diều
		float offsetX = 0.0f;
		float offsetY = 0.0f;
		float speed = 0.1f; // Tốc độ di chuyển
		//Biến toàn cục vẽ con diều 2
		float heartCenterX = 400.0f; // Tọa độ tâm X của trái tim
		float heartCenterY = 400.0f; // Tọa độ tâm Y của trái tim
		float heartSize = 43.0f;     // Kích thước trái tim   
public:
	Summer() {
		glClearColor(0.529, 0.808, 0.980, 1.0); // Màu nền (xanh da trời nhạt)
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0.0, 500.0, 0.0, 500.0); // Hệ tọa độ từ (0, 0) đến (500, 500)
		PlayMusicAsync();
	}
	void PlayMusicAsync() {
		bool played = PlaySound(TEXT("../music/summer.wav"), NULL, SND_ASYNC);
		if (played)
			std::wcout << L"Nhạc Summer bật lên" << std::endl;
	}
	// Hàm vẽ hình elip
	void drawEllipse(float cx, float cy, float rx, float ry, int r, int g, int b) {
		glColor3ub(r, g, b); // Màu sắc
		int num_segments = 100; // Số điểm trên elip
		glBegin(GL_POLYGON);
		for (int i = 0; i < num_segments; i++) {
			float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
			float x = rx * cosf(theta);
			float y = ry * sinf(theta);
			glVertex2f(x + cx, y + cy);
		}
		glEnd();
	}
	//Hình tròn cho mây
	void drawCircle(float cx, float cy, float r) {
		int num_segments = 100; // Số điểm để vẽ hình tròn (càng nhiều thì càng mịn)
		glBegin(GL_POLYGON);
		for (int i = 0; i < num_segments; i++) {
			float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
			float x = r * cosf(theta);
			float y = r * sinf(theta);
			glVertex2f(x + cx, y + cy);
		}
		glEnd();
	}
	//Hình tròn thường
	void drawCircle3(float x, float y, float radius) {
		glBegin(GL_TRIANGLE_FAN);
		for (int i = 0; i <= 360; i++) {
			float angle = i * 3.14159f / 180.0f;
			float dx = radius * cos(angle);
			float dy = radius * sin(angle);
			glVertex2f(x + dx, y + dy);
		}
		glEnd();
	}
	//Vẽ hình chữ nhật
	void drawRectangle(float x1, float y1, float x2, float y2) {
		glBegin(GL_QUADS);
		glVertex2f(x1, y1);
		glVertex2f(x2, y1);
		glVertex2f(x2, y2);
		glVertex2f(x1, y2);
		glEnd();
	}
	//Vẽ đoạn thẳng
	void drawThickLine(float x1, float y1, float x2, float y2, float width) {
		float angle = atan2(y2 - y1, x2 - x1); // Tính góc nghiêng
		float dx = sin(angle) * width / 2.0;   // Độ dời theo trục x
		float dy = cos(angle) * width / 2.0;   // Độ dời theo trục y

		glBegin(GL_QUADS); // Vẽ hình chữ nhật
		glVertex2f(x1 - dx, y1 + dy);
		glVertex2f(x1 + dx, y1 - dy);
		glVertex2f(x2 + dx, y2 - dy);
		glVertex2f(x2 - dx, y2 + dy);
		glEnd();
	}
	//Vẽ tam giác
	void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
		glBegin(GL_TRIANGLES); // Bắt đầu vẽ tam giác
		glVertex2f(x1, y1);    // Đỉnh thứ nhất
		glVertex2f(x2, y2);    // Đỉnh thứ hai
		glVertex2f(x3, y3);    // Đỉnh thứ ba
		glEnd();               // Kết thúc vẽ
	}
	// Vẽ hình tam giác với màu
	void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, int r, int g, int b) {
		glColor3f(r / 255.0f, g / 255.0f, b / 255.0f); // Màu sắc
		glBegin(GL_TRIANGLES);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
		glVertex2f(x3, y3);
		glEnd();
	}
	//Nhân vật Nam
	void drawCharacter() {
		// Đầu
		glColor3ub(255, 220, 185); // Màu da
		drawCircle3(characterX, characterY + 80, 30);

		// Tóc
		glColor3ub(139, 69, 19); // Màu nâu
		drawCircle3(characterX, characterY + 80, 30);

		//Cổ
		glColor3ub(255, 220, 185); // Màu da
		drawRectangle(characterX - 7, characterY + 42, characterX + 7, characterY + 52);

		//tay trai
		glColor3ub(255, 220, 185);

		// Vai đến khuỷu tay
		drawThickLine(characterX - 10, characterY + 32, characterX - 30, characterY + 12, 12.0); // 10.0 là độ rộng

		// Khuỷu tay đến bàn tay
		drawThickLine(characterX - 28, characterY + 18, characterX - 30, characterY + 0, 10.7);

		// Bàn tay
		drawCircle3(characterX - 30, characterY - 5, 8); // Tăng kích thước bàn tay để cân đối

		// Thân
		glColor3ub(255, 165, 0); // Màu áo (cam)
		drawRectangle(characterX - 15, characterY - 12, characterX + 15, characterY + 42);
		// Tay áo
		glColor3ub(255, 165, 0);
		drawThickLine(characterX - 5, characterY + 37, characterX - 25, characterY + 17, 16.0); // 10.0 là độ rộng

		//Quần
		glColor3ub(66, 129, 245);
		drawRectangle(characterX - 15, characterY - 22, characterX + 15, characterY + 2);

		//tay phải
		glColor3ub(255, 220, 185);

		// Vai đến khuỷu tay
		drawThickLine(characterX + 30, characterY + 12, characterX + 10, characterY + 32, 12.0); // 10.0 là độ rộng

		// Khuỷu tay đến bàn tay
		drawThickLine(characterX + 25, characterY + 8, characterX + 39, characterY + 23, 10.7);

		// Bàn tay
		drawCircle3(characterX + 42, characterY + 28, 8); // Tăng kích thước bàn tay để cân đối

		// Tay áo
		glColor3ub(255, 165, 0);
		drawThickLine(characterX + 25, characterY + 17, characterX + 5, characterY + 37, 16.0); // 10.0 là độ rộng

		// Chân trái
		glColor3ub(255, 192, 203); // Màu hồng
		drawRectangle(characterX - 13, characterY - 50, characterX - 3, characterY - 22);

		// Chân phải
		glColor3ub(255, 192, 203); // Màu hồng
		drawRectangle(characterX + 3, characterY - 50, characterX + 13, characterY - 22);

		// Giày
		glColor3ub(0, 0, 0); // Màu đen
		drawRectangle(characterX - 13, characterY - 50, characterX - 3, characterY - 45); // Giày trái
		drawRectangle(characterX + 3, characterY - 50, characterX + 13, characterY - 45); // Giày phải

		//Chia ống quần
		glColor4ub(96, 245, 66, 128);
		drawRectangle(characterX - 1, characterY - 22, characterX + 1, characterY - 7);
	}
	//Vẽ nhân vật nữ
	void drawCharacter2() {
		// Đầu
		glColor3ub(255, 220, 185); // Màu da
		drawCircle3(characterX1, characterY1 + 64, 30);

		// Tóc dài
		glColor3ub(139, 69, 19); // Màu nâu
		drawCircle3(characterX1, characterY1 + 74, 27); // Tóc trên đầu
		drawRectangle(characterX1 - 30, characterY1 + 34, characterX1 + 30, characterY1 + 64); // Tóc dài

		// Cổ
		glColor3ub(255, 220, 185); // Màu da
		drawRectangle(characterX1 - 7, characterY1 + 24, characterX1 + 7, characterY1 + 34);

		// Tay trái
		glColor3ub(255, 220, 185);
		drawThickLine(characterX1 - 10, characterY1 + 16, characterX1 - 30, characterY1 - 4, 12.0); // Vai đến khuỷu tay
		drawThickLine(characterX1 - 28, characterY1 + 0, characterX1 - 30, characterY1 + -18, 10.7); // Khuỷu tay đến bàn tay
		drawCircle3(characterX1 - 30, characterY1 - 23, 8); // Bàn tay

		// Váy
		glColor3ub(255, 105, 180); // Màu hồng (váy)
		drawRectangle(characterX1 - 15, characterY1 - 25, characterX1 + 15, characterY1 - 10);
		drawTriangle(characterX1, characterY1 + 25, characterX1 - 20, characterY1 - 40, characterX1 + 20, characterY1 - 40);

		// Tay phải
		glColor3ub(255, 220, 185);
		drawThickLine(characterX1 + 30, characterY1 - 6, characterX1 + 10, characterY1 + 14, 12.0); // Vai đến khuỷu tay
		drawThickLine(characterX1 + 25, characterY1 + -10, characterX1 + 39, characterY1 + 5, 10.7); // Khuỷu tay đến bàn tay
		drawCircle3(characterX1 + 42, characterY1 + 10, 8); // Bàn tay

		// Thân (áo)
		glColor3ub(255, 165, 0); // Màu áo (cam)
		drawRectangle(characterX1 - 15, characterY1 - 20, characterX1 + 15, characterY1 + 24);

		// Chân trái
		glColor3ub(255, 220, 185); // Màu da
		drawRectangle(characterX1 - 13, characterY1 - 70, characterX1 - 3, characterY1 - 40);

		// Chân phải
		glColor3ub(255, 220, 185); // Màu da
		drawRectangle(characterX1 + 3, characterY1 - 70, characterX1 + 13, characterY1 - 40);

		// Giày
		glColor3ub(0, 0, 0); // Màu đen
		drawRectangle(characterX1 - 13, characterY1 - 70, characterX1 - 3, characterY1 - 65); // Giày trái
		drawRectangle(characterX1 + 3, characterY1 - 70, characterX1 + 13, characterY1 - 65); // Giày phải
	}
	//Vẽ con diều 1
	void drawKite() {
		// Tọa độ các đỉnh của hình thoi
		float centerX = 300.0f + offsetX, centerY = 400.0f - offsetY; // Tâm hình thoi
		float scaleFactor = 0.5f; // Tỷ lệ thu nhỏ (ví dụ: nhỏ hơn 50%)

		// Tính toán lại tọa độ các đỉnh sau khi thu nhỏ
		float topX = centerX, topY = centerY + 100.0f * scaleFactor;    // Đỉnh trên
		float bottomX = centerX, bottomY = centerY - 100.0f * scaleFactor; // Đỉnh dưới
		float leftX = centerX - 80.0f * scaleFactor, leftY = centerY;   // Đỉnh trái
		float rightX = centerX + 80.0f * scaleFactor, rightY = centerY; // Đỉnh phải

		// Vẽ các phần bên trong (4 tam giác)
		drawTriangle(centerX, centerY, topX, topY, leftX, leftY, 254, 120, 50);  // Tam giác trên (màu hồng)
		drawTriangle(centerX, centerY, topX, topY, rightX, rightY, 254, 255, 141); // Tam giác trên phải (màu vàng)
		drawTriangle(centerX, centerY, bottomX, bottomY, leftX, leftY, 254, 0, 0); // Tam giác dưới trái (màu đỏ)
		drawTriangle(centerX, centerY, bottomX, bottomY, rightX, rightY, 28, 136, 254); // Tam giác dưới phải (màu xanh)

		// Vẽ khung của con diều
		glColor3f(0.0f, 0.0f, 0.0f); // Màu đen
		glLineWidth(2.0); // Độ dày đường viền
		glBegin(GL_LINE_LOOP);
		glVertex2f(topX, topY);    // Đỉnh trên
		glVertex2f(leftX, leftY);  // Đỉnh trái
		glVertex2f(bottomX, bottomY); // Đỉnh dưới
		glVertex2f(rightX, rightY); // Đỉnh phải
		glEnd();

		// Vẽ các đường chéo bên trong
		glBegin(GL_LINES);
		glVertex2f(topX, topY);
		glVertex2f(bottomX, bottomY); // Đường dọc
		glVertex2f(leftX, leftY);
		glVertex2f(rightX, rightY); // Đường ngang
		glEnd();
	}
	//Vẽ đuôi diều (Áp dụng cho cả 2 con diều)
	void drawKiteTail(float startX, float startY, int numSegments, int color[3], float time) {
		float segmentHeight = 20.0f;          // Chiều cao mỗi đoạn
		float segmentWidth = 10.0f;           // Chiều rộng mỗi đoạn
		float amplitude = 5.0f;              // Biên độ dao động của đường cong
		float frequency = 0.5f;               // Tần số dao động
		float waveSpeed = 2.0f;               // Tốc độ chuyển động sóng

		// Tô màu cho toàn bộ dây
		glColor3f(color[0] / 255.0f, color[1] / 255.0f, color[2] / 255.0f);

		for (int i = 0; i < numSegments; i++) {
			// Tạo dao động theo thời gian
			float offsetX = amplitude * sin(frequency * i + waveSpeed * time); // Biến đổi với thời gian
			float x1 = startX - segmentWidth / 2 + offsetX;
			float x2 = startX + segmentWidth / 2 + offsetX;
			float y1 = startY - i * segmentHeight;
			float y2 = y1 - segmentHeight;

			glBegin(GL_QUADS);
			glVertex2f(x1, y1);
			glVertex2f(x2, y1);
			glVertex2f(x2, y2);
			glVertex2f(x1, y2);
			glEnd();
		}
	}
	// Vẽ dây diều 1
	void drawKiteString() {
		glColor3f(0.0f, 0.0f, 0.0f); // Màu đen
		glLineWidth(2.0); // Độ dày dây
		glBegin(GL_LINES);
		glVertex2f(300.0f + offsetX, 400.0f - offsetY); // Điểm cuối của đuôi
		glVertex2f(180.0f, 80.0f); // Điểm kết thúc dây
		glEnd();
	}

	//Diều thứ 2
	void drawKiteHeart(float centerX, float centerY, float size) {
		// Vẽ phần cung tròn của trái tim
		glBegin(GL_TRIANGLE_FAN);
		glColor3ub(255, 105, 180); // Màu đỏ cho trái tim
		glVertex2f(centerX, centerY); // Điểm trung tâm trái tim

		for (float angle = 0; angle <= 180; angle += 1.0f) {
			float x1 = centerX - size * 0.5f + size * 0.5f * cos(angle * PI / 180.0f);
			float y1 = centerY + size * 0.5f * sin(angle * PI / 180.0f);
			glVertex2f(x1, y1);
		}

		for (float angle = 180; angle >= 0; angle -= 1.0f) {
			float x2 = centerX + size * 0.5f - size * 0.5f * cos(angle * PI / 180.0f);
			float y2 = centerY + size * 0.5f * sin(angle * PI / 180.0f);
			glVertex2f(x2, y2);
		}
		glEnd();

		// Vẽ phần tam giác nhọn của trái tim
		glBegin(GL_TRIANGLES);
		glVertex2f(centerX - size, centerY);         // Đỉnh trái
		glVertex2f(centerX + size, centerY);         // Đỉnh phải
		glVertex2f(centerX, centerY - size * 1.5f);  // Đỉnh nhọn
		glEnd();
	}
	// Vẽ dây diều 2
	void drawKiteString2() {
		glColor3f(0.0f, 0.0f, 0.0f); // Màu đen
		glLineWidth(2.0); // Độ dày dây
		glBegin(GL_LINES);
		glVertex2f(400.0f + offsetX, 380.0f - offsetY); // Điểm cuối của đuôi
		glVertex2f(80.0f, 130.0f); // Điểm kết thúc dây
		glEnd();
	}
	void display() override
	{
		glClear(GL_COLOR_BUFFER_BIT);
		// Bật chế độ blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//Vẽ mây ----------------------------------------------------//
		glColor3ub(255, 255, 255); // Màu trắng
		// Mây thứ 1
		drawCircle(30 + cloudX1, 430, 35);
		drawCircle(60 + cloudX1, 430, 45);
		drawCircle(90 + cloudX1, 430, 35);

		// Mây thứ 2
		drawCircle(150 + cloudX1, 400, 20);
		drawCircle(180 + cloudX1, 400, 30);
		drawCircle(210 + cloudX1, 400, 20);

		// Mây thứ 3
		drawCircle(250 + cloudX1, 450, 25);
		drawCircle(280 + cloudX1, 450, 35);
		drawCircle(310 + cloudX1, 450, 25);

		// Mây thứ 4
		drawCircle(400 + cloudX1, 420, 35);
		drawCircle(430 + cloudX1, 420, 45);
		drawCircle(470 + cloudX1, 420, 35);

		//Vẽ đất ------------------------------------------------------/ (như background)
			// Vẽ mặt đất (nền cỏ)
		glColor3ub(50, 205, 50); // Xanh lá
		glBegin(GL_POLYGON);
		glVertex2d(0, 0);
		glVertex2d(500, 0);
		glVertex2d(500, 200);
		glVertex2d(0, 200);
		glEnd();

		//Vẽ cỏ ----------------------------------------------------------/
		  //Cỏ ở xa ---------------------------------------------------/
			// Bụi cỏ đầu tiên
		drawEllipse(10, 200, 30, 50, 34, 139, 34);  // Elip 1 - xanh đậm
		drawEllipse(40, 200, 40, 60, 34, 139, 34);  // Elip 2
		drawEllipse(70, 200, 30, 50, 34, 139, 34); // Elip 3

		// Bụi cỏ thứ hai
		drawEllipse(120, 180, 30, 50, 34, 139, 34);  // Elip 1 - xanh đậm
		drawEllipse(150, 180, 40, 60, 34, 139, 34);  // Elip 2
		drawEllipse(180, 180, 30, 50, 34, 139, 34); // Elip 3

		// Bụi cỏ thứ ba
		drawEllipse(220, 190, 30, 50, 34, 139, 34);  // Elip 1 - xanh đậm
		drawEllipse(250, 190, 40, 60, 34, 139, 34);  // Elip 2
		drawEllipse(280, 190, 30, 50, 34, 139, 34); // Elip 3

		// Bụi cỏ thứ tư
		drawEllipse(320, 200, 30, 50, 34, 139, 34);  // Elip 1 - xanh đậm
		drawEllipse(350, 200, 40, 60, 34, 139, 34);  // Elip 2
		drawEllipse(380, 200, 30, 50, 34, 139, 34); // Elip 3

		// Bụi cỏ thứ năm
		drawEllipse(420, 190, 30, 50, 34, 139, 34);  // Elip 1 - xanh đậm
		drawEllipse(450, 190, 40, 60, 34, 139, 34);  // Elip 2
		drawEllipse(480, 190, 30, 50, 34, 139, 34); // Elip 3

		//Cỏ ở gần ----------------------------------------------------/
		   //1
		drawEllipse(-10, 160, 20, 40, 0, 100, 0); // Elip 3
		drawEllipse(20, 160, 30, 50, 0, 100, 0); // Elip 3
		drawEllipse(50, 160, 20, 40, 0, 100, 0); // Elip 3
		//1
		drawEllipse(80, 150, 20, 40, 0, 100, 0); // Elip 3
		drawEllipse(110, 150, 30, 50, 0, 100, 0); // Elip 3
		drawEllipse(140, 150, 20, 40, 0, 100, 0); // Elip 3
		//1
		drawEllipse(170, 160, 20, 40, 0, 100, 0); // Elip 3
		drawEllipse(200, 160, 30, 50, 0, 100, 0); // Elip 3
		drawEllipse(230, 160, 20, 40, 0, 100, 0); // Elip 3
		//1
		drawEllipse(260, 170, 20, 40, 0, 100, 0); // Elip 3
		drawEllipse(290, 170, 30, 50, 0, 100, 0); // Elip 3
		drawEllipse(320, 170, 20, 40, 0, 100, 0); // Elip 3
		//1
		drawEllipse(350, 160, 20, 40, 0, 100, 0); // Elip 3
		drawEllipse(380, 160, 30, 50, 0, 100, 0); // Elip 3
		drawEllipse(410, 160, 20, 40, 0, 100, 0); // Elip 3
		//1
		drawEllipse(440, 150, 20, 40, 0, 100, 0); // Elip 3
		drawEllipse(470, 150, 30, 50, 0, 100, 0); // Elip 3
		drawEllipse(500, 150, 20, 40, 0, 100, 0); // Elip 3

		//Vẽ đất ----------------------------------------------------/ (Sử dụng blend)
			// Vẽ mặt đất (nền cỏ)
		glColor3ub(50, 205, 50); // Xanh lá
		glBegin(GL_POLYGON);
		glVertex2d(0, 0);
		glVertex2d(500, 0);
		glVertex2d(500, 150);
		glVertex2d(0, 150);
		glEnd();

		glColor4ub(255, 255, 0, 70);  // Màu vàng với độ trong suốt
		glBegin(GL_POLYGON);
		glVertex2d(0, 0);
		glVertex2d(500, 0);
		glVertex2d(500, 150);
		glVertex2d(0, 150);
		glEnd();

		glColor4ub(255, 255, 0, 80);  // Màu vàng với độ trong suốt
		glBegin(GL_POLYGON);
		glVertex2d(0, 0);
		glVertex2d(500, 0);
		glVertex2d(500, 150);
		glVertex2d(0, 150);
		glEnd();

		glColor4ub(50, 205, 50, 128); // Xanh lá
		glBegin(GL_POLYGON);
		glVertex2d(0, 0);
		glVertex2d(500, 0);
		glVertex2d(500, 150);
		glVertex2d(0, 150);
		glEnd();

		// Vẽ con diều
		//Tạo màu
		int tailColor[3] = { 255, 100, 100 };
		int tailColor1[3] = { 246,178,56 };
		int tailColor2[3] = { 33,204,71 };

		// Time chuyển động cho đuôi diều (Cả 2 diều)
		float time = glutGet(GLUT_ELAPSED_TIME) / 1500.0f;

		// Vẽ đuôi diều với chuyển động (con diều 1)
		drawKiteTail(300 + offsetX, 380 - offsetY, 7, tailColor, time);
		drawKiteTail(285 + offsetX, 393 - offsetY, 6, tailColor1, time);
		drawKiteTail(315 + offsetX, 393 - offsetY, 6, tailColor2, time);
		// Vẽ con diều 1
		drawKite();
		// Vẽ dây diều 1
		drawKiteString();

		//Màu cho đuôi diều 2
		int tailColor5[3] = { 8,100,241 };
		int tailColor6[3] = { 243,113,240 };
		int tailColor7[3] = { 246,252,148 };
		int tailColor8[3] = { 248,159,106 };

		// Vẽ đuôi diều với chuyển động (con diều thứ 2)
		drawKiteTail(385 + offsetX, 390 - offsetY, 6, tailColor5, time);
		drawKiteTail(415 + offsetX, 390 - offsetY, 6, tailColor6, time);
		drawKiteTail(370 + offsetX, 410 - offsetY, 6, tailColor7, time);
		drawKiteTail(430 + offsetX, 410 - offsetY, 6, tailColor8, time);

		// Vẽ con diều 2
		drawKiteHeart(heartCenterX + offsetX, heartCenterY - offsetY, heartSize);
		// Vẽ đuôi diều 2
		drawKiteString2();

		// Vẽ nhân vật nam
		drawCharacter();
		// Vẽ nhân vật nữ
		drawCharacter2();
		glDisable(GL_BLEND);
		//Vẽ bụi
		//drawParticles();
	}
	void update() override {
		//Chuyển động của mây -------------------------------/
		cloudX1 += 0.1f; // Tăng tọa độ X của mây (tốc độ 2 pixel mỗi lần cập nhật)
		if (cloudX1 > 500) // Nếu mây đi quá màn hình, quay lại từ đầu
			cloudX1 = -100;
		// Thời gian mỗi chu kỳ (tính bằng giây)
		float period = 4.0f; // Chu kỳ 2 giây

		//Chuyển động của diều ----------------------------------/
		  // Tính toán offsetX theo chu kỳ thời gian
		offsetX = 25.0f * sin(2 * PI * (glutGet(GLUT_ELAPSED_TIME) / 1000.0f) / period);
		offsetY = 25.0f * sin(speed * glutGet(GLUT_ELAPSED_TIME) / 1000.0f); // Tạo hiệu ứng sóng

		// Giới hạn phạm vi di chuyển của con diều
		if (offsetX > 25.0f) {
			offsetX = 25.0f; // Đảm bảo không vượt quá 25
		}
		else if (offsetX < -25.0f) {
			offsetX = -25.0f; // Đảm bảo không vượt quá -20
		}
	}
	void mousePress(int, int, int, int)  override{

	}
};