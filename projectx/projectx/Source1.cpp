#include <iostream>
#include <vector>
#include <map>
using namespace std;
int findOdd(const std::vector<int>& numbers)
{
	multimap <int, int> myMap;
    for (auto i : numbers)
    {
        myMap.insert(pair<int, int>(i, 1));
    }
    for (auto it = myMap.begin(); it != myMap.end(); ++it)
    {
        cout << it->first << " : " << it->second << endl;
    }
    return 0;
}
int main()
{
    findOdd({ 20,1,-1,2,-2,3,3,5,5,1,2,4,20,4,-1,-2,5 });
    return 0;
}