#ifndef APP_H
#define APP_H

#include <string>

#include "LinkedList.h"

class App {
 private:
  int clock_;

  LinkedList *doctors_list_;
  LinkedList *nurses_list_;

 public:
  App(void);
  ~App(void);
  void AddNurse(void);
  void TickTock(const std::string &num_ticktock);
  void RemoveNurse(void);
  void AddDoctor(const std::string &doc_type);
  void AddPatient(const std::string &consult_time);
  void RemovePatient(const std::string &patient_id);
  void RemoveDoctor(const std::string &doc_id);
  void ShowPatient(const std::string &patient_id) const;
  void ShowDoctor(const std::string &doctor_id) const;
};

#endif  // APP_H
