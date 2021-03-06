// -*-c++-*-
//-----------------------------------------------------------------------------
/**
 * @file  test_isfree.cpp
 *
 * <br>@b Author(s):    Jared Strader
 * <br>@b Date:         9/5/20
 *
 */
//-----------------------------------------------------------------------------

#include <CSpace.hpp>

int main( int argc, char** argv )
{
  std::cout << "Running test_world..." << std::endl;

  std::cout << "\n******************Test Default******************\n";
  mpl::CSpace cspace1;
  cspace1.defineConfigurationSpaceAndObstacles();

  std::cout << "\n******************Test Loading******************\n";
  mpl::CSpace cspace2;
  cspace2.loadConfigurationSpace("configuration_space.txt");
  cspace2.loadObstacles("obstacles.txt");

  std::cout << "\n******************Test isFree******************\n";
  cspace2.testIsFree();

  std::cout << "Terminating..." << std::endl;
  return 0;
}
