#pragma once
#include<vector>
#include<cstdlib> 

struct MyRGB {
	float R;
	float G;
	float B;
	MyRGB(float r ,float g , float b) {
		R = r; G = g; B = b;
	}
};
std::vector<MyRGB> colors = {
	//--> x / 255 

	//RGB: (102, 255, 0)  bright greens
	MyRGB(0.4f, 1, 0),
	//RGB: (133, 1, 1) deep reds
	MyRGB(0.52156862745f, 0.00392156862f, 0.00392156862f),
	//RGB: (0, 0, 255) blues
	MyRGB(0, 0,1),
	//RGB: (255, 255, 0) yellows
	MyRGB(1, 1,0),
	//RGB: (228, 228, 228) silvery white
	MyRGB(0.89411764705f, 0.89411764705f, 0.89411764705f),
	//RGB: (230, 230, 250) lavendar color
	MyRGB(0.90196078431f, 0.90196078431f, 0.98039215686f),
};
MyRGB getRandomColor() {
	// 0 -> n-1
	int index = rand() % (colors.size());
	/*std::wcout << "INDEX COLOR : "<<index << std::endl;*/
	return colors[index];
}
