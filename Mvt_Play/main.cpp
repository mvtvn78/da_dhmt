#include "./Scenes/Main.h"
#include<io.h>
#include<fcntl.h>
int main(int argc, char** argv)
{
	// Tiếng Việt
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stdout), _O_U16TEXT);
	MainScene scene(argc,argv);
	return 0;
}