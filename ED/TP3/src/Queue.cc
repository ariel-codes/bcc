//
// Created by Ariel Santos on 27/03/21.
//

#include "Queue.hh"

Queue::LList::LList(char v) : value(v) {}

Queue::LList::~LList() {
  delete next;
}

void Queue::enqueue(char value) {
  auto new_item = new LList(value);
  if (first == nullptr) {
	first = new_item;
  } else {
	last->next = new_item;
  }
  last = new_item;
}

char Queue::dequeue() {
  char val = first->value;

  auto rm = first;
  first = first->next;
  rm->next = nullptr;
  delete rm;

  return val;
}

bool Queue::empty() {
  return first == nullptr;
}

Queue::~Queue() {
  delete first;
}
