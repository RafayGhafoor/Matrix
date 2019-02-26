#include <iostream>

using namespace std;

int main()
{
    int *ptr = new int[20];
    int i = 0, j = 0;

    for (; i < 10; i++)
        ptr[i] = i;

    while (j++ < i)
        cout << ptr[j] << endl;

    delete[] ptr;
}