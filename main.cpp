#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "polyscope/polyscope.h"
#include "polyscope/point_cloud.h"

#include "imgui.h"

int main(int argc, char **argv)
{

  std::string filename= argv[1];
  // Initialize polyscope
  polyscope::init();

  std::vector<std::array<double, 3>> pc;
  std::ifstream ifs(filename);
  double x,y,z;
  while (ifs.good())
  {
    ifs>>x>>y>>z;
    pc.push_back({x,y,z});
  }
  polyscope::registerPointCloud("input", pc);
  
  // Give control to the polyscope gui
  polyscope::show();

  return EXIT_SUCCESS;
}
