
#include "command.h"

#include <iostream>

#include "message.h"
#include "utils.h"
using namespace std;

const Command Command::TICKTOCK(
    "TICKTOCK", 1, "Increment the SimClinic clock by <NUMBER_TICKTOCK>.");
const Command Command::ADD_NURSE("ADD_NURSE", 0,
                                 "Add a new nurse to SimClinic.");
const Command Command::REMOVE_NURSE("REMOVE_NURSE", 0,
                                    "Remove nurse from SimClinic.");
const Command Command::ADD_DOCTOR(
    "ADD_DOCTOR", 1, "Added a new doctor type <DOCTYPE> to SimClinic.");
const Command Command::ADD_PATIENT(
    "ADD_PATIENT", 1,
    "Added a new patient to SimClinic. Consultation time is <CONSULT_TIME>.");
const Command Command::SHOW_PATIENT(
    "SHOW_PATIENT", 1,
    "Show info about SimClinic patient with ID <PATIENT_ID>.");
const Command Command::SHOW_DOCTOR(
    "SHOW_DOCTOR", 1, "Show info about SimClinic doctor with ID <DOCTOR_ID>.");
const Command Command::REMOVE_PATIENT(
    "REMOVE_PATIENT", 1, "Remove patient <PATIENT_ID> from SimClinic.");
const Command Command::REMOVE_DOCTOR(
    "REMOVE_DOCTOR", 1, "Remove doctor <DOCTOR_ID> from SimClinic.");
const Command Command::HELP("HELP", 0, "Print usage");
const Command Command::EXIT("EXIT", 0, "Exit the application");
const Command Command::INVALID("_____INVALID____", 0,
                               "Placeholder for INVALID Command value");

std::initializer_list<Command> Command::commands = {
    Command::TICKTOCK,       Command::ADD_NURSE,     Command::REMOVE_NURSE,
    Command::ADD_DOCTOR,     Command::REMOVE_DOCTOR, Command::ADD_PATIENT,
    Command::REMOVE_PATIENT, Command::SHOW_PATIENT,  Command::SHOW_DOCTOR,
    Command::HELP,           Command::EXIT};

Command::Command(const std::string &name, int num_args,
                 const std::string &message) {
  this->name_ = name;
  this->num_args_ = num_args;
  this->message_ = message;
}

Command::Command(const std::string &name, int num_args,
                 const std::string &message,
                 const std::vector<std::string> &option_prompts) {
  this->name_ = name;
  this->num_args_ = num_args;
  this->message_ = message;
  this->option_prompts_ = option_prompts;
}

std::string Command::GetName() const { return name_; }

bool Command::HasArguments() const { return num_args_ > 0; }

int Command::GetNumArgs() const { return num_args_; }

bool Command::HasOptions() const { return option_prompts_.size() > 0; }

int Command::GetNumOptions() const { return option_prompts_.size(); }

std::string Command::GetMessage() const { return message_; }

std::string Command::GetOptionPrompt(int index) const {
  return option_prompts_[index];
}

bool Command::operator==(const Command &other) const {
  return name_ == other.name_;
}

bool Command::operator!=(const Command &other) const {
  return !(*this == other);
}

std::string Command::GetHelp() {
  std::string help;
  for (const Command &command : commands) {
    int num_args = command.GetNumArgs();
    help += command.GetName() + "\t";
    help += "[" + (num_args == 0 ? "no" : to_string(command.GetNumArgs())) +
            " argument" + (num_args == 1 ? "" : "s") + "]";
    help += "\t";
    help += command.GetMessage() + "\n";
  }
  return help;
}

bool Command::IsValidCommand(const std::string &cmd_input) {
  return Find(cmd_input) != Command::INVALID;
}

const Command &Command::Find(const std::string &cmd_input) {
  string cmd = Utils::GetFirstWord(cmd_input);
  cmd = Utils::GetUppercaseUnderscore(cmd);

  for (const Command &command : commands) {
    if (command.GetName() == cmd) {
      return command;
    }
  }

  return Command::INVALID;
}
