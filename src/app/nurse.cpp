#include "nurse.h"

#include <iostream>

#include "message.h"
#include "utils.h"

using namespace std;

int Nurse::next_nurse_id_ = 0;

Nurse::Nurse() : Staff() {
  this->nurse_id_ = Nurse::next_nurse_id_;
  Nurse::next_nurse_id_++;
}

void Nurse::FastForwardOneTick() {
  // do nothing
  return;
}

int Nurse::GetId() const { return this->nurse_id_; }

Nurse::~Nurse() {}
