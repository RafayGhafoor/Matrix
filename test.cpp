#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

void readMatrix(char filename[])
{

    ifstream fin(filename);
    // int ptr[][4];
    char temp[200];
    int num;
    while (fin.getline(temp, 200))
    {
        for (int i = 0; temp[i] != 0; i++)
        {
            if (temp[i] != ' ' && temp[i] != '\n')
            {
                num = temp[i] - 48;
                cout << num << " ";
            }
        }
    }
    // int r, c;
    // fin >> r;
    // fin >> c;

    // myMatrix(r, c, 0);
}
int main()
{
    char fn[] = "test.txt";
    readMatrix(fn);
}