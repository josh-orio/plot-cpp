#include <iostream>

#include "nlohmann/json.hpp"
#include <plot-cpp/plot.hpp>

int main() {
  int x[] = {-3, -2, -1, 0, 1, 2, 3};
  int y[] = {-27, -8, -1, 0, 1, 8, 27};

  nlohmann::json data_dict;
  data_dict["x"] = x;
  data_dict["y"] = y;
  data_dict["title"] = "Example Graph: f(x) = x^3";
  data_dict["xlabel"] = "X Axis";
  data_dict["ylabel"] = "Y Axis";

  std::cout << data_dict.dump(2) << std::endl;

  // // create plot obj then run shader
  // Plot plot1("../shader.py", data_dict.dump());
  // plot.run();

  // // ensure no variable persistence between instances
  // Plot plot2("../shader.py", "{}", true);

  // create plot with 'autorun' enabled, this should be the default
  Plot plot3("../shader.py", data_dict.dump(), true);
  std::cout << "graphed" << std::endl;

  return 0;
}
