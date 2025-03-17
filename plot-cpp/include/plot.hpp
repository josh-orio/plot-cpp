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

  Plot(){};

  Plot(std::string sf, std::string d) {
    if (std::filesystem::exists(sf)) {
      std::vector<char> bin(std::filesystem::file_size(sf));

      std::ifstream i(sf, std::ifstream::binary);
      i.read(bin.data(), bin.size());
      i.close();

      shader = std::string(bin.begin(), bin.end());
    } else {
      shader = "";
    }

    data = d;
  };

  Plot(std::string sf, std::string d, bool autorun) {
    if (std::filesystem::exists(sf)) {
      std::vector<char> bin(std::filesystem::file_size(sf));

      std::ifstream i(sf, std::ifstream::binary);
      i.read(bin.data(), bin.size());
      i.close();

      shader = std::string(bin.begin(), bin.end());
    } else {
      shader = "";
    }

    data = d;

    if (autorun) {
      run();
    }
  };

  void run() {
    // python instance must be started if not already running
    if (!python::instance_running) {
      python::start();
    }

    // copy data dict to python
    PyObject *main_module = PyImport_AddModule("__main__");
    PyObject *main_dict = PyModule_GetDict(main_module);
    PyObject *py_string =
        PyUnicode_Decode(data.c_str(), data.size(), nullptr, nullptr);
    PyDict_SetItemString(main_dict, "data_dict", py_string);

    // run some code to unpack the data_dict into variables
    // where variable name == key
    std::string loading_shader =
        "import json\n"
        "data_dict = json.loads(data_dict)\n"
        "for key in data_dict:\n"
        "\tif type(data_dict[key]) == str:\n"
        // if string, add extra quotes
        "\t\tdata_dict[key] = \"'\" + data_dict[key] + \"'\"\n"
        "\texec(key + \" = \" + str(data_dict[key]))\n";
    PyRun_SimpleString(loading_shader.c_str());

    // run the 'real' shader
    PyRun_SimpleString(shader.c_str());

    // must clear the (python) variable dictionary
    // otherwise variables will persist between instances of Plot class
    PyDict_Clear(main_dict);
  }
};

#endif
