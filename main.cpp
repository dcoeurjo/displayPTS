#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <set>
#include "polyscope/polyscope.h"
#include "polyscope/point_cloud.h"

#include "deps/CLI11.hpp"

void processFile(const std::string &filename,
                const std::vector<unsigned int> &vectorCols,
                 size_t n,
                 size_t colX,
                 bool allCols)
{
  std::vector<std::array<double, 3>> pc;
  std::vector<std::vector<double>> alldata;
  std::ifstream ifs(filename);
  double x,y,z;
  std::string line;
  auto cpt = 0u;
  while ((std::getline(ifs, line)) && ( (n ==0) || (cpt < n)))
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
    pc.push_back({data[colX],data[colX+1],data[colX+2]});
    alldata.push_back(data);
  }
  std::cout<<filename<<" "<<alldata[0].size()<<" cols ["
           <<vectorCols.size()<<" vectors, "
           << alldata[0].size()-3*vectorCols.size()-3<<" scalars] "<<alldata.size()<<" points."<<std::endl;
  
  std::vector<double> scalars(alldata.size());
  std::vector<std::array<double, 3>> V;
  if (vectorCols.size() != 0)
    V.resize(alldata.size());
  
  //Polyscope
  auto ps = polyscope::registerPointCloud(filename, pc);
  
  unsigned int indexV;
  for(auto col=0u; col < alldata[0].size(); ++col)
  {
    if (col == colX) continue;
    if (std::find(vectorCols.begin(), vectorCols.end(), col) == vectorCols.end())
    {
      for(auto i=0u; i < alldata.size(); ++i)
        scalars[i] = alldata[i][col];
      ps->addScalarQuantity("Scalar col"+std::to_string(col), scalars);
    }
    else
    {
      for(auto i=0u; i < alldata.size(); ++i)
        V[i] ={alldata[i][col],alldata[i][col+1],alldata[i][col+2]};
        ps->addVectorQuantity("Vector col"+std::to_string(col), V);
     col +=2;
    }
  }
  
  if (allCols)
  {
    for(auto col=0u; col < alldata[0].size(); ++col)
    {
      for(auto i=0u; i < alldata.size(); ++i)
       scalars[i] = alldata[i][col];
      ps->addScalarQuantity("_(allCols) "+std::to_string(col), scalars);
    }
  }
}

int main(int argc, char **argv)
{
  CLI::App app{"displayPTS"};
  std::vector<std::string> filenames;
  app.add_option("-i,--input,1", filenames, "Input point clouds")
     ->required();
  std::vector<unsigned int> vectorCols;
  app.add_option("--vectorCols,-v", vectorCols, "Indices of columns to group as vectors (col col+1 col+2)");
  bool allCols=false;
  app.add_flag("--all,-a", allCols, "Expose all columns (including positions and vector components) as scalar quantities");
  size_t colX=0;
  app.add_option("--colX,-c", colX, "Index of the column c containing the 'x', (c+1 and c+2 will be 'y' and 'z'");
  size_t nbPts=0;
  app.add_option("--nbPts,-n", nbPts, "Number of points to display (0 = all points).");
  CLI11_PARSE(app,argc,argv);
  
  auto errorMSG=[&](const size_t vi, const size_t vj){
    std::cout<<"Error while parsing the vectorCols: ";
    std::cout<<"("<<vi<<","<<vi+1<<","<<vi+2<<") overlaps with "<<"("<<vj<<","<<vj+1<<","<<vj+2<<")"<<std::endl;
    exit(2);
  };
  
  //Check the consistency of the param.
  for(auto i=0u; i < vectorCols.size(); ++i)
  {
    for(auto j=i+1; j < vectorCols.size(); ++j)
    {
      if ((vectorCols[j] == vectorCols[i]) || (vectorCols[j] == vectorCols[i]+1) || (vectorCols[j] == vectorCols[i]+2))
        errorMSG(vectorCols[i], vectorCols[j]);
    }
  }
  
  // Initialize polyscope
  polyscope::init();

  //Process all files
  for(auto &filename: filenames)
    processFile(filename,vectorCols,nbPts,colX,allCols);
  
  // Give control to the polyscope gui
  polyscope::show();

  return EXIT_SUCCESS;
}
