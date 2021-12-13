// Imagine++ project
// Project:  Mastermind
// Student(s): 

#include<iostream>
#include <string>
using namespace std;

// Get combination from keyboard
// (nbcases digits in a sequence)
// Beware: add check length and values
void getCombination(int trial, int combi[5]) {
    cout << "Your trial #" << trial <<" : ";
    string s;
    cin >> s;
    for(int i=0; i<5; i++)
        combi[i]=s[i]-'0';
}

int main() {
	cout << "MASTERMIND" << endl;
	return 0;
}
