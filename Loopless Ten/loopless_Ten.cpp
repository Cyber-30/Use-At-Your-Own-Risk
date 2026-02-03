#include <iostream>
using namespace std;

// Counting 1 to 10 without using a loop
int main()
{
    int x = 0;

s:
    cout << ++x << "  ";
    if (x >= 10)    // Change '10' to any other number to count up to that number
        return 0;   
    else
        goto s;     // continue the loop
}
