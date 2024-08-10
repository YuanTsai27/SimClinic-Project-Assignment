#include "patient.h"

#include <iostream>

#include "message.h"
#include "utils.h"

using namespace std;

int Patient::next_id_ = 0;

Patient::Patient(const int consultation_time, const int time_of_arrival) {
  this->id_ = Patient::next_id_;
  Patient::next_id_++;
  this->consultation_time_left_ = this->consultation_time_ = consultation_time;
  this->time_waited_ = 0;
  this->in_consultation_ = false;
  this->time_of_arrival_ = time_of_arrival;
}

int Patient::GetId() const { return this->id_; }

int Patient::GetConsultationTimeLeft() const {
  return this->consultation_time_left_;
}

int Patient::GetConsultationTime() const { return this->consultation_time_; }

int Patient::GetTimeOfArrival() const { return this->time_of_arrival_; }

int Patient::GetTimeWaited() const { return this->time_waited_; }

bool Patient::IsInConsultation() const { return this->in_consultation_; }

void Patient::SetInConsultation(const bool in_consultation) {
  this->in_consultation_ = in_consultation;
}

void Patient::FastForwardTime(const int time) {
  if (in_consultation_) {
    this->consultation_time_left_ -= time;

    if (consultation_time_left_ < 0) {
      consultation_time_left_ = 0;
    }

  } else {
    this->time_waited_ += time;
  }
}

Patient::~Patient() {}
