#include <iostream>
#define SIZE 256
//#include <math.h>

using namespace std;

int main()
{
	int   n, m, k = 0;
	cout << "input natural number n: ";
	cin >> n ;
	int arr[SIZE]{};

	
	for (int m = 1; m < n/2; m++)
	{
		if((n % int(pow(m,2)) == 0) && (n % int(pow(m, 3)) != 0))
		{
			arr[k] = m;
			k++;
		}
	}

	for (int i = 0; i < k; i++)
		cout << arr[i] << endl;

	system("pause");
}