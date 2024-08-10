#include "doctor.h"

#include <iostream>

#include "message.h"
#include "utils.h"

using namespace std;

int Doctor::next_doc_id_ = 0;

Doctor::Doctor(Type type) : Staff() {
  this->doc_id_ = Doctor::next_doc_id_;
  Doctor::next_doc_id_++;
  this->patients_consulted_ = 0;
  this->patients_ = new LinkedList();
  this->type_ = type;
}

void Doctor::AddPatient(Patient* new_patient) {
  // add to the back for FIFO queue or if there are no patients in the SJN queue
  if ((this->type_ == Doctor::Type::FIFO) ||
      (this->patients_->LinkedList::GetSize() == 0)) {
    this->patients_->LinkedList::AddBack((void*)new_patient);
    return;
  }

  // add to the correct position for SJN queue

  // check if the first patient in the list is in consultation
  int current_position = 0;
  if (static_cast<Patient*>(this->patients_->LinkedList::Get(0))
          ->Patient::IsInConsultation()) {
    current_position = 1;
  }

  Patient* current_node =
      static_cast<Patient*>(patients_->LinkedList::Get(current_position));

  while (!(current_node == nullptr)) {
    if (new_patient->Patient::GetConsultationTime() <
        current_node->Patient::GetConsultationTime()) {
      break;
    }

    current_position++;
    current_node =
        static_cast<Patient*>(patients_->LinkedList::Get(current_position));
  }

  this->patients_->LinkedList::AddWithPosition(new_patient, current_position);
  return;
}

LinkedList* Doctor::GetPatientsList() const { return this->patients_; }

int Doctor::GetId() const { return this->doc_id_; }

int Doctor::GetNumPatient() const {
  int num_patients = this->patients_->LinkedList::GetSize();

  return num_patients;
}

int Doctor::GetNumPatientsConsulted() const {
  return this->patients_consulted_;
}

void Doctor::FastForwardOneTick() {
  if (this->patients_->LinkedList::GetSize() == 0) {
    return;
  }

  Patient* patient_in_consultation =
      static_cast<Patient*>(this->patients_->LinkedList::Get(0));
  Patient* current_patient = patient_in_consultation;
  patient_in_consultation->Patient::SetInConsultation(true);

  for (int i = 0; i < patients_->LinkedList::GetSize(); i++) {
    current_patient =
        static_cast<Patient*>(this->patients_->LinkedList::Get(i));
    current_patient->Patient::FastForwardTime(1);
  }

  if (patient_in_consultation->Patient::GetConsultationTimeLeft() > 0) {
    return;
  }

  this->patients_consulted_++;
  Message::PATIENT_REMOVED.PrintMessage(
      {to_string(patient_in_consultation->Patient::GetId()), "was",
       to_string(patient_in_consultation->Patient::GetTimeWaited())});
  this->patients_->LinkedList::RemoveWithPosition(0);
}

Doctor::~Doctor() {}
