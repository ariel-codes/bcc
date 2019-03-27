#include "List.hpp"

List::List()
{
    this->size = 0;
    this->head = NULL;
}

void List::insert(int value)
{
    Node *node = new Node();
    node->value = value;
    node->next = this->head;
    this->head = node;
    size++;
}

void List::clearList()
{
    while (head != NULL)
    {
        Node *gone = head;
        head = head->next;
        delete gone;
    }
}

void List::print()
{
    Node *head = this->head;
    if (this->size > 0)
    {
        while (head)
        {
            std::cout << head->value << " ";
            head = head->next;
        }
        std::cout << std::endl;
    }
    else
    {
        std::cout << "-" << std::endl;
        return;
    }
}

int List::removeFirst()
{
    Node *current = head;
    if (this->size > 0)
    {
        this->head = this->head->next;
        const int val = current->value;
        delete current;
        size--;
        return val;
    }
    else
    {
        return -1;
    }
}

int List::indexOf(int value)
{
    if (this->size > 0)
    {
        Node *head = this->head;
        int index = 0;
        while (head && head->value != value)
        {
            index++;
            head = head->next;
        }
        if (head->value == value)
            return index;
        return -1;
    }
    else
    {
        return -1;
    }
}

void List::remove(int value)
{
    if (head != NULL && head->value == value)
    {
        const Node *found = head;
        head = found->next;
        delete found;
        size--;
    }
    else
    {
        Node *previous = head;
        Node *current = head->next;
        while (current != NULL)
        {
            if (current->value == value)
            {
                previous->next = current->next;
                delete current;
                size--;
                current = NULL;
            }
            else
            {
                previous = current;
                current = current->next;
            }
        }
    }
}