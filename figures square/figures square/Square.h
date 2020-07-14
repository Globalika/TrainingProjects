#include <iostream>
#include "math.h"
using namespace std;
#define PI 3.14159265

#pragma once
class Figure {
public:
	virtual double FindSquare() { return 0; }
	//Figure* arr;
protected:
	double S;
};

class Square : public Figure{
public:
	Square(double a);

	double FindSquare() override
	{
		S = a * a;
		return S;
	}
private:
	double a;
};

class Rectangle : public  Figure{
public:
	Rectangle(double a, double b);

	double FindSquare() override 
	{
		S = a * b;
		return S;
	}
private:
	double a;
	double b;
};

class Parallelogram : public Figure {
public:

	Parallelogram(double a, double b, float degree);

	double FindSquare() override
	{
		S = a * b * sin(degree * PI / 180);
		return S;
	}
private:
	double a;
	double b;
	float degree;
};

class Triangle : public Figure {
public:
	Triangle(double a, double b, double c);
	double FindSquare() override
	{
		p = (a + b + c) / 2;
		S = sqrt(p * (p - a) * (p - b) * (p - c));
		return S;
	}
private:
	double p;
	double a;
	double b;
	double c;
};


class Circle : public Figure {
public:
	Circle(float r);

	double FindSquare() override
	{
		S = PI * pow(r, 2);
		return S;
	}
	float r;
};

class Ellipse : public Figure {
public:
	Ellipse(double a, double b);
	double FindSquare() override
	{
		S = PI * a * b;
		return S;
	}
private:
	double a;
	double b;
};