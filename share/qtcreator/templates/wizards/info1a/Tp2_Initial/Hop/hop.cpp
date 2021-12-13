// Imagine++ project
// Project:  Hop
// Author:   renaud
// Date:     2007/10/9

#include <iostream>
using namespace std;

int add(int a,int b) {
	int c;
	c=a+b;
	return c;
}

void triple1(int a) {
	a=a*3;
}

void triple2(int& a) {
	a=a*3;
}

int main() {
	int i,j=2,k;
	i=3;
	k=add(i,j);
	triple1(i);
	triple2(i);
	return 0;
}
