#include <iostream>

using namespace std;

bool isPrime(int n)
{
	if (n == 1) {
		return false;
	}
	else if (n == 2 || n == 3) {
		return true;
	}
	else {

		for (int i = 2; i <= (int)n / 2; i++)
		{
			if (n % i == 0)
			{
				return false;
			}

			if (i == (int)n / 2)
			{
				return true;
			}
		}
	}
}

int main()
{
	int  n;
	cout << "enter number\n";
	cin >> n;
	cout << isPrime(n);

}



