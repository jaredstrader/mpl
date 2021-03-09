// -*-c++-*-
//-----------------------------------------------------------------------------
/**
 * @file    test_matplotplusplus.cpp
 * @author  Jared Strader
 */
//-----------------------------------------------------------------------------

#include <matplot/matplot.h>

#include <chrono>
#include <thread>

int main( int argc, char** argv )
{
  std::cout << "Running test_matplotplusplus..." << std::endl;

  std::vector<double> x;
  std::vector<double> y;
  double xtemp = 0;
  double ytemp = 0;
  for (int i=0; i<100; i++) {
    ytemp = xtemp*xtemp;
    x.push_back(xtemp);
    y.push_back(ytemp);
    xtemp =  xtemp + 1;
    matplot::plot(x,y,"ob");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  // matplot::plot(x,y,"ob");
  // matplot::show();

  std::cout << "Terminating..." << std::endl;

  return 0;
}
