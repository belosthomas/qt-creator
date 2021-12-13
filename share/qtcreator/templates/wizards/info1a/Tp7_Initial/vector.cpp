#include "vector.h"
#include <cmath>
using namespace std;

Vector operator+(Vector a, Vector b) {
	Vector c;
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	return c;
}

Vector operator-(Vector a, Vector b) {
	Vector c;
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	return c;
}

Vector operator*(Vector a, double lambda) {
	Vector c;
	c.x = a.x * lambda;
	c.y = a.y * lambda;
	return c;
}

Vector operator/(Vector a, double lambda) {
	Vector c;
	c.x = a.x / lambda;
	c.y = a.y / lambda;
	return c;
}

double operator*(Vector a, Vector b) {
	return a.x * b.x + a.y * b.y;
}

double norm(Vector a) {
	return sqrt( a.x * a.x + a.y * a.y );
}

Vector rotate(Vector a, double angle) {
	angle *= M_PI / 180;
	Vector c;
	double co = cos(angle);
	double si = sin(angle);
	c.x = co * a.x + si * a.y;
	c.y = - si * a.x + co * a.y;
	return c;
}
