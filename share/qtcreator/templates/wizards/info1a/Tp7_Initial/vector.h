#pragma once

struct Vector {
	double x,y;
};

// Sum
Vector operator+(Vector a, Vector b);

// Difference
Vector operator-(Vector a, Vector b);

// Multiplication vector*scalar
Vector operator*(Vector a, double lambda);
Vector operator/(Vector a, double lambda);

// Scalar product
double operator*(Vector a, Vector b);

// Norm
double norm(Vector a);

// Rotation (angle in degrees)
Vector rotate(Vector a, double angle);
