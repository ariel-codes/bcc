//
// Created by Ariel Santos on 27/03/21.
//

#ifndef TP3_SRC_STACK_HH_
#define TP3_SRC_STACK_HH_

class Queue {
 private:
  class LList {
	friend class Queue;

	explicit LList(char v);
	~LList();

   private:
	const char value;
	LList *next = nullptr;
  };

 public:
  Queue() = default;
  void enqueue(char value);
  char dequeue();

  ~Queue();
  bool empty();
 private:
  LList *first = nullptr;
  LList *last = nullptr;
};

#endif //TP3_SRC_STACK_HH_
