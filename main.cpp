#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <set>
#include "polyscope/polyscope.h"
#include "polyscope/point_cloud.h"

#include "CLI11.hpp"


void processFile(const std::string &filename,
                const std::vector<unsigned int> &vectorsCol)
{
  std::vector<std::array<double, 3>> pc;
  std::vector<std::vector<double>> alldata;
  std::ifstream ifs(filename);
  double x,y,z;
  std::string line;
  while(std::getline(ifs, line))
  {
    std::stringstream   linestream(line);
    std::vector<double> data;
    auto i=0;
    while(linestream.good())
    {
      double v;
      linestream >> v;
      data.push_back(v);
      ++i;
    }
    pc.push_back({data[0],data[1],data[2]});
    alldata.push_back(data);
  }
  std::cout<<filename<<" "<<alldata[0].size()<<" cols ["
           <<vectorsCol.size()<<" vectors, "
           << alldata[0].size()-3*vectorsCol.size()-3<<" scalars]"<<std::endl;
  //Polyscope
  auto ps = polyscope::registerPointCloud(filename, pc);
  
  unsigned int indexV;
  for(auto col=3u; col < alldata[0].size(); ++col)
  {
    if (std::find(vectorsCol.begin(), vectorsCol.end(), col) == vectorsCol.end())
    {
      std::vector<double> H;
      for(auto i=0u; i < alldata.size(); ++i)
        H.push_back(alldata[i][col]);
      ps->addScalarQuantity("Scalar col"+std::to_string(col), H);
    }
    else
    {
      std::vector<std::array<double, 3>> V;
      for(auto i=0u; i < alldata.size(); ++i)
        V.push_back({alldata[i][col],alldata[i][col+1],alldata[i][col+2]});
        ps->addVectorQuantity("Vector col"+std::to_string(col), V);
     col +=2;
    }
  }
}

int main(int argc, char **argv)
{
  CLI::App app{"displayPTS"};
  std::vector<std::string> filenames;
  app.add_option("-i,--input,1", filenames, "Input point clouds")
     ->required();
  std::vector<unsigned int> vectorsCol;
  app.add_option("--vectors", vectorsCol, "Indices of columns to group as vectors (col col+1 col+2)");
  CLI11_PARSE(app,argc,argv);
  
  // Initialize polyscope
  polyscope::init();

  //Process all files
  for(auto &filename: filenames)
    processFile(filename,vectorsCol);

  
  // Give control to the polyscope gui
  polyscope::show();

  return EXIT_SUCCESS;
}
