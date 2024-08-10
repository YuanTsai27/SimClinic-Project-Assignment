#ifndef STAFF_H
#define STAFF_H

#include <string>

using namespace std;

class Staff {
 public:
  Staff();
  virtual int GetId() const = 0;
  virtual void FastForwardOneTick() = 0;
  virtual ~Staff();
};

#endif  // STAFF_H
