#ifndef PATIENT_H
#define PATIENT_H

#include <string>

using namespace std;

class Patient {
 private:
  int id_;
  static int next_id_;

  int consultation_time_left_;
  int consultation_time_;
  int time_waited_;
  int time_of_arrival_;

  bool in_consultation_;

 public:
  Patient(const int consultation_time, const int time_of_arrival);
  int GetId() const;
  void FastForwardTime(const int time);
  bool IsInConsultation() const;
  void SetInConsultation(const bool in_consultation);
  int GetConsultationTimeLeft() const;
  int GetConsultationTime() const;
  int GetTimeOfArrival() const;
  int GetTimeWaited() const;

  virtual ~Patient();
};

#endif  // PATIENT_H
