#ifndef DOCTOR_H
#define DOCTOR_H

#include <string>

#include "LinkedList.h"
#include "patient.h"
#include "staff.h"

using namespace std;

class Doctor : public Staff {
 public:
  enum Type { FIFO, SJN };

 private:
  LinkedList* patients_;
  int patients_consulted_;
  int doc_id_;
  static int next_doc_id_;
  Type type_;

 public:
  Doctor(Type type);
  void AddPatient(Patient* new_patient);
  LinkedList* GetPatientsList() const;
  int GetNumPatient() const;
  int GetId() const override;
  void FastForwardOneTick() override;
  int GetNumPatientsConsulted() const;

  virtual ~Doctor();
};

#endif  // DOCTOR_H
