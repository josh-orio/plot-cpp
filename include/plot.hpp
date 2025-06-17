#ifndef PLOT_HPP
#define PLOT_HPP

#include <Python.h>
#include <fstream>
#include <iostream>

namespace python {
extern bool instance_running;

void shutdown();
void start();
} // namespace python

class Plot {
public:
  std::string shader;
  std::string data;

  Plot();
  Plot(std::string sf, std::string d);
  Plot(std::string sf, std::string d, bool autorun);

  void run();
};

#endif
