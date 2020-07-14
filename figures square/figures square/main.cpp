#include <iostream>
#include "math.h"
#include "Square.h"
using namespace std;

int main()
{
	Square g(4);
	cout << g.FindSquare() << endl;
	Parallelogram l(3, 6, 45);
	cout << l.FindSquare() << endl;
	Triangle c(3, 4, 5);
	cout << c.FindSquare() << endl;
	Circle e(4);
	cout << e.FindSquare() << endl;
	Ellipse ff(2,5);
	cout << ff.FindSquare() << endl;
	int n = 4;
	Figure** arr = new Figure*[n];// = { &g,&l,&c,&ff };

	arr[0] = &g;
	arr[1] = &l;
	arr[2] = &c;
	arr[3] = &ff;
	cout << (*arr[3]).FindSquare() << endl;

	return 0;
}