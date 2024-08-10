#include "app.h"

#include <iostream>
#include <string>

#include "doctor.h"
#include "message.h"
#include "nurse.h"
#include "patient.h"
#include "utils.h"

using namespace std;

App::App() {
  clock_ = 0;
  this->doctors_list_ = new LinkedList();
  this->nurses_list_ = new LinkedList();
}

App::~App() {}

void App::TickTock(const std::string &num_ticktock) {
  // check if there is already a nurse
  if (nurses_list_->LinkedList::GetSize() == 0) {
    Message::ERROR_NO_NURSES.PrintMessage();
    return;
  }

  // check if input time is valid
  for (int i = 0; i < num_ticktock.length(); i++) {
    if ((i == 0) && (num_ticktock[i] == '-')) {  // case where input is negative
      Message::SIMCLINIC_CLOCK_ERROR.PrintMessage();
      return;
    } else if (num_ticktock[i] < '0' ||
               num_ticktock[i] > '9') {  // case for other invalid characters
      Message::INVALID_COMMAND.PrintMessage();
      return;
    }
  }

  // fast forward time for all doctors 1 clock tick at a time

  Doctor *current_node = nullptr;

  for (int i = 0; i < stoi(num_ticktock); i++) {
    for (int j = 0; j < doctors_list_->LinkedList::GetSize(); j++) {
      current_node = static_cast<Doctor *>(doctors_list_->LinkedList::Get(j));
      current_node->Doctor::FastForwardOneTick();
    }
  }

  // update sim clock
  clock_ = clock_ + stoi(num_ticktock);
  Message::SIMCLINIC_CLOCK.PrintMessage({to_string(clock_)});
}

void App::AddNurse() {
  // check if there is a nurse
  if (nurses_list_->LinkedList::GetSize() > 0) {
    Message::ERROR_SECOND_NURSE.PrintMessage();
    return;
  }

  // add a new nurse
  Nurse *nurse = new Nurse();
  nurses_list_->LinkedList::AddBack(nurse);
  Message::NURSE_ADDED.PrintMessage();

  return;
}

void App::RemoveNurse() {
  // check if there is a nurse
  if (nurses_list_->LinkedList::GetSize() == 0) {
    Message::ERROR_NO_NURSES.PrintMessage();
    return;
  }

  // check if no doctors left working, if so, remove nurse
  if (doctors_list_->LinkedList::GetSize() == 0) {
    Message::NURSE_REMOVED.PrintMessage();
    nurses_list_->LinkedList::RemoveWithPosition(0);
    return;
  }

  // last case, there are still doctors remaining
  Message::ERROR_DOCTORS.PrintMessage();
}

void App::AddDoctor(const std::string &doc_type) {
  // check if there is a nurse
  if (nurses_list_->LinkedList::GetSize() == 0) {
    Message::ERROR_NO_NURSES.PrintMessage();
    return;
  }

  // check if there are too many doctors
  if (doctors_list_->LinkedList::GetSize() >= 3) {
    Message::ERROR_MAX_DOCTORS.PrintMessage();
    return;
  }

  std::string type_lower_cased = Utils::GetLowercase(doc_type);
  Doctor::Type type = Doctor::Type::FIFO;

  // check if case-insensitive input is valid, if not return
  if (type_lower_cased == "sjn") {
    type = Doctor::Type::SJN;
  } else if (type_lower_cased == "fifo") {
    type = Doctor::Type::FIFO;
  } else {
    Message::ERROR_DOCTOR_TYPE.PrintMessage();
    return;
  }

  // adding new doctor to the list
  Doctor *doctor = new Doctor(type);
  doctors_list_->LinkedList::AddBack(doctor);
  Message::DOCTOR_ADDED.PrintMessage(
      {Utils::GetUppercase(doc_type), to_string(doctor->GetId())});
}

void App::RemoveDoctor(const std::string &doc_id) {
  // check if there is a nurse
  if (nurses_list_->LinkedList::GetSize() == 0) {
    Message::ERROR_NO_NURSES.PrintMessage();
    return;
  }

  // check if there are 1+ doctors
  if (doctors_list_->LinkedList::GetSize() == 0) {
    Message::ERROR_NO_DOCTORS.PrintMessage();
    return;
  }

  // check if input number is valid
  for (int i = 0; i < doc_id.length(); i++) {
    if (doc_id[i] < '0' ||
        doc_id[i] > '9') {  // case for any invalid characters including "-" for
                            // negative numbers.
      Message::INVALID_COMMAND.PrintMessage();
      return;
    }
  }

  // check if doctor free
  Doctor *current_node = nullptr;

  for (int i = 0; i < doctors_list_->LinkedList::GetSize(); i++) {
    current_node = static_cast<Doctor *>(doctors_list_->LinkedList::Get(i));
    if (current_node->Doctor::GetId() == stoi(doc_id)) {
      if (current_node->Doctor::GetNumPatient() > 0) {
        // if doctor has 1+ patients in their list, they are not free
        Message::ERROR_DOCTOR_NOT_FREE.PrintMessage({doc_id});
        return;
      }

      // remove doctor from doctors list
      doctors_list_->LinkedList::RemoveWithPosition(i);
      Message::DOCTOR_REMOVED.PrintMessage({doc_id});
      return;
    }
  }

  // last case, doctor not found
  Message::ERROR_NO_DOCTOR.PrintMessage({doc_id});

  return;
}

void App::AddPatient(const std::string &consult_time) {
  // check if there is a nurse
  if (nurses_list_->LinkedList::GetSize() == 0) {
    Message::ERROR_NO_NURSES.PrintMessage();
    return;
  }

  // check if there are 1+ doctors
  if (doctors_list_->LinkedList::GetSize() == 0) {
    Message::ERROR_NO_DOCTORS.PrintMessage();
    return;
  }

  // check if input time is purely numbers
  for (int i = 0; i < consult_time.length(); i++) {
    if (consult_time[i] < '0' ||
        consult_time[i] > '9') {  // case for any invalid characters
      Message::INVALID_COMMAND.PrintMessage();
      return;
    }
  }

  // check if time => 1
  if (stoi(consult_time) < 1) {
    Message::PATIENT_ADDED_ERROR.PrintMessage();
    return;
  }

  Patient *patient = new Patient(stoi(consult_time), clock_);

  // finding the position in the doctors list of the doctor with the least
  // amount of patients
  Doctor *current_node = nullptr;
  int min_num_patients = 0;
  int min_num_patients_position = 0;

  // illiterate through doctors list, updating min_num_patients when a new min
  // is found
  for (int i = 0; i < doctors_list_->LinkedList::GetSize(); i++) {
    current_node = static_cast<Doctor *>(doctors_list_->LinkedList::Get(i));
    if (i == 0 || (current_node->Doctor::GetNumPatient() < min_num_patients)) {
      min_num_patients = current_node->Doctor::GetNumPatient();
      min_num_patients_position = i;
    }
  }

  // adding patient to the doctor's list
  Doctor *doctor_to_add_patient = static_cast<Doctor *>(
      doctors_list_->LinkedList::Get(min_num_patients_position));

  doctor_to_add_patient->Doctor::AddPatient(patient);

  Message::PATIENT_ADDED.PrintMessage(
      {to_string(patient->Patient::GetId()), consult_time});
  return;
}

void App::RemovePatient(const std::string &patient_id) {
  // check if there is a nurse
  if (nurses_list_->LinkedList::GetSize() == 0) {
    Message::ERROR_NO_NURSES.PrintMessage();
    return;
  }

  // check if there are 1+ doctors
  if (doctors_list_->LinkedList::GetSize() == 0) {
    Message::ERROR_NO_DOCTORS.PrintMessage();
    return;
  }

  // check if input number is valid
  for (int i = 0; i < patient_id.length(); i++) {
    if (patient_id[i] < '0' ||
        patient_id[i] > '9') {  // case for any invalid characters
      Message::INVALID_COMMAND.PrintMessage();
      return;
    }
  }

  // find patient across all of the doctors' patient lists
  Doctor *current_doctor = nullptr;
  Patient *current_patient = nullptr;

  for (int i = 0; i < doctors_list_->LinkedList::GetSize(); i++) {
    current_doctor = static_cast<Doctor *>(doctors_list_->LinkedList::Get(i));
    for (int j = 0; j < current_doctor->Doctor::GetNumPatient(); j++) {
      current_patient = static_cast<Patient *>(
          current_doctor->Doctor::GetPatientsList()->LinkedList::Get(j));
      if (current_patient->Patient::GetId() == stoi(patient_id)) {
        // check if patient is being seen by doctor
        if (current_patient->Patient::IsInConsultation()) {
          Message::PATIENT_NOT_REMOVED.PrintMessage({patient_id});
          return;
        }

        // otherwise, patient is free to remove
        Message::PATIENT_REMOVED.PrintMessage(
            {patient_id, "was not",
             to_string(current_patient->Patient::GetTimeWaited())});

        current_doctor->Doctor::GetPatientsList()
            ->LinkedList::RemoveWithPosition(j);

        return;
      }
    }
  }

  Message::ERROR_NO_PATIENT.PrintMessage({patient_id});
}

void App::ShowDoctor(const std::string &doctor_id) const {
  // check if there is a nurse
  if (nurses_list_->LinkedList::GetSize() == 0) {
    Message::ERROR_NO_NURSES.PrintMessage();
    return;
  }

  // check if there are 1+ doctors
  if (doctors_list_->LinkedList::GetSize() == 0) {
    Message::ERROR_NO_DOCTORS.PrintMessage();
    return;
  }

  // check if input number is valid
  for (int i = 0; i < doctor_id.length(); i++) {
    if (doctor_id[i] < '0' ||
        doctor_id[i] > '9') {  // case for any invalid characters
      Message::INVALID_COMMAND.PrintMessage();
      return;
    }
  }

  // find doctor in doctors list
  Doctor *current_node = nullptr;

  for (int i = 0; i < doctors_list_->LinkedList::GetSize(); i++) {
    current_node = static_cast<Doctor *>(doctors_list_->LinkedList::Get(i));
    if (current_node->Doctor::GetId() == stoi(doctor_id)) {
      Message::SHOW_DOCTOR.PrintMessage(
          {to_string(current_node->Doctor::GetId()),
           to_string(current_node->Doctor::GetNumPatient()),
           to_string(current_node->Doctor::GetNumPatientsConsulted())});
      return;
    }
  }

  Message::ERROR_NO_DOCTORS.PrintMessage({doctor_id});
}

void App::ShowPatient(const std::string &patient_id) const {
  // check if there is a nurse
  if (nurses_list_->LinkedList::GetSize() == 0) {
    Message::ERROR_NO_NURSES.PrintMessage();
    return;
  }

  // check if there are 1+ doctors
  if (doctors_list_->LinkedList::GetSize() == 0) {
    Message::ERROR_NO_DOCTORS.PrintMessage();
    return;
  }

  // check if input number is valid
  for (int i = 0; i < patient_id.length(); i++) {
    if (patient_id[i] < '0' ||
        patient_id[i] > '9') {  // case for any invalid characters
      Message::INVALID_COMMAND.PrintMessage();
      return;
    }
  }

  // find patient across all of the doctors' patient lists
  Doctor *current_node = nullptr;
  Patient *current_patient = nullptr;

  for (int i = 0; i < doctors_list_->LinkedList::GetSize(); i++) {
    current_node = static_cast<Doctor *>(doctors_list_->LinkedList::Get(i));
    for (int j = 0; j < current_node->Doctor::GetNumPatient(); j++) {
      current_patient = static_cast<Patient *>(
          current_node->Doctor::GetPatientsList()->LinkedList::Get(j));
      if (current_patient->Patient::GetId() == stoi(patient_id)) {
        Message::SHOW_PATIENT.PrintMessage(
            {to_string(current_patient->Patient::GetId()),
             to_string(current_patient->Patient::GetTimeOfArrival()),
             to_string(current_patient->Patient::GetConsultationTime()),
             to_string(current_patient->Patient::GetConsultationTimeLeft())});
        return;
      }
    }
  }

  Message::ERROR_NO_PATIENT.PrintMessage({patient_id});
}
