#ifndef MESSAGE_H
#define MESSAGE_H

#include <initializer_list>
#include <string>

class Message {
 private:
  std::string msg_;

 public:
  static const Message ERROR_SECOND_NURSE;
  static const Message ERROR_NO_NURSES;
  static const Message ERROR_NO_DOCTORS;
  static const Message ERROR_DOCTORS;
  static const Message ERROR_NO_DOCTOR;
  static const Message ERROR_NO_PATIENT;
  static const Message ERROR_DOCTOR_NOT_FREE;
  static const Message SHOW_PATIENT;
  static const Message SHOW_DOCTOR;
  static const Message NURSE_ADDED;
  static const Message NURSE_REMOVED;
  static const Message ERROR_MAX_DOCTORS;
  static const Message ERROR_DOCTOR_TYPE;
  static const Message DOCTOR_ADDED;
  static const Message DOCTOR_REMOVED;
  static const Message PATIENT_ADDED;
  static const Message PATIENT_ADDED_ERROR;
  static const Message PATIENT_REMOVED;
  static const Message PATIENT_NOT_REMOVED;
  static const Message SIMCLINIC_CLOCK;
  static const Message SIMCLINIC_CLOCK_ERROR;
  static const Message INVALID_COMMAND;
  static const Message COMMAND_NOT_FOUND;
  static const Message WRONG_ARGUMENT_COUNT;
  static const Message END;

  Message(const std::string &msg);
  std::string GetMessage() const;
  std::string GetMessage(std::initializer_list<std::string> args) const;
  void PrintMessage() const;
  void PrintMessage(std::initializer_list<std::string> args) const;
};

#endif  // MESSAGE_H
