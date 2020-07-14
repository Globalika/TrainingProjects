#include <iostream>
#include "math.h"
#include "Square.h"
using namespace std;

Square::Square(double a) {
	this->a = a;
}

Rectangle::Rectangle(double a, double b) {
	this->a = a;
	this->b = b;
}

Parallelogram::Parallelogram(double a, double b, float degree) {
	this->a = a;
	this->b = b;
	this->degree = degree;
}

Triangle::Triangle(double a, double b, double c) {
	this->a = a;
	this->b = b;
	this->c = c;
}

Circle::Circle(float r) {
	this->r = r;
}

Ellipse::Ellipse(double a, double b) {
	this->a = a;
	this->b = b;
}