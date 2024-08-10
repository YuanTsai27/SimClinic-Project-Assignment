
#include "launcher.h"

#include <iostream>
#include <vector>

#include "message.h"
#include "utils.h"

using namespace std;

string Launcher::COMMAND_PREFIX = "simclinic> ";

Launcher::Launcher() {}

bool Launcher::ProcessCommand(const std::string &cmd_input) {
  // Check it is a valid command name
  string cmd_input_name = Utils::GetFirstWord(cmd_input);
  Command command = Command::Find(cmd_input_name);
  if (command == Command::INVALID) {
    Message::COMMAND_NOT_FOUND.PrintMessage({cmd_input_name});
    return true;
  }

  // Check the number of arguments provided match as the command expects
  vector<string> args = Utils::SplitString(cmd_input);
  int num_args_provided = args.size() - 1;
  int num_args_expected = command.GetNumArgs();
  if (num_args_provided != num_args_expected) {
    string provided = to_string(num_args_provided) + " argument" +
                      (num_args_provided == 1 ? "" : "s");
    string expected = to_string(num_args_expected) + " argument" +
                      (num_args_expected == 1 ? "" : "s");
    cout << Message::WRONG_ARGUMENT_COUNT.GetMessage({command.GetName()}) +
                " Expected " + expected + ", but " + provided + " provided."
         << endl;
    return true;
  }

  if (command == Command::TICKTOCK) {
    app_.TickTock(args[1]);
  } else if (command == Command::ADD_NURSE) {
    app_.AddNurse();
  } else if (command == Command::REMOVE_NURSE) {
    app_.RemoveNurse();
  } else if (command == Command::ADD_DOCTOR) {
    app_.AddDoctor(args[1]);
  } else if (command == Command::REMOVE_DOCTOR) {
    app_.RemoveDoctor(args[1]);
  } else if (command == Command::ADD_PATIENT) {
    app_.AddPatient(args[1]);
  } else if (command == Command::SHOW_PATIENT) {
    app_.ShowPatient(args[1]);
  } else if (command == Command::SHOW_DOCTOR) {
    app_.ShowDoctor(args[1]);
  } else if (command == Command::REMOVE_PATIENT) {
    app_.RemovePatient(args[1]);
  } else if (command == Command::HELP) {
    cout << Command::GetHelp() << endl;
  } else if (command == Command::EXIT) {
    Message::END.PrintMessage();
    return false;
  } else {
    Message::COMMAND_NOT_FOUND.PrintMessage({cmd_input});
  }
  return true;
}

void Launcher::Start() {
  PrintBanner();
  cout << Command::GetHelp() << endl;

  // Keep reading commands until the user exits
  string cmd_input;
  do {
    cout << COMMAND_PREFIX;
    std::getline(std::cin, cmd_input);
    cmd_input = Utils::TrimString(cmd_input);
  } while (ProcessCommand(cmd_input));
}

void Launcher::PrintBanner() const {
  // https://emojicombos.com/dot-art-generator
  // https://www.freeformatter.com/java-dotnet-escape.html#before-output

  std::string banner =
      "\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u005F\u005F\u005F\u005F"
      "\u005F\u0020\u005F\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020"
      "\u0020\u0020\u000A\u0020\u0020\u0020\u0020\u005F\u0020\u0020\u002F\u0020"
      "\u005F\u005F\u005F\u005F\u0028\u005F\u0029\u0020\u0020\u0020\u0020\u0020"
      "\u0020\u0020\u0020\u0020\u0020\u000A\u0020\u0020\u005F\u007C\u0020\u007C"
      "\u007C\u0020\u0028\u005F\u005F\u005F\u0020\u0020\u005F\u0020\u005F\u0020"
      "\u005F\u005F\u0020\u005F\u005F\u005F\u0020\u0020\u000A\u0020\u007C\u005F"
      "\u0020\u0020\u0020\u005F\u005C\u005F\u005F\u005F\u0020\u005C\u007C\u0020"
      "\u007C\u0020\u0027\u005F\u0020\u0060\u0020\u005F\u0020\u005C\u0020\u000A"
      "\u0020\u0020\u0020\u007C\u005F\u007C\u0020\u005F\u005F\u005F\u005F\u0029"
      "\u0020\u007C\u0020\u007C\u0020\u007C\u0020\u007C\u0020\u007C\u0020\u007C"
      "\u0020\u007C\u000A\u0020\u0020\u0020\u005F\u005F\u005F\u007C\u005F\u005F"
      "\u005F\u005F\u005F\u002F\u007C\u005F\u007C\u005F\u007C\u0020\u007C\u005F"
      "\u007C\u0020\u007C\u005F\u007C\u000A\u0020\u0020\u002F\u0020\u005F\u005F"
      "\u005F\u005F\u007C\u0020\u0028\u005F\u0029\u0020\u0020\u0020\u0020\u0020"
      "\u0028\u005F\u0029\u0020\u0020\u0020\u0020\u0020\u000A\u0020\u007C\u0020"
      "\u007C\u0020\u0020\u0020\u0020\u007C\u0020\u007C\u005F\u0020\u005F\u0020"
      "\u005F\u005F\u0020\u0020\u005F\u0020\u0020\u005F\u005F\u005F\u0020\u000A"
      "\u0020\u007C\u0020\u007C\u0020\u0020\u0020\u0020\u007C\u0020\u007C\u0020"
      "\u007C\u0020\u0027\u005F\u0020\u005C\u007C\u0020\u007C\u002F\u0020\u005F"
      "\u005F\u007C\u000A\u0020\u007C\u0020\u007C\u005F\u005F\u005F\u005F\u007C"
      "\u0020\u007C\u0020\u007C\u0020\u007C\u0020\u007C\u0020\u007C\u0020\u007C"
      "\u0020\u0028\u005F\u005F\u0020\u000A\u0020\u0020\u005C\u005F\u005F\u005F"
      "\u005F\u005F\u007C\u005F\u007C\u005F\u007C\u005F\u007C\u0020\u007C\u005F"
      "\u007C\u005F\u007C\u005C\u005F\u005F\u005F\u007C\u000A\u0020\u0020\u0020"
      "\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020"
      "\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u000A"
      "\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020"
      "\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020"
      "\u0020\u0020\u000A\u000A";
  cout << endl << endl << banner;
}

std::string Launcher::GetCommandPrefix() const { return COMMAND_PREFIX; }
