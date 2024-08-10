#include "LinkedList.h"

#include <iostream>

using namespace std;

LinkedList::LinkedList() { this->head_ = nullptr; }

Node* LinkedList::GetLast() const {
  if (this->head_ == nullptr) {
    return nullptr;
  }

  Node* current_node = this->head_;
  while (current_node->GetNext() != nullptr) {
    current_node = current_node->GetNext();
  }

  return current_node;
}

void LinkedList::RemoveWithPosition(int position) {
  if (this->head_ == nullptr) {
    return;
  }

  if (position == 0) {
    Node* new_head = this->head_->GetNext();
    delete this->head_;
    this->head_ = new_head;
    return;
  }

  Node* current_node = this->head_;
  Node* previous_node = nullptr;
  int current_position = 0;

  while (current_node != nullptr) {
    if (current_position == position) {
      previous_node->SetNext(current_node->GetNext());
      delete current_node;
      return;
    }

    previous_node = current_node;
    current_node = current_node->GetNext();
    current_position++;
  }

  return;
}

int LinkedList::GetPosition(void* n) const {
  Node* current_node = this->head_;
  int current_position = 0;

  while (current_node != nullptr) {
    if (current_node->GetAddress() == n) {
      return current_position;
    }

    current_node = current_node->GetNext();
    current_position++;
  }

  return -1;
}

int LinkedList::GetSize() const {
  int size = 0;
  Node* current_node = this->head_;
  while (current_node != nullptr) {
    size++;
    current_node = current_node->GetNext();
  }

  return size;
}

void LinkedList::AddBack(void* n) {
  Node* new_node = new Node(n);

  if (this->head_ == nullptr) {
    this->head_ = new_node;
    return;
  }

  Node* last = this->GetLast();
  last->SetNext(new_node);
}

void LinkedList::AddWithPosition(void* n, int position) {
  Node* new_node = new Node(n);
  Node* current_node = this->head_;
  Node* previous_node = nullptr;
  int current_position = 0;

  if (position == 0) {
    new_node->SetNext(this->head_);
    this->head_ = new_node;
    return;
  }

  while (current_node != nullptr) {
    if (current_position == position) {
      previous_node->SetNext(new_node);
      new_node->SetNext(current_node);
      return;
    }

    previous_node = current_node;
    current_node = current_node->GetNext();
    current_position++;
  }

  if (current_position == position) {
    previous_node->SetNext(new_node);
    new_node->SetNext(current_node);
  }

  return;
}

void* LinkedList::Get(int position) const {
  Node* current_node = this->head_;
  int current_position = 0;

  while (current_node != nullptr) {
    if (current_position == position) {
      return current_node->GetAddress();
    }

    current_node = current_node->GetNext();
    current_position++;
  }

  return nullptr;
}

LinkedList::~LinkedList() {}
