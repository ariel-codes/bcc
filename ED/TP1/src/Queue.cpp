//
// Created by Ariel Santos on 08/02/21.
//

#include "Queue.hpp"

template<typename ItemData>
Queue<ItemData>::Item::Item(ItemData data, ItemData *next) : data(data), next(next) {};

template<typename ItemData>
Queue<ItemData>::~Queue() {
  for (Item *i = head; i != nullptr;) {
    Item next = i->next;
    delete i;
    i = next;
  }
}

template<typename ItemData>
typename Queue<ItemData>::Item *Queue<ItemData>::enqueue(ItemData data) {
  auto item = new Item(data);
  tail->next = item;
  tail = item;
  return item;
}

template<typename ItemData>
typename Queue<ItemData>::Item *Queue<ItemData>::dequeue() {
  auto item = head;
  head = item->next;
  return item;
}
