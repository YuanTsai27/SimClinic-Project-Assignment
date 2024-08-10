#include "node.h"

#include <iostream>

using namespace std;

void* Node::GetAddress() const { return this->address_; }

void Node::SetNext(Node* n) { this->next_ = n; }

Node* Node::GetNext() const { return this->next_; }

Node::Node(void* v) {
  this->address_ = v;
  this->next_ = nullptr;
}

Node::~Node() {}
