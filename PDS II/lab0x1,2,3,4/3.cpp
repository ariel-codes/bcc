#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char const *argv[])
{
    string name;
    ifstream file;
    int num;

    cin >> name;
    file.open(name);
    while (file >> num)
        if (num % 2 == 0)
            cout << num << ' ';
    cout << endl;
    file.close();
    file.open(name);
    while (file >> num)
        if (num % 2 != 0)
            cout << num << ' ';
    cout << endl;
    file.close();
    return 0;
}
