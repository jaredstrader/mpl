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

  std::cout << "\n******************Test Roadmap (mins, maxs)******************\n";
  std::vector<double> mins = {-5, -5};
  std::vector<double> maxs = { 5,  5};
  mpl::Roadmap roadmap(mins, maxs);
  
  //generate PRM
  roadmap.runQRM(500, 0.7, 0.02);

  mpl::Plotting plotting;
  plotting.plotRoadmap(roadmap);

  roadmap.computePath({0,0},{5,5});

  // std::cout << "\n******************Test Roadmap GUI******************\n";
  // mpl::Roadmap roadmap2;

  // std::cout << "\n******************Test Roadmap Load******************\n";
  // // mpl::Roadmap roadmap3("configuration_space.txt","obstacles.txt");

  // std::cout << "\n******************Test Roadmap Run******************\n";
  // roadmap1.runPRM(200, 1.2, 0.1);
  // roadmap1.getPath({0,0},{5,5});

  std::cout << "Terminating..." << std::endl;
  return 0;
}
