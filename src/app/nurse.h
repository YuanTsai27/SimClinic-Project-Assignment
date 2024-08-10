#ifndef NURSE_H
#define NURSE_H

#include <string>

#include "LinkedList.h"
#include "staff.h"

using namespace std;

class Nurse : public Staff {
 private:
  int nurse_id_;
  static int next_nurse_id_;

 public:
  Nurse();
  int GetId() const override;
  void FastForwardOneTick() override;
  virtual ~Nurse();
};

#endif  // NURSE_H
