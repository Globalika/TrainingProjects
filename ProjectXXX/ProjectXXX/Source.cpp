#include <iostream>
#include <mutex>
#include <thread>
#include "SimpleTimer.h"
using namespace std;
//uniquw_lock
mutex mtx;
void Print(char ch)
{
	unique_lock<mutex> ul(mtx,std::defer_lock);//eshe ne vuzvali i mohem sami
	
	this_thread::sleep_for(chrono::milliseconds(10));
	ul.lock();// naprimer zdes
	//lock_guard<mutex> lg(mtx);
	//unique_lock<mutex> ul(mtx);//mohet vazvat lock a mohet i ne//sami vasuvaem gde nado
	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			cout << ch;
			this_thread::sleep_for(chrono::milliseconds(10));
		}
		cout << endl;
	}
	cout << endl;
	ul.unlock();//esli sami ne vuzovem
	//mtx.unlock();
	this_thread::sleep_for(chrono::milliseconds(10));
}//to vuzovet zdes!!

int main()
{
	SimpleTimer timer;

	thread t1(Print, '&');
	thread t2(Print, '%');

	t1.join();
	t2.join();
	return 0;
}