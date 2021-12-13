// Imagine++ project
// Project:  Tp1Supplement
// Author:   renaud

#include<Imagine/Graphics.h>
using namespace Imagine;

int main()
{
	openWindow(256,256);
	int i=20,j=0;//Position
	int di=2,dj=2;//Speed
	while(true) {
		fillRect(i,j,4,4,RED);
		milliSleep(10);
		if(i+di > 250) {
			di=-di;
		}
		int ni=i+di;
		if(j+dj > 250) {
			dj=-dj;
		}
		int nj=j+dj;
		fillRect(i,j,4,4,WHITE);
		i=ni;
		j=nj;
	}
	endGraphics();
	return 0;
}
