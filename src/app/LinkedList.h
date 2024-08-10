#ifndef LinkedList_H
#define LinkedList_H

#include "node.h"

class LinkedList {
 private:
  Node* head_;
  Node* GetLast() const;

 public:
  LinkedList();
  ~LinkedList();
  void RemoveWithPosition(int position);
  int GetPosition(void* n) const;
  int GetSize() const;
  void AddBack(void* n);
  void AddWithPosition(void* n, int position);
  void* Get(int position) const;
};

#endif /* LinkedList_H */
