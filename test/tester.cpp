#include <algorithm>
#include <cctype>
#include <cstring>
#include <fstream>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "app/launcher.h"
#include "app/utils.h"

using namespace std;

/*
*****************************
  DO NOT MODIFY EXISTING METHODS
  However, you are welcome to add additional test cases.
*****************************
*/

enum TestResult { TEST_RESULT_PASS, TEST_RESULT_FAIL };

#define RUN_COMMAND(command_with_args)                         \
  cout << app.GetCommandPrefix() << command_with_args << endl; \
  app.ProcessCommand(command_with_args);

#define __FILENAME__ \
  (std::strrchr(__FILE__, '/') ? std::strrchr(__FILE__, '/') + 1 : __FILE__)

#define EXPECT_CONTAINS(expected)                                              \
  if (still_capturing_cout) {                                                  \
    still_capturing_cout = false;                                              \
    output = buffer.str();                                                     \
    std::cout.rdbuf(old);                                                      \
    std::cout << output << std::endl;                                          \
  }                                                                            \
  if (output.find(expected) == std::string::npos) {                            \
    cerr << "FAILED Test " << test_number << " in " << __FILENAME__            \
         << " on line " << __LINE__ << endl                                    \
         << "\tExpected '" << expected                                         \
         << "' in the output, but it was not found." << endl                   \
         << endl                                                               \
         << "----------------------------------------------------------------" \
            "------------"                                                     \
         << endl                                                               \
         << endl;                                                              \
    return TEST_RESULT_FAIL;                                                   \
  }

#define EXPECT_DOES_NOT_CONTAINS(expected, ignore_case)             \
  output = buffer.str();                                            \
  if (Utils::Contains(output, expected, ignore_case)) {             \
    cerr << "FAILED Test " << test_number << " in " << __FILENAME__ \
         << " on line " << __LINE__ << endl                         \
         << "\tExpected '" << expected                              \
         << "' to NOT be in the output, but it was." << endl        \
         << endl;                                                   \
    return TEST_RESULT_FAIL;                                        \
  }

int main(int argc, char *argv[]) {
  Launcher app;
  string output = "";
  bool still_capturing_cout = true;
  std::stringstream buffer;
  std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());

  // Helper Variables
  int LoopSize;
  string ShowDoctor;

  int test_number = std::stoi(argv[1]);
  switch (test_number) {
    case 1:  // Task1-T1
      RUN_COMMAND("ADD_NURSE");
      RUN_COMMAND("ADD_DOCTOR FIFO");
      RUN_COMMAND("ADD_DOCTOR SJN");
      RUN_COMMAND("ADD_DOCTOR SJN");
      RUN_COMMAND("ADD_PATIENT 5");
      RUN_COMMAND("ADD_PATIENT 5");
      RUN_COMMAND("ADD_PATIENT 2");
      RUN_COMMAND("ADD_PATIENT 2");
      RUN_COMMAND("ADD_PATIENT 1");
      RUN_COMMAND("ADD_PATIENT 1");
      RUN_COMMAND("ADD_PATIENT 3");
      RUN_COMMAND("ADD_PATIENT 3");
      RUN_COMMAND("ADD_PATIENT 1");
      RUN_COMMAND("TICKTOCK 20");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Added nurse.");
      EXPECT_CONTAINS("Added doctor of type 'FIFO' with ID 0.");
      EXPECT_CONTAINS("Added doctor of type 'SJN' with ID 1.");
      EXPECT_CONTAINS("Added doctor of type 'SJN' with ID 2.");
      EXPECT_CONTAINS("Added patient with ID 0 and consultation time of 5.");
      EXPECT_CONTAINS("Added patient with ID 1 and consultation time of 5.");
      EXPECT_CONTAINS("Added patient with ID 2 and consultation time of 2.");
      EXPECT_CONTAINS("Added patient with ID 3 and consultation time of 2.");
      EXPECT_CONTAINS("Added patient with ID 4 and consultation time of 1.");
      EXPECT_CONTAINS("Added patient with ID 5 and consultation time of 1.");
      EXPECT_CONTAINS("Added patient with ID 6 and consultation time of 3.");
      EXPECT_CONTAINS("Added patient with ID 7 and consultation time of 3.");
      EXPECT_CONTAINS("Added patient with ID 8 and consultation time of 1.");
      EXPECT_CONTAINS(
          "Removed patient 4 who was seen by a doctor after waiting 0.\n"
          "Removed patient 5 who was seen by a doctor after waiting 0.\n"
          "Removed patient 8 who was seen by a doctor after waiting 1.\n"
          "Removed patient 7 who was seen by a doctor after waiting 1.\n"
          "Removed patient 2 who was seen by a doctor after waiting 2.\n"
          "Removed patient 0 who was seen by a doctor after waiting 0.\n"
          "Removed patient 3 who was seen by a doctor after waiting 5.\n"
          "Removed patient 1 who was seen by a doctor after waiting 4.\n"
          "Removed patient 6 who was seen by a doctor after waiting 7.\n"
          "SimClinic clock is now 20.");
      break;

    case 2:  // Task1-T2
      RUN_COMMAND("ADD_NURSE");
      RUN_COMMAND("ADD_NURSE");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Added nurse.");
      EXPECT_CONTAINS("Cannot add another nurse.");
      break;

    case 3:  // Task1-T3
      RUN_COMMAND("ADD_NURSE");
      RUN_COMMAND("REMOVE_NURSE");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Added nurse.");
      EXPECT_CONTAINS("Removed nurse.");
      break;

    case 4:  // Task1-T4
      RUN_COMMAND("REMOVE_NURSE");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Cannot perform that operation without a nurse.");
      break;

    case 5:  // Task1-T5
      RUN_COMMAND("ADD_NURSE");
      RUN_COMMAND("ADD_DOCTOR FIFO");
      RUN_COMMAND("ADD_DOCTOR SJN");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Added nurse.");
      EXPECT_CONTAINS("Added doctor of type 'FIFO' with ID 0.");
      EXPECT_CONTAINS("Added doctor of type 'SJN' with ID 1.");
      break;

    case 6:  // Task1-T14
      RUN_COMMAND("ADD_NURSE");
      RUN_COMMAND("ADD_DOCTOR FIFO");
      RUN_COMMAND("ADD_DOCTOR SJN");
      RUN_COMMAND("ADD_NURSE");
      RUN_COMMAND("ADD_DOCTOR FIFO");
      RUN_COMMAND("ADD_DOCTOR SJN");
      RUN_COMMAND("REMOVE_NURSE");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Added nurse.");
      EXPECT_CONTAINS("Added doctor of type 'FIFO' with ID 0.");
      EXPECT_CONTAINS("Added doctor of type 'SJN' with ID 1.");
      EXPECT_CONTAINS("Cannot add another nurse.");
      EXPECT_CONTAINS("Added doctor of type 'FIFO' with ID 2.");
      EXPECT_CONTAINS("Cannot add another doctor.");
      EXPECT_CONTAINS(
          "Cannot perform that operation without first removing doctor(s).");

      EXPECT_DOES_NOT_CONTAINS("Added doctor of type 'SJN' with ID 3", true)
      break;

    case 7:  // Task1-T6
      RUN_COMMAND("ADD_DOCTOR FIFO");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Cannot perform that operation without a nurse.");
      break;

    case 8:  // Task1-T7
      RUN_COMMAND("ADD_NURSE");
      RUN_COMMAND("ADD_DOCTOR FIFO");
      RUN_COMMAND("REMOVE_NURSE");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Added nurse.");
      EXPECT_CONTAINS("Added doctor of type 'FIFO' with ID 0.");
      EXPECT_CONTAINS(
          "Cannot perform that operation without first removing doctor(s).");
      break;

    case 9:  // Task1-T8
      RUN_COMMAND("ADD_NURSE");
      RUN_COMMAND("ADD_DOCTOR FIFO");
      RUN_COMMAND("REMOVE_DOCTOR 0")
      RUN_COMMAND("REMOVE_NURSE");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Added nurse.");
      EXPECT_CONTAINS("Added doctor of type 'FIFO' with ID 0.");
      EXPECT_CONTAINS("Removed doctor 0.");
      EXPECT_CONTAINS("Removed nurse.");
      break;

    case 10:  // Task1-T9
      RUN_COMMAND("REMOVE_DOCTOR 0")
      RUN_COMMAND("ADD_NURSE");
      RUN_COMMAND("REMOVE_DOCTOR 2")
      RUN_COMMAND("REMOVE_NURSE");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Cannot perform that operation without a nurse.");
      EXPECT_CONTAINS("Added nurse.");
      EXPECT_CONTAINS("Cannot perform that operation without a doctor.");
      EXPECT_CONTAINS("Removed nurse.");
      break;

    case 11:  // Task1-T13
      RUN_COMMAND("REMOVE_DOCTOR 0")
      RUN_COMMAND("ADD_NURSE");
      RUN_COMMAND("REMOVE_DOCTOR 2")
      RUN_COMMAND("ADD_DOCTOR FIFO")
      RUN_COMMAND("REMOVE_DOCTOR 2")
      RUN_COMMAND("REMOVE_DOCTOR 0")
      RUN_COMMAND("REMOVE_NURSE");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Cannot perform that operation without a nurse.");
      EXPECT_CONTAINS("Added nurse.");
      EXPECT_CONTAINS("Cannot perform that operation without a doctor.");
      EXPECT_CONTAINS("Added doctor of type 'FIFO' with ID 0.");
      EXPECT_CONTAINS("No doctor with ID 2.")
      EXPECT_CONTAINS("Removed doctor 0.");
      EXPECT_CONTAINS("Removed nurse.");

      EXPECT_DOES_NOT_CONTAINS("Removed doctor 2", true)
      EXPECT_DOES_NOT_CONTAINS(
          "Cannot perform that operation without first removing doctor(s).",
          true)
      break;

    case 12:  // Task1-T10
      RUN_COMMAND("ADD_NURSE");
      RUN_COMMAND("ADD_DOCTOR FIFO")
      RUN_COMMAND("SHOW_DOCTOR 0")
      RUN_COMMAND("REMOVE_DOCTOR 0")
      RUN_COMMAND("REMOVE_NURSE");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Added nurse.");
      EXPECT_CONTAINS("Added doctor of type 'FIFO' with ID 0.");
      EXPECT_CONTAINS(
          "Doctor 0 is currently assigned 0 patient(s) and has finished seeing "
          "0 patient(s).")
      EXPECT_CONTAINS("Removed doctor 0.");
      EXPECT_CONTAINS("Removed nurse.");
      break;

    case 13:  // Task1-T11
      RUN_COMMAND("SHOW_DOCTOR 0")
      RUN_COMMAND("ADD_NURSE");
      RUN_COMMAND("SHOW_DOCTOR 0")
      RUN_COMMAND("REMOVE_NURSE");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Cannot perform that operation without a nurse.");
      EXPECT_CONTAINS("Added nurse.");
      EXPECT_CONTAINS("Cannot perform that operation without a doctor.");
      EXPECT_CONTAINS("Removed nurse.");
      break;

    case 14:  // Task1-T12
      RUN_COMMAND("ADD_NURSE")
      RUN_COMMAND("ADD_NURSE");
      RUN_COMMAND("ADD_DOCTOR FIFO");
      RUN_COMMAND("ADD_DOCTOR SJN");
      RUN_COMMAND("SHOW_DOCTOR 1");
      RUN_COMMAND("REMOVE_DOCTOR 1");
      RUN_COMMAND("REMOVE_DOCTOR 0");
      RUN_COMMAND("REMOVE_NURSE");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Added nurse.");
      EXPECT_CONTAINS("Cannot add another nurse.");
      EXPECT_CONTAINS("Added doctor of type 'FIFO' with ID 0.");
      EXPECT_CONTAINS("Added doctor of type 'SJN' with ID 1.");
      EXPECT_CONTAINS(
          "Doctor 1 is currently assigned 0 patient(s) and has finished seeing "
          "0 patient(s).");
      EXPECT_CONTAINS("Removed doctor 1.");
      EXPECT_CONTAINS("Removed doctor 0.");
      EXPECT_CONTAINS("Removed nurse.");
      break;

    case 15:  // Task2-T1
      RUN_COMMAND("ADD_NURSE")
      RUN_COMMAND("ADD_DOCTOR FIFO");
      RUN_COMMAND("ADD_PATIENT 10");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Added nurse.");
      EXPECT_CONTAINS("Added doctor of type 'FIFO' with ID 0.");
      EXPECT_CONTAINS("Added patient with ID 0 and consultation time of 10.");
      break;

    case 16:  // Task2-T2
      RUN_COMMAND("ADD_PATIENT 10");
      RUN_COMMAND("ADD_NURSE")
      RUN_COMMAND("ADD_PATIENT 10");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Cannot perform that operation without a nurse.");
      EXPECT_CONTAINS("Added nurse.");
      EXPECT_CONTAINS("Cannot perform that operation without a doctor.");
      break;

    case 17:  // Task2-T10
      RUN_COMMAND("ADD_PATIENT 10");
      RUN_COMMAND("ADD_NURSE")
      RUN_COMMAND("REMOVE_PATIENT 10");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Cannot perform that operation without a nurse.");
      EXPECT_CONTAINS("Added nurse.");
      EXPECT_CONTAINS("Cannot perform that operation without a doctor.");

      EXPECT_DOES_NOT_CONTAINS("Removed patient 10.", true);
      EXPECT_DOES_NOT_CONTAINS("No patient with ID 10", true);
      break;

    case 18:  // Task2-T3
      RUN_COMMAND("ADD_NURSE");
      RUN_COMMAND("ADD_DOCTOR FIFO");
      RUN_COMMAND("ADD_PATIENT 5");
      RUN_COMMAND("ADD_PATIENT 5");
      RUN_COMMAND("REMOVE_PATIENT 1");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Added nurse.");
      EXPECT_CONTAINS("Added doctor of type 'FIFO' with ID 0.");
      EXPECT_CONTAINS("Added patient with ID 0 and consultation time of 5.");
      EXPECT_CONTAINS("Added patient with ID 1 and consultation time of 5.");
      EXPECT_CONTAINS(
          "Removed patient 1 who was not seen by a doctor after waiting 0.")
      break;

    case 19:  // Task2-T11
      RUN_COMMAND("ADD_NURSE");
      RUN_COMMAND("ADD_DOCTOR SJN");
      RUN_COMMAND("ADD_PATIENT 5");
      RUN_COMMAND("ADD_PATIENT 5");
      RUN_COMMAND("SHOW_DOCTOR 0")
      RUN_COMMAND("REMOVE_PATIENT 2");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Added nurse.");
      EXPECT_CONTAINS("Added doctor of type 'SJN' with ID 0.");
      EXPECT_CONTAINS("Added patient with ID 0 and consultation time of 5.");
      EXPECT_CONTAINS("Added patient with ID 1 and consultation time of 5.");
      EXPECT_CONTAINS(
          "Doctor 0 is currently assigned 2 patient(s) and has finished seeing "
          "0 "
          "patient(s).")
      EXPECT_CONTAINS("No patient with ID 2.")

      EXPECT_DOES_NOT_CONTAINS("Removed patient 2", true);
      EXPECT_DOES_NOT_CONTAINS(
          "Patient 0, time arrival 0, consultation time 5, consultation time "
          "remaining 5.",
          true);
      EXPECT_DOES_NOT_CONTAINS(
          "Patient 1, time arrival 0, consultation time 5, consultation time "
          "remaining 5.",
          true);
      break;

    case 20:  // Task2-T4
      RUN_COMMAND("ADD_NURSE");
      RUN_COMMAND("ADD_DOCTOR FIFO");
      RUN_COMMAND("ADD_PATIENT 5");
      RUN_COMMAND("ADD_PATIENT 7");
      RUN_COMMAND("SHOW_PATIENT 0");
      RUN_COMMAND("SHOW_PATIENT 1");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Added nurse.");
      EXPECT_CONTAINS("Added doctor of type 'FIFO' with ID 0.");
      EXPECT_CONTAINS("Added patient with ID 0 and consultation time of 5.");
      EXPECT_CONTAINS("Added patient with ID 1 and consultation time of 7.");
      EXPECT_CONTAINS(
          "Patient 0, time arrival 0, consultation time 5, consultation time "
          "remaining 5.");
      EXPECT_CONTAINS(
          "Patient 1, time arrival 0, consultation time 7, consultation time "
          "remaining 7.");
      break;

    case 21:  // Task2-T12
      RUN_COMMAND("ADD_NURSE");
      RUN_COMMAND("ADD_DOCTOR SJN");
      RUN_COMMAND("ADD_PATIENT 5");
      RUN_COMMAND("ADD_PATIENT 7");
      RUN_COMMAND("SHOW_PATIENT 1");
      RUN_COMMAND("SHOW_PATIENT 2");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Added nurse.");
      EXPECT_CONTAINS("Added doctor of type 'SJN' with ID 0.");
      EXPECT_CONTAINS("Added patient with ID 0 and consultation time of 5.");
      EXPECT_CONTAINS("Added patient with ID 1 and consultation time of 7.");
      EXPECT_CONTAINS(
          "Patient 1, time arrival 0, consultation time 7, consultation time "
          "remaining 7.");
      EXPECT_CONTAINS("No patient with ID 2.")
      break;

    case 22:  // Task2-T5
      RUN_COMMAND("ADD_NURSE")
      RUN_COMMAND("ADD_DOCTOR FIFO");
      RUN_COMMAND("ADD_DOCTOR SJN");
      RUN_COMMAND("ADD_PATIENT 5");
      RUN_COMMAND("ADD_PATIENT 5");
      RUN_COMMAND("ADD_PATIENT 2");
      RUN_COMMAND("ADD_PATIENT 2");
      RUN_COMMAND("TICKTOCK 10");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Added nurse.");
      EXPECT_CONTAINS("Added doctor of type 'FIFO' with ID 0.");
      EXPECT_CONTAINS("Added doctor of type 'SJN' with ID 1.");
      EXPECT_CONTAINS("Added patient with ID 0 and consultation time of 5.");
      EXPECT_CONTAINS("Added patient with ID 1 and consultation time of 5.");
      EXPECT_CONTAINS("Added patient with ID 2 and consultation time of 2.");
      EXPECT_CONTAINS("Added patient with ID 3 and consultation time of 2.");
      EXPECT_CONTAINS(
          "Removed patient 3 who was seen by a doctor after waiting 0.\n"
          "Removed patient 0 who was seen by a doctor after waiting 0.\n"
          "Removed patient 2 who was seen by a doctor after waiting 5.\n"
          "Removed patient 1 who was seen by a doctor after waiting 2.\n"
          "SimClinic clock is now 10.")
      break;

    case 23:  // Task2-T13
      // Hidden smthng about ticktock, remove patient during it
      RUN_COMMAND("ADD_NURSE")
      RUN_COMMAND("ADD_DOCTOR FIFO");
      RUN_COMMAND("ADD_DOCTOR SJN");
      RUN_COMMAND("ADD_PATIENT 5");
      RUN_COMMAND("ADD_PATIENT 5");
      RUN_COMMAND("ADD_PATIENT 2");
      RUN_COMMAND("ADD_PATIENT 2");
      RUN_COMMAND("TICKTOCK 3");
      RUN_COMMAND("REMOVE_PATIENT 0")
      RUN_COMMAND("REMOVE_PATIENT 1")
      RUN_COMMAND("REMOVE_PATIENT 2")
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Added nurse.");
      EXPECT_CONTAINS("Added doctor of type 'FIFO' with ID 0.");
      EXPECT_CONTAINS("Added doctor of type 'SJN' with ID 1.");
      EXPECT_CONTAINS("Added patient with ID 0 and consultation time of 5.");
      EXPECT_CONTAINS("Added patient with ID 1 and consultation time of 5.");
      EXPECT_CONTAINS("Added patient with ID 2 and consultation time of 2.");
      EXPECT_CONTAINS("Added patient with ID 3 and consultation time of 2.");
      EXPECT_CONTAINS(
          "Removed patient 3 who was seen by a doctor after waiting 0.\n"
          "SimClinic clock is now 3.")
      EXPECT_CONTAINS("Patient 0 is currently seeing the doctor.")
      EXPECT_CONTAINS("Patient 1 is currently seeing the doctor.")
      EXPECT_CONTAINS(
          "Removed patient 2 who was not seen by a doctor after waiting 3.")

      EXPECT_DOES_NOT_CONTAINS("Removed patient 0", true);
      EXPECT_DOES_NOT_CONTAINS("Removed patient 1", true);
      break;

    case 24:  // Task2-T14
      // Hidden smthng about ticktock, remove doctor during it
      RUN_COMMAND("ADD_NURSE")
      RUN_COMMAND("ADD_DOCTOR FIFO");
      RUN_COMMAND("ADD_DOCTOR SJN");
      RUN_COMMAND("ADD_PATIENT 5");
      RUN_COMMAND("ADD_PATIENT 5");
      RUN_COMMAND("ADD_PATIENT 2");
      RUN_COMMAND("ADD_PATIENT 2");
      RUN_COMMAND("TICKTOCK 3");
      RUN_COMMAND("REMOVE_PATIENT 0")
      RUN_COMMAND("REMOVE_PATIENT 1")
      RUN_COMMAND("REMOVE_PATIENT 2")
      RUN_COMMAND("SHOW_DOCTOR 1")
      RUN_COMMAND("SHOW_DOCTOR 0")
      RUN_COMMAND("REMOVE_DOCTOR 1")
      RUN_COMMAND("REMOVE_DOCTOR 0")
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Added nurse.");
      EXPECT_CONTAINS("Added doctor of type 'FIFO' with ID 0.");
      EXPECT_CONTAINS("Added doctor of type 'SJN' with ID 1.");
      EXPECT_CONTAINS("Added patient with ID 0 and consultation time of 5.");
      EXPECT_CONTAINS("Added patient with ID 1 and consultation time of 5.");
      EXPECT_CONTAINS("Added patient with ID 2 and consultation time of 2.");
      EXPECT_CONTAINS("Added patient with ID 3 and consultation time of 2.");
      EXPECT_CONTAINS(
          "Removed patient 3 who was seen by a doctor after waiting 0.\n"
          "SimClinic clock is now 3.")
      EXPECT_CONTAINS("Patient 0 is currently seeing the doctor.")
      EXPECT_CONTAINS("Patient 1 is currently seeing the doctor.")
      EXPECT_CONTAINS(
          "Doctor 1 is currently assigned 1 patient(s) and has finished seeing "
          "1 patient(s).")
      EXPECT_CONTAINS(
          "Doctor 0 is currently assigned 1 patient(s) and has finished seeing "
          "0 "
          "patient(s).")
      EXPECT_CONTAINS(
          "Removed patient 2 who was not seen by a doctor after waiting 3.")
      EXPECT_CONTAINS("Doctor 0 is currently with a patient.")
      EXPECT_CONTAINS("Doctor 1 is currently with a patient.")

      EXPECT_DOES_NOT_CONTAINS("Removed doctor 1.", false);
      EXPECT_DOES_NOT_CONTAINS("Removed doctor 0.", false);
      EXPECT_DOES_NOT_CONTAINS("Removed patient 0", true);
      EXPECT_DOES_NOT_CONTAINS("Removed patient 1", true);
      break;

    case 25:  // Task2-T6
      RUN_COMMAND("ADD_NURSE");
      RUN_COMMAND("ADD_DOCTOR QUEUE");
      RUN_COMMAND("ADD_DOCTOR FIFO");
      RUN_COMMAND("REMOVE_DOCTOR -1");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Added nurse.");
      EXPECT_CONTAINS(
          "Invalid command input. Please input the correct argument.");
      EXPECT_CONTAINS("Added doctor of type 'FIFO' with ID 0.");
      EXPECT_CONTAINS(
          "Invalid command input. Please input the correct argument.");
      break;

    case 26:  // Task2-T7
      RUN_COMMAND("ADD_NURSE");
      RUN_COMMAND("ADD_DOCTOR FIFO");
      RUN_COMMAND("ADD_PATIENT 0");
      RUN_COMMAND("ADD_PATIENT 1");
      RUN_COMMAND("REMOVE_PATIENT -1");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Added nurse.");
      EXPECT_CONTAINS("Added doctor of type 'FIFO' with ID 0.");
      EXPECT_CONTAINS(
          "Patient must have have a consultation time longer then 1 minute.");
      EXPECT_CONTAINS("Added patient with ID 0 and consultation time of 1.");
      EXPECT_CONTAINS(
          "Invalid command input. Please input the correct argument.");
      break;

    case 27:  // Task2-T8
      RUN_COMMAND("ADD_NURSE");
      RUN_COMMAND("ADD_DOCTOR FIFO");
      RUN_COMMAND("ADD_PATIENT 5");
      RUN_COMMAND("SHOW_DOCTOR -1");
      RUN_COMMAND("SHOW_PATIENT -1");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Added nurse.");
      EXPECT_CONTAINS("Added doctor of type 'FIFO' with ID 0.");
      EXPECT_CONTAINS("Added patient with ID 0 and consultation time of 5.");
      EXPECT_CONTAINS(
          "Invalid command input. Please input the correct argument.");
      EXPECT_CONTAINS(
          "Invalid command input. Please input the correct argument.");
      break;

    case 28:  // Task2-T9
      RUN_COMMAND("ADD_NURSE");
      RUN_COMMAND("ADD_DOCTOR FIFO");
      RUN_COMMAND("ADD_PATIENT 5");
      RUN_COMMAND("TICKTOCK -1");
      RUN_COMMAND("TICKTOCK 10");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Added nurse.");
      EXPECT_CONTAINS("Added doctor of type 'FIFO' with ID 0.");
      EXPECT_CONTAINS("Added patient with ID 0 and consultation time of 5.");
      EXPECT_CONTAINS(
          "Cannot perform that operation, SimClinic clock cannot go back in "
          "time!");
      EXPECT_CONTAINS("SimClinic clock is now 10.");
      break;

    default:
      cerr << "Test case not found: #" << test_number << endl;
      return TEST_RESULT_FAIL;
  }

  cerr << "PASSED Test " << test_number << "." << endl
       << endl
       << "--------------------------------------------------------------------"
          "--------"
       << endl
       << endl;

  return TEST_RESULT_PASS;
}