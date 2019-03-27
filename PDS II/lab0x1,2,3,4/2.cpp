#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    int h;
    cin >> h;
    for (int i = 1; i <= h; i++)
    {
        cout << string(i, '*') << endl;
    }
    for (int i = h - 1; i > 0; i--)
    {
        cout << string(i, '*') << endl;
    }
    return 0;
}
