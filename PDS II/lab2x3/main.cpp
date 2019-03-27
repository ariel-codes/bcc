#include <iostream>
#include "List.hpp"

using namespace std;

int main()
{
    List *L = new List();
    long n, k;
    cin >> n >> k;
    for (size_t i = 0; i <= n; i++)
    {
        L->insert(i);
    }
    L->print();
    cout << L->size << endl;
    for (size_t i = 0; i < k; i++)
    {
        L->removeFirst();
    }
    L->print();
    cout << L->size << endl;
    for (size_t i = 0; i <= n; i += 2)
    {
        L->remove(i);
    }
    L->print();
    cout << L->size << endl;

    L->clearList();
    delete L;
    return 0;
}