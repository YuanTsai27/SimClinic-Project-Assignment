#ifndef NODE_H
#define NODE_H

class Node {
 private:
  void* address_;
  Node* next_;

 public:
  Node(void* v);
  void SetNext(Node* n);
  Node* GetNext() const;
  void* GetAddress() const;

  ~Node();
};

#endif /* NODE_H */
