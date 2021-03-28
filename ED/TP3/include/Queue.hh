//
// Created by Ariel Santos on 27/03/21.
//

#ifndef TP3_SRC_STACK_HH_
#define TP3_SRC_STACK_HH_

#include <ostream>
class Queue {
 private:
  class LList {
	explicit LList(char v);

	~LList();

   private:
	const char value;
	LList *next = nullptr;

	friend class Queue;
	friend std::ostream &operator<<(std::ostream &os, const Queue &queue);
  };

 public:
  Queue() = default;

  void enqueue(char value);
  char dequeue();
  bool empty();

  ~Queue();

 private:
  LList *first = nullptr;
  LList *last = nullptr;

  friend std::ostream &operator<<(std::ostream &os, const Queue &queue);
};

#endif //TP3_SRC_STACK_HH_
