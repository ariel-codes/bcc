//
// Created by Ariel Santos on 27/03/21.
//

#ifndef TP3_SRC_STACK_HH_
#define TP3_SRC_STACK_HH_

#include <ostream>
class Queue {
 private:
  class LList {
	friend class Queue;

	explicit LList(char v);

	friend std::ostream &operator<<(std::ostream &os, const Queue &queue);

	~LList();

   private:
	const char value;
	LList *next = nullptr;
  };

 public:
  Queue() = default;
  void enqueue(char value);
  char dequeue();
  bool empty();

  friend std::ostream &operator<<(std::ostream &os, const Queue &queue);

  ~Queue();

 private:
  LList *first = nullptr;
  LList *last = nullptr;
};

#endif //TP3_SRC_STACK_HH_
