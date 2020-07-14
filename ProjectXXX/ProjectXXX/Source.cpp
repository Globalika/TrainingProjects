#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void DoWork(int a, int b, string msg)
{
	cout << msg << endl;
	this_thread::sleep_for(chrono::milliseconds(1000));
	cout << "++++ " << " start+++" << endl;
	this_thread::sleep_for(chrono::milliseconds(2000));
	cout << "a+b = " << a + b << endl;
	this_thread::sleep_for(chrono::milliseconds(1000));
	cout << "++++ " << " end+++" << endl;
}


int main()
{
	thread th(DoWork,2,4,"our msf");//potok prinimaet ukazatel, parametru cherez zapyatuu
	//DoWork(2, 3);
	for (size_t i = 0; true; i++)
	{
		cout << "id -> " << this_thread::get_id() << " main work : " << i << endl;
		this_thread::sleep_for(chrono::milliseconds(500));
	}
	th.join();
	return 0;
}

