#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <cstdlib>

struct Node
{
    int value;
    Node *next;
};

struct List
{
    Node *head;
    int size;

    List();
    void insert(int value);
    void remove(int value);
    void print();
    void clearList();
    int removeFirst();
    int indexOf(int value);
};

#endif