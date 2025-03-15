#include "plot.hpp"

// cannot call Py_Init and Py_Fin each time Plot::run() is used
bool python::instance_running = false;

void python::shutdown() {
  Py_Finalize();
  instance_running = false;
}

void python::start() {
  Py_Initialize();
  instance_running = true;
  std::atexit(
      shutdown); // should only shutdown the py instance when main() exits
}
