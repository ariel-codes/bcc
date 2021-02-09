//
// Created by Ariel Santos on 08/02/21.
//

#ifndef TP1_SRC_QUEUE_HPP_
#define TP1_SRC_QUEUE_HPP_

template<typename ItemData>
class Queue {
 public:
  class Item {
   public:
    ItemData data;
    Item *next;

    explicit Item(ItemData data, ItemData *next = nullptr);
  };

  Queue() = default;
  ~Queue();

  Item *enqueue(ItemData data);

  Item *dequeue();

 private:
  Item *head, *tail;
};

#endif //TP1_SRC_QUEUE_HPP_
