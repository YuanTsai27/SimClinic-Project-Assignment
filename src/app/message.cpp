
#include "message.h"

#include <iostream>

using namespace std;

const Message Message::ERROR_SECOND_NURSE("Cannot add another nurse.");
const Message Message::ERROR_NO_NURSES(
    "Cannot perform that operation without a nurse.");
const Message Message::ERROR_NO_DOCTORS(
    "Cannot perform that operation without a doctor.");
const Message Message::ERROR_DOCTORS(
    "Cannot perform that operation without first removing doctor(s).");
const Message Message::ERROR_NO_PATIENT("No patient with ID %s.");
const Message Message::ERROR_NO_DOCTOR("No doctor with ID %s.");
const Message Message::ERROR_DOCTOR_NOT_FREE(
    "Doctor %s is currently with a patient.");
const Message Message::SHOW_PATIENT(
    "Patient %s, time arrival %s, consultation time %s, consultation time "
    "remaining %s.");
const Message Message::SHOW_DOCTOR(
    "Doctor %s is currently assigned %s patient(s) and has finished seeing %s "
    "patient(s).");
const Message Message::NURSE_ADDED("Added nurse.");
const Message Message::NURSE_REMOVED("Removed nurse.");
const Message Message::ERROR_MAX_DOCTORS("Cannot add another doctor.");
const Message Message::ERROR_DOCTOR_TYPE("Specified doctor type is unknown.");
const Message Message::DOCTOR_ADDED("Added doctor of type '%s' with ID %s.");
const Message Message::DOCTOR_REMOVED("Removed doctor %s.");
const Message Message::PATIENT_ADDED(
    "Added patient with ID %s and consultation time of %s.");
const Message Message::PATIENT_ADDED_ERROR(
    "Patient must have have a consultation time longer then 1 minute.");
const Message Message::PATIENT_REMOVED(
    "Removed patient %s who %s seen by a doctor after waiting %s.");
const Message Message::PATIENT_NOT_REMOVED(
    "Patient %s is currently seeing the doctor.");
const Message Message::SIMCLINIC_CLOCK("SimClinic clock is now %s.");
const Message Message::SIMCLINIC_CLOCK_ERROR(
    "Cannot perform that operation, SimClinic clock cannot go back in time!");
const Message Message::INVALID_COMMAND(
    "Invalid command input. Please input the correct argument.");
const Message Message::COMMAND_NOT_FOUND(
    "Command '%s' not found. Run 'help' for the list of available commands.");
const Message Message::WRONG_ARGUMENT_COUNT(
    "Incorrect number of arguments for %s.");
const Message Message::END("Program ended.");

Message::Message(const std::string &msg) { this->msg_ = msg; }

std::string Message::GetMessage() const { return GetMessage({}); }

std::string Message::GetMessage(std::initializer_list<std::string> args) const {
  std::string result = msg_;
  for (const string &arg : args) {
    size_t pos = result.find("%s");
    if (pos != std::string::npos) {
      result.replace(pos, 2, arg);
    }
  }
  return result;
}

void Message::PrintMessage() const { PrintMessage({}); }

void Message::PrintMessage(std::initializer_list<std::string> args) const {
  cout << GetMessage(args) << endl;
}
