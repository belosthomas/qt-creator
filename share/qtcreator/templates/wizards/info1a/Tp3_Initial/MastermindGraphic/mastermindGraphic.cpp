// Imagine++ project
// Project:  Mastermind Graphic
// Student(s): 

#include<iostream>
using namespace std;

#include<Imagine/Graphics.h>
using namespace Imagine;


// Game parameters
const int nbcases = 5;   // Number of pieces to guess
const int nbcol = 6;     // Number of colors
const int nbtrials = 10; // Number of trials for the player
const int ncmax = 7;     // Max number of colors

/////////////////////////////////////////////////////////////////////////
// Display functions

Color colors[ncmax+1]={RED,GREEN,BLUE,YELLOW,MAGENTA,CYAN,BLACK,WHITE};
char key_color[ncmax+1]={'r','g','b','y','m','c','n',' '};
const int c_size = 24;
const int gap = 10;

// Display cursor (next piece to input)
void displayCursor(int n, int line, Color c) {
	drawCircle(n*c_size+c_size/2,line*c_size+c_size/2,c_size/2,c);
}

// Display combination
void displayCombination(int line, int combi[nbcases]) {
	for(int i=0; i<nbcases; ++i)
		fillCircle(i*c_size+c_size/2, line*c_size+c_size/2,
                   c_size/2, colors[combi[i]]);
}

// Display hints
void displayHints(int good, int bad, int line) {
	for(int i=0; i<good; ++i)
		fillCircle(nbcases*c_size+gap+i*c_size/2+c_size/4,
                   line*c_size+c_size/2,c_size/4, BLACK);
	for(int i=0; i<bad; ++i)
		drawCircle(nbcases*c_size+gap+(good+i)*c_size/2+c_size/4,
                   line*c_size+c_size/2,c_size/4, BLACK);
}

// Display a horizontal separation line
void displaySeparation(int line) {
	drawLine(0, (2*line+1)*c_size/2, 500, (2*line+1)*c_size/2, BLACK);
}

// Display a user guide with a key for each color.
void displayKeys(int line) {
	char c[2] = {0,0};
	for(int i=0; i<nbcol; ++i) {
		fillCircle(i*c_size+c_size/2,line*c_size+c_size/2,
                   c_size/2, colors[i]);
		c[0] = key_color[i];
        drawString(i*c_size, (line+1)*c_size+c_size/2,c, BLACK);
	}
}

/////////////////////////////////////////////////////////////////////////
// Keyboard handling
// Return color between 0 and nbcol-1,
// -1 means backspace
// -2 means unknown key
int keyboard() {
	int k = getKey();
	if(k==KEY_BACK) // Backspace
		return -1;
	for(int i=0; i<nbcol; i++)
		if(k==key_color[i] || k==key_color[i]-'a'+'A')
			return i;
	return -2; // Wrong key
}

//////////////////////////////////////////////////////////////////////////
// Fonctions Mastermind

//
//
// Insert function for generation of random combination
//
//

void getCombination(int trial, int combi[nbcases]) {
	for(int j=0; j<nbcases; ++j)
		combi[j]=ncmax;
	for(int j=0; j<nbcases; ++j){
		displayCursor(j, trial, Color(160,160,160));
		int c;
		do 
			c = keyboard();
		while(c<0);
			combi[j]=c;
		displayCursor(j, trial, WHITE);
		displayCombination(trial,combi);
	}
}

//
//
// Insert function of comparison of combinations
//
//

int main() {
    // Generate combination
	// TODO

	// Initialize display
	int width = nbcases*c_size + gap + nbcases*c_size/2;
	int height = (nbtrials+6)*c_size;
	openWindow(width,height,"Master Mind");
	displaySeparation(nbtrials);
	displaySeparation(nbtrials+3);
    displayKeys(nbtrials+4);

    // Display solution for debugging
	//display(nbtrials+1, solution);

	// Game
	bool found=false;
	// TODO
	if(found)
        drawString(0,(nbtrials+3)*c_size,"WIN",RED);
	else
        drawString(0,(nbtrials+3)*c_size,"Game over",RED);
	endGraphics();
	return 0;
}
