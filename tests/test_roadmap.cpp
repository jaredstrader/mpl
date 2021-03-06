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

int main( int argc, char** argv )
{
  std::cout << "Running test_world..." << std::endl;

  std::cout << "\n******************Test Roadmap (mins, maxs)******************\n";
  std::vector<double> mins = {-5, -10};
  std::vector<double> maxs = { 5,  10};
  mpl::Roadmap roadmap(mins, maxs);
  // roadmap.runPRM(200, 1.2, 0.1);
  // roadmap.getPath({0,0},{5,5});

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
