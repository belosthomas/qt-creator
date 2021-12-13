// Imagine++ project
// Project:  Tp6
// Student(s): 

#include <Imagine/Graphics.h>
using namespace Imagine;

int main() {
	const int W=300,H=200;
	openWindow(W,H);

	byte grey[W*H];
    // Fill grey here
	putGreyImage(0,0,grey,W,H);

	endGraphics();
	return 0;
}
