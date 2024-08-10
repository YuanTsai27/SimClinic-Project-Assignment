# SimClinic Project Assignment (Completed October 2023)

This project is focused around enhancing my skills in applying object-oriented programming and abstract data type concepts in c++.

The abstract data type utilised in this project is a linked list with nodes which I have written a customised version of myself in the codebase - that have proved to structure my code effectively with efficient sharing of information between many object classes in the program.

Other core OOP concepts etc inheritance, abstract classes, polymorphism were once again efficiently utilised.


**Code Style**
Throughout this project, I have adhered to the Google C++ Style Guide, ensuring that the code is clean, consistent, and follows industry-standard practices.

**Feel free to check this project out!** _To run this project, cmake is required._

# How to use (terminal)

* **Build:** Create a `build` directory for the output (if it doesn't already exist), generate the build files in it, then run it:
  ```bash
  mkdir build
  cd build
  cmake ..          # generates the build files
  cmake --build .   # execute the build and creates the executable(s)
  ```

* **Run:** Run the program interactively:
  ```bash
  cd build
  ./simclinic
  ```

* **Test:** Run the test cases:
  ```bash
  cd build
  ctest     # minimal output
  ctest -V  # verbose output
  ctest --output-on-failure  # verbose for failing test cases, but minimal for tests that pass
  ctest -V -R T1 # run a single specific test case in verbose mode
  ```
