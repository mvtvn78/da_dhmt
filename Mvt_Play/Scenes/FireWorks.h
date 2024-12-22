#pragma once
#include"./Scene.h"
#include<math.h>
#include"./Summary.h"
class FireWorks : public Scene {
private:
	float radius = 5;    // Bán kính
	int id; 
	Scene* sm_scene;
	std::vector< Particle> paritcles;
	static const int particleCount = 200;
	const float angleIcrement = (PI * 2) / particleCount;
	const float power = 2.5f;
	bool oneShot = false;
	std::vector < std::pair<int, int>> posYear = {
		  {171, 727}, {189, 700}, {213, 666}, {232, 640}, {271, 663},
		{299, 691}, {329, 725}, {231, 596}, {225, 550}, {432, 724},
		{430, 681}, {432, 625}, {430, 575}, {432, 541}, {507, 539},
		{579, 540}, {501, 630}, {579, 632}, {501, 730}, {585, 727},
		{767, 726}, {731, 659}, {697, 586}, {682, 544}, {823, 664},
		{857, 589}, {883, 545}, {747, 630}, {800, 629}, {990, 724},
		{988, 667}, {989, 622}, {989, 575}, {985, 537}, {1054, 726},
		{1132, 726}, {1141, 664}, {1081, 634}, {1102, 611}, {1133, 581},
		{1161, 541}, {160, 380}, {220, 383}, {285, 384}, {328, 385},
		{299, 327}, {231, 281}, {165, 247}, {166, 202}, {229, 200},
		{295, 200}, {346, 201}, {431, 399}, {426, 311}, {432, 206},
		{511, 400}, {594, 399}, {600, 315}, {602, 210}, {518, 209},
		{698, 410}, {772, 410}, {853, 416}, {892, 416}, {850, 348},
		{801, 304}, {718, 257}, {718, 213}, {792, 215}, {846, 216},
		{895, 216}, {994, 429}, {1054, 429}, {1118, 429}, {1175, 436},
		{996, 369}, {994, 335}, {1058, 330}, {1109, 332}, {1161, 333},
		{1172, 305}, {1171, 238}, {1113, 213}, {1025, 215}, {990, 214}
	};
	std::vector < std::pair<int, int>> posP = {
		 {458, 633}, {553, 635}, {657, 633}, {776, 637}, {844, 600},
		{861, 538}, {857, 491}, {816, 448}, {461, 575}, {458, 523},
		{455, 476}, {455, 413}, {453, 364}, {448, 309}, {454, 257},
		{455, 205}, {498, 418}, {575, 417}, {647, 415}, {718, 418}
	};
	std::vector < std::pair<int, int>> posT = {
		  {398, 603}, {502, 605}, {597, 605}, {693, 609}, {842, 609},
		{596, 529}, {600, 481}, {596, 429}, {596, 376}, {592, 328},
		{590, 279}, {768, 608}, {454, 610}, {550, 603}, {632, 598}
	};
	std::vector < std::pair<int, int>> posL = {
		{421, 661}, {422, 587}, {420, 516}, {416, 471}, {416, 423},
		{409, 363}, {406, 311}, {408, 258}, {506, 245}, {569, 242},
		{641, 251}, {700, 251}, {790, 251}, {849, 257}
	};
	std::vector < std::pair<int, int>> posC = {
		 {861, 570}, {840, 619}, {791, 646}, {731, 663}, {683, 672},
		{616, 672}, {561, 656}, {495, 621}, {474, 575}, {466, 537},
		{457, 489}, {458, 430}, {458, 367}, {469, 323}, {485, 270},
		{501, 230}, {534, 209}, {579, 197}, {643, 186}, {695, 193},
		{764, 198}, {807, 241}, {827, 290}, {844, 323}, {849, 341}
	};
	std::vector < std::pair<int, int>> posRandom = {
		{167, 737}, {152, 689}, {226, 689}, {853, 711}, {824, 647},
		{923, 634}, {465, 594}, {476, 621}, {498, 598}, {1064, 546},
		{983, 457}, {1080, 457}, {189, 356}, {221, 291}, {287, 350},
		{705, 323}, {637, 257}, {699, 227}, {714, 276}

	};
	std::vector < std::pair<int, int>> posRandom1 = {
		{114, 110}, {98, 207}, {168, 135}, {877, 116}, {902, 172},
		{907, 132}, {441, 580}, {485, 628}, {522, 596}, {519, 563},
		{457, 521}, {894, 650}, {967, 721}, {1065, 699}, {1030, 637},
		{126, 694}, {107, 606}, {144, 494}, {165, 621}, {977, 482},
		{893, 395}, {905, 328}, {1004, 285}, {929, 417}
	};
	std::vector < std::pair<int, int>> posHeart = {
		{612, 536}, {660, 576}, {709, 614}, {778, 652}, {831, 643},
		{853, 637}, {888, 594}, {910, 553}, {915, 499}, {915, 449},
		{908, 393}, {872, 326}, {808, 259}, {754, 216}, {652, 185},
		{627, 156}, {552, 566}, {515, 605}, {463, 630}, {428, 621},
		{401, 611}, {384, 590}, {370, 560}, {364, 521}, {363, 479},
		{367, 438}, {380, 401}, {394, 352}, {421, 312}, {460, 254},
		{488, 208}, {559, 180}, {696, 178}
	};
public:
	FireWorks() {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		// định nghĩa khung vẽ
		gluOrtho2D(0, con.SCREEN_WIDTH, 0, con.SCREEN_HEIGHT);
		if (!con.DEBUG)
		{
			PlayMusicAsync();
			id = 0;
			radius = 0.5f;
			fire();
		}
	}
	// Thật là phong cách
	void fire()
	{
		switch (id)
		{
			case 0:
				for (std::pair<int, int> el : posRandom)
				{
					instanceParticle(el.first, el.second);
					instanceParticle(el.first, el.second);
				}
				break;
			case 1:
				for (std::pair<int, int> el : posT)
				{
					instanceParticle(el.first, el.second);
					instanceParticle(el.first, el.second);
				}
				break;
			case 2:
				for (std::pair<int, int> el : posL)
				{
					instanceParticle(el.first, el.second);
					instanceParticle(el.first, el.second);
				}
				break;
			case 3 :
				for (std::pair<int, int> el : posP)
				{
					instanceParticle(el.first, el.second);
					instanceParticle(el.first, el.second);
				}
				break;
			case 4:
				for (std::pair<int, int> el : posC)
				{
					instanceParticle(el.first, el.second);
					instanceParticle(el.first, el.second);
				}
				break;
			case 5:
				for (std::pair<int, int> el : posHeart)
				{
					instanceParticle(el.first, el.second);
					instanceParticle(el.first, el.second);
				}
				break;
			case 6:
				for (std::pair<int, int> el : posRandom1)
				{
					instanceParticle(el.first, el.second);
					instanceParticle(el.first, el.second);
				}
				break;
			case 7 :
				for (std::pair<int, int> el : posYear)
				{
					instanceParticle(el.first, el.second);
					instanceParticle(el.first, el.second);
				}
				break;
			
			default : 
				break;
		}
	}
	void PlayMusicAsync() {
		bool played = PlaySound(TEXT("../music/pro1.wav"), NULL, SND_ASYNC );
		if (played)
			std::wcout << L"Hiệu ứng Pháo hoa" << std::endl;
	}
	
	void display()  override {
		if (id == -1)
		{
			sm_scene->display();
			return;
		}
		 // Bật blend để hỗ trợ alpha
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Vẽ hình vuông
		if (!con.DEBUG)
		{
			glBegin(GL_QUADS);
			glColor4f(0.0f, 0.0f, 0.0f, 0.1f);
			glVertex2f(0, 0); // Đỉnh dưới bên trái
			glVertex2f(con.SCREEN_WIDTH, 0);  // Đỉnh dưới bên phải
			glVertex2f(con.SCREEN_WIDTH, con.SCREEN_HEIGHT);   // Đỉnh trên bên phải
			glVertex2f(0, con.SCREEN_HEIGHT);  // Đỉnh trên bên trái	
			glEnd();
		}
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
		if (!con.DEBUG)
		{
			int cntCurrent = paritcles.size();
			int cnt = 0;
			for (int i = 0; i < paritcles.size(); ++i)
			{
				if (paritcles[i].getAlpha() > 0)
					paritcles[i].update();
				else
				{
					paritcles.erase(paritcles.begin() + i);
					cnt++;
				}
			}
			if (cnt == cntCurrent && id != -1)
			{
				id++;
				fire();
				if (id > 8) id = -1;
			}
		}
		if (id == -1 && !oneShot)
		{
			sm_scene = new Summary();
			oneShot = true;
		}
		if (id == -1)
		{
			sm_scene->update();
		}
	}
	void mousePress(int button, int state, int x, int y) override {
		if (con.DEBUG)
		{
			if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
			{
				std::wcout << x << " " << y << "\n";
				instanceParticle(x, y);
				instanceParticle(x, y);
				instanceParticle(x, y);
			}
		}
	}
	void instanceParticle(int x , int y) {
		MyRGB temp = getRandomColor();
		for (int i = 0; i < particleCount; ++i)
		{
			Particle a(x, y, temp.R, temp.G, temp.B, 1,
				cos(angleIcrement * i) * randomNumber() * power,
				sin(angleIcrement * i) * randomNumber() * power,
				radius);
			paritcles.push_back(a);
		}
	}	
	// 0 to 1
	double randomNumber() {
		return ((double)rand()) / RAND_MAX;
	}
};
