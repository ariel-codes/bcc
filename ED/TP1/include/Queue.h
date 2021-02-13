//
// Created by Ariel Santos on 08/02/21.
//

#ifndef TP1_SRC_QUEUE_h_
#define TP1_SRC_QUEUE_h_

#include <memory>

template<typename datatype>
class Queue {
 public:
  class Item {
   public:
    datatype data;
    std::shared_ptr<Item> next;

    explicit Item(datatype data, std::shared_ptr<Item> next = std::shared_ptr<Item>()) : data(data), next(next) {};
  };

  std::shared_ptr<Item> enqueue(datatype data) {
    std::shared_ptr<Item> it(new Item(data));
    if (!back && !front) {
      front = it;
      back = it;
    } else {
      back->next = it;
      back = it;
    }
    return it;
  }

  std::shared_ptr<Item> unshift(datatype data) {
    std::shared_ptr<Item> it(new Item(data, front));
    if (!back && !front) {
      front = it;
      back = it;
    } else {
      front = it;
    }
    return it;
  }

  void dequeue() {
    front = front->next;
  }

  std::shared_ptr<Item> get_front() { return front; }

 private:
  std::shared_ptr<Item> front, back = front;
};

#endif //TP1_SRC_QUEUE_h_
