#include <iostream>

using namespace std;

int main()
{
	int i, n;
	cout << "enter simple number\n";
	cin >> n;
	
	if(n==1)
	{
		cout << "number is not simple\n";
	}
	else if(n == 2)
		cout << "number simple\n";
	else if (n == 3)
		cout << "number simple\n";

	
	for(i=2;i<=(int)n/2;i++)
	{
		if (n % i == 0) 
		{
			cout << "number is not simple\n";
			break;
		}

		if (i == (int)n / 2)
		{
			cout << "number simple\n";
			break;
		}
	}
}