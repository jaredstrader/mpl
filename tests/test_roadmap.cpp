// -*-c++-*-
//-----------------------------------------------------------------------------
/**
 * @file  test_roadmap.cpp
 *
 * <br>@b Author(s):    Jared Strader
 * <br>@b Date:         9/5/20
 *
 */
//-----------------------------------------------------------------------------

#include <Roadmap.hpp>
#include <Plotting.hpp>

#include <matplot/matplot.h>

int main( int argc, char** argv )
{
  std::cout << "Running test_world..." << std::endl;

  // std::cout << "\n******************Test Roadmap (mins, maxs)******************\n";
  // std::vector<double> mins = {-5, -5};
  // std::vector<double> maxs = { 5,  5};
  // mpl::Roadmap roadmap(mins, maxs); //initialize roadmap without obstacles
  
  // roadmap.runPRM(1000, 1.0, 0.02); //generate roadmap
  // std::vector<int> path = roadmap.computePath({-5,-5},{5,5}); //compute path from roadmap

  std::cout << "\n******************Test Roadmap Load******************\n";
  mpl::Roadmap roadmap("configuration_space.txt","obstacles.txt"); //initialize roadmap with obstacles

  // std::cout << "\n******************Test Roadmap Run******************\n";
  roadmap.runPRM(1000, 1.0, 0.1);
  std::vector<int> path = roadmap.computePath({-5,-5},{5,5});

  matplot::figure(true); //true == quite, false == reactive
  mpl::Plotting plotting;
  plotting.plotPolygons(roadmap);
  plotting.plotRoadmap(roadmap);
  plotting.plotPath(roadmap, path);
  matplot::show();

  std::cout << "Terminating..." << std::endl;
  return 0;
}
