//
// Created by Ariel Santos on 08/02/21.
//

#ifndef TP1_SRC_QUEUE_h_
#define TP1_SRC_QUEUE_h_

#include <memory>

template<typename datatype>
class Queue {
 private:
  class Item {
    friend class Queue<datatype>;
   public:
    datatype get_data() const { return data; }
    std::shared_ptr<Item> get_next() const { return next; }

   private:
    explicit Item(datatype data, std::shared_ptr<Item> next = nullptr) : data(data), next(next) {};

    const datatype data;
    std::shared_ptr<Item> next;
  };

 public:
  std::shared_ptr<Item> enqueue(datatype data) {
    std::shared_ptr<Item> it(new Item(data));
    if (!back) {
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
    if (!front) {
      front = it;
      back = it;
    } else {
      front = it;
    }
    return it;
  }

  void dequeue() {
    if (!front->next)
      back.reset();
    front = front->next;
  }

  std::shared_ptr<Item> get_front() { return front; }

 private:
  std::shared_ptr<Item> front, back;
};

#endif //TP1_SRC_QUEUE_h_
