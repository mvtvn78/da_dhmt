#pragma once
#include"./Scene.h"
class Autumn :public Scene {
private:
    double r = 0.2, s = 0.3;
    int i;
    float tx = 10, bx = 10;
    double sunRadius = 35.0;  // Bán kính của mặt trời
    int angleOffsetLeft = 360;  // Góc khuyết phía bên trái của hình tròn
    int angleOffsetRight = 180;   // Góc khuyết phía bên phải của hình tròn
    int changeCount = 0;  // Biến đếm số lần thay đổi
    float timeElapsed = 0.0f;  // Thời gian trôi qua
    float maxAngle = 5.0f;  // Góc xoay tối đa cho phần đầu con thỏ
    float maxTime = 1330.0f;  // Giới hạn thời gian (10 giây)
    bool isMoving = true;   // Cờ để kiểm tra liệu có tiếp tục chuyển động hay không
    static Autumn* instance;
    bool oneShot = false;
public:
	Autumn() {
        instance = this;
		PlayMusicAsync();
		// Đặt tọa độ (0,0) ở góc trái dưới
		glMatrixMode(GL_PROJECTION); // Chọn ma trận chiếu
		glLoadIdentity(); // Đặt lại ma trận về mặc định
		glOrtho(-210, 210, -220, 310, -210, 310);
        glClearColor(0, 0, 0, 1.0); 
	}
	void PlayMusicAsync() {
		bool played = PlaySound(TEXT("../music/fall-autumn.wav"), NULL, SND_ASYNC | SND_LOOP);
		if (played)
			std::wcout << L"Nhạc Thu bật lên" << std::endl;
	}
    void cloud(double x, double y) {
        glBegin(GL_TRIANGLE_FAN);
        for (i = 0; i < 360; i++) {
            x = x + cos((i * 3.14) / 180) * r;
            y = y + sin((i * 3.14) / 180) * r;
            glVertex2d(x, y);
        }
        glEnd();
    }

    void sun(double centerX, double centerY) {
        double radius = 70.0;  // Bán kính mặt trời lớn
        glBegin(GL_TRIANGLE_FAN);
        glVertex2d(centerX, centerY);
        for (int i = 0; i <= 360; i++) {
            double x = centerX + radius * cos(i * PI / 180);
            double y = centerY + radius * sin(i * PI / 180);
            glVertex2d(x, y);
        }
        glEnd();
    }

    void sun1(double centerX, double centerY) {
        glBegin(GL_TRIANGLE_FAN);
        glVertex2d(centerX, centerY);

        // Vẽ phần của hình tròn còn lại (khuyết dần từ 180 độ về 0 độ)
        for (int i = 0; i <= angleOffsetLeft; i++) {
            double x = centerX + sunRadius * cos(i * PI / 180);
            double y = centerY + sunRadius * sin(i * PI / 180);
            glVertex2d(x, y);
        }

        for (int i = 360; i >= angleOffsetRight; i--) {
            double x = centerX + sunRadius * cos(i * PI / 180);
            double y = centerY + sunRadius * sin(i * PI / 180);
            glVertex2d(x, y);
        }

        glEnd();
    }

    // Hàm vẽ hình elip
    void drawEllipse(float x, float y, float radiusX, float radiusY) {
        int i;
        int lineAmount = 100;
        GLfloat twicePi = 2.0f * PI;
        glBegin(GL_POLYGON);
        for (i = 0; i <= lineAmount; i++) {
            glVertex2f(
                x + (radiusX * cos(i * twicePi / lineAmount)),
                y + (radiusY * sin(i * twicePi / lineAmount))
            );
        }
        glEnd();
    }
    // Hàm vẽ elip với phần bên trong được tô màu
    void drawFilledEllipse(float x, float y, float radiusX, float radiusY, float angle) {
        int num_segments = 100; // Số lượng điểm để vẽ elip mượt mà
        float rad = angle * (3.1415926 / 180.0); // Chuyển góc sang radian

        glBegin(GL_TRIANGLE_FAN); // Dùng Triangle Fan để tô màu bên trong
        glVertex2f(x, y); // Tâm elip

        for (int i = 0; i <= num_segments; i++) {
            float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);

            // Tính tọa độ trên đường elip
            float dx = radiusX * cosf(theta);
            float dy = radiusY * sinf(theta);

            // Xoay tọa độ qua góc rad
            float rotatedX = dx * cos(rad) - dy * sin(rad);
            float rotatedY = dx * sin(rad) + dy * cos(rad);

            // Dịch chuyển elip đến vị trí (x, y)
            glVertex2f(rotatedX + x, rotatedY + y);
        }
        glEnd();
    }


    // Vẽ con thỏ với khả năng di chuyển và thu nhỏ
    void drawRabbit(float x, float y, float scale) {

        glPushMatrix(); // Lưu trạng thái ma trận hiện tại

        // Di chuyển con thỏ đến vị trí (x, y)
        glTranslatef(x, y, 0.0f);

        // Áp dụng phép biến đổi tỉ lệ
        glScalef(scale, scale, 1.0f);

        // Vẽ con thỏ
        glColor3f(1.0f, 1.0f, 1.0f);
        drawFilledEllipse(-30.0f, 55.0f, 10.0f, 65.0f, -20.0f);

        glColor3f(1.0f, 0.8f, 0.9f);
        drawEllipse(7.0f, 95.0f, 25.0f, 30.0f);
        drawEllipse(18.0f, 80.0f, 20.0f, 30.0f);
        drawEllipse(0.0f, 43.0f, 26.0f, 80.0f);
        drawEllipse(0.0f, 22.0f, 28.0f, 80.0f);
        drawEllipse(0.0f, 0.0f, 30.0f, 80.0f);

        glColor3f(1.0f, 1.0f, 1.0f);
        drawEllipse(-5.0f, -60.0f, 12.0f, 20.0f);

        glColor3f(1.0f, 0.0f, 0.0f);
        drawEllipse(20.0f, 93.0f, 3.0f, 5.0f);

        glColor3f(1.0f, 1.0f, 1.0f);
        drawEllipse(0.0f, 50.0f, 10.0f, 60.0f);

        glPopMatrix(); // Khôi phục trạng thái ma trận trước đó
    }
    void drawRabbit1(float offsetX, float offsetY) {
        glPushMatrix();  // Lưu lại ma trận hiện tại

        // Dịch chuyển tất cả đối tượng vẽ theo vector (offsetX, offsetY)
        glTranslatef(offsetX, offsetY, 0.0f);
        // Tạo chuyển động gật đầu nhẹ theo trục Y
        float angle = maxAngle * sin(timeElapsed * 3.14159f / 180.0f); // Sử dụng sin() để tạo chuyển động xoay
        glRotatef(angle, 0.0f, 0.0f, 1.0f);  // Quay phần đầu theo trục Z (xoay nhẹ lên xuống)

        glColor3f(1.0f, 1.0f, 1.0f);
        drawFilledEllipse(67.0f, 42.0f, 11.0f, 50.0f, -10.0f); // Góc 45 độ
        glColor3f(1.0f, 1.0f, 1.0f);
        drawEllipse(127.0f, -10.0f, 10.0f, 20.0f);
        glColor3f(1.0f, 0.8f, 0.9f);
        drawFilledEllipse(75.0f, 3.0f, 25.0f, 40.0f, -30.0f);
        drawEllipse(95.0f, 00.0f, 30.0f, 39.0f);
        drawEllipse(100.0f, 00.0f, 30.0f, 40.0f);

        glColor3f(1.0f, 0.2f, 0.0f); // Màu đỏ nhạt
        drawEllipse(62.0f, -5.0f, 2.0f, 4.0f);

        glColor3f(1.0f, 1.0f, 1.0f);
        drawFilledEllipse(90.0f, 52.0f, 12.0f, 40.0f, -23.0f); // Góc 45 độ

        glPopMatrix();  // Khôi phục lại ma trận trước khi dịch chuyển
    }
	void display() {
        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_BLEND);  // Bật chế độ blend
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  // Thiết lập hàm trộn màu
        //-------------------SUN-------------------------
    //    glColor3ub(255, 215, 0);  // Màu vàng cho mặt trời
        glColor4f(0.922f, 0.675f, 0.071f, 0.05f);
        drawEllipse(-10.0f, 100.0f, 90.0f, 180.0f);
        glColor4f(0.922f, 0.675f, 0.071f, 0.1f);
        drawEllipse(-10.0f, 100.0f, 86.0f, 172.0f);
        glColor4f(0.922f, 0.675f, 0.071f, 0.2f);
        drawEllipse(-10.0f, 100.0f, 84.0f, 168.0f);
        glColor4f(0.922f, 0.675f, 0.071f, 0.4f);
        drawEllipse(-10.0f, 100.0f, 82.0f, 164.0f);

        glColor3f(0.922f, 0.675f, 0.071f);
        drawEllipse(-10.0f, 100.0f, 80.0f, 160.0f);
        //    sun(-10, 180);  // Vẽ mặt trời lớn

        glColor3ub(210, 105, 30);  // Màu nâu cho mặt trời nhỏ
        sun1(-10, -70);  // Vẽ mặt trời nhỏ với hiệu ứng bị khuyết dần

        //-------------------------------------------CLOUD-------------------------------------------------
        glPushMatrix();
        glColor3f(0.996f, 0.8f, 0.459f);
        glTranslatef(tx, 0, 0);
        cloud(0, 185 - 70);
        cloud(15, 180 - 70);
        cloud(10, 175 - 70);
        cloud(-2, 185 - 70);

        cloud(15, 180 - 70);
        cloud(30, 185 - 70);
        cloud(35, 175 - 70);
        cloud(14, 190 - 70);

        cloud(-20, 160 - 70);
        cloud(-30, 165 - 70);
        cloud(-25, 170 - 70);
        cloud(-34, 165 - 70);

        cloud(-80, 250 - 70);
        cloud(-95, 245 - 70);
        cloud(-90, 240 - 70);
        cloud(-90, 243 - 70);
        cloud(-75, 243 - 70);

        cloud(-60, 250 - 70);
        cloud(-80, 245 - 70);
        cloud(-75, 240 - 70);
        cloud(-75, 243 - 70);
        cloud(-55, 243 - 70);

        glPopMatrix();
        

        drawRabbit1(-20.0f, -70.0f);
        drawRabbit(-80.0f, -50.0f, 0.8f);
	}
    static void updateCake(int value) {
        instance->handleCake();
    }
    void handleCake() {
        if (changeCount < 10) {  // Thực hiện hiệu ứng 5 lần
            angleOffsetLeft -= 36;  // Mỗi lần thay đổi, giảm 36 độ từ phía bên trái
            angleOffsetRight += 36; // Mỗi lần thay đổi, giảm 36 độ từ phía bên phải
            changeCount++;          // Đếm số lần thay đổi
            glutPostRedisplay();    // Cập nhật lại màn hình
        }
        // Lặp lại cập nhật mỗi 2 giây (2000 ms)
        glutTimerFunc(2000, updateCake, 0);
    }
	void update() {
        // update cloud
        tx += .05;
        //    if (tx > 200) tx = -200;
        if (tx > 50) tx = -50;
        if (!oneShot)
        {
            updateCake(0);
            oneShot = true;
        }
        if (isMoving) {
            // Cập nhật thời gian theo chu kỳ
            timeElapsed += 1.0f;  // Tăng thời gian mỗi frame, có thể thay đổi để điều chỉnh tốc độ

            // Nếu thời gian vượt qua 10 giây, dừng chuyển động
            if (timeElapsed > maxTime) {
                timeElapsed = maxTime;  // Giới hạn thời gian không vượt quá maxTime
                isMoving = false;  // Dừng chuyển động
            }
            // Nếu không dừng lại, tiếp tục yêu cầu vẽ lại
        }
	}
	void mousePress(int, int, int, int) {

	}
};
// gán nullptr cho instance 
Autumn* Autumn::instance = nullptr;