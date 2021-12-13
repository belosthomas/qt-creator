// Imagine++ project
// Project:  Tennis
// Student(s): 

#include <Imagine/Graphics.h>
using namespace Imagine;

// Keyboard handling.
// For now, do not care how it works.
// Return in sens1 (resp. sens2) -1, 1 or 0 for player 1
// (resp. player 2) according to pressed keys
void keyboard(int& sens1, int& sens2) {
	static bool left1=false,right1=false,left2=false,right2=false;
	Event e;
	do {
		getEvent(0,e);
		if(e.type==EVT_KEY_ON || e.type==EVT_KEY_OFF) {
			bool push=(e.type==EVT_KEY_ON);
			switch (e.key) {
			case 's': case 'S':
				left1=push;
				break;
			case 'd': case 'D':
				right1=push;
				break;
			case 'k': case 'K':
				left2=push;
				break;
			case 'l': case 'L':
				right2=push;
				break;
			}
		}
	} while(e.type!=EVT_NONE);
	sens1=(left1?-1:(right1?1:0));
	sens2=(left2?-1:(right2?1:0));
}

int main() {
	openWindow(256,256);
	// Position and speed of ball
	int xb=128,
	    yb=20,
	    ub=2,
	    vb=3;
    // Main loop
	while (true) {
		// Display ball
		fillRect(xb-3,yb-3,7,7,RED);
		// Pause
		milliSleep(20);
		// Erase ball
		fillRect(xb-3,yb-3,7,7,WHITE);
		// Bouncing
		if(xb+ub > 253)
			ub=-ub;
		// Update ball position
		xb+=ub;
		yb+=vb;
	}
	endGraphics();
	return 0;
}
