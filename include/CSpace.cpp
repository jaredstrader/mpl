// -*-c++-*-
//-----------------------------------------------------------------------------
/**
 * @file  CSpace.cpp
 *
 * <br>@b Author(s):    Jared Strader
 * <br>@b Date:         9/5/20
 *
 */
//-----------------------------------------------------------------------------

#include <CSpace.hpp>

namespace mpl
{

bool CSpace::
isFree(std::vector< std::vector<double> > pts) const {
  //loop through pts and return false if pt not in free space
  for(auto pt : pts) {
    if(!isFree(pt)) {
      return false;
    }
  }

  return true;
};

bool CSpace::
isFree(std::vector<double> pt) const {
  //TODO: only supports 2D, need to update
  assert(pt.size() == 2);

  //loop through osbtacles and return false if pt inside any obstacle
  for(auto obs : obstacles_) {
    if(utils::inPolygon(pt, obs.pts)) {
      return false;
    }
  }

  return true;
};

bool CSpace::
loadConfigurationSpace(std::string filepath) {
  //open file containing obstacles
  std::ifstream input_file;
  input_file.open(filepath.c_str());
  if(!input_file) {
    std::cout << "Error! Failed to open file: " << filepath.c_str() << "!\n";
    return false;
  }

  //load configuration space
  double xmin;
  double xmax;
  double ymin;
  double ymax;
  input_file >> xmin;
  input_file >> xmax;
  input_file >> ymin;
  input_file >> ymax;
  minimums_.clear();
  minimums_.push_back(xmin);
  minimums_.push_back(ymin);
  maximums_.clear();
  maximums_.push_back(xmax);
  maximums_.push_back(ymax);

  //close file
  input_file.close();

  //print configuration space (only for testing)
  std::cout << "\nLoaded Configuration Space:\n";
  std::cout << "xmin = " << xmin << std::endl;
  std::cout << "xmax = " << xmax << std::endl;
  std::cout << "ymin = " << ymin << std::endl;
  std::cout << "ymax = " << ymax << std::endl;

  return true;
};

bool CSpace::
loadObstacles(std::string filepath) {
  //open file containing obstacles
  std::ifstream input_file;
  input_file.open(filepath.c_str());
  if(!input_file) {
    std::cout << "Error! Failed to open file: " << filepath.c_str() << "!\n";
    return false;
  }

  //load polygons
  obstacles_.clear();
  std::string line;
  while(std::getline(input_file, line)) { //loop over lines in input file
    Obstacle obs;
    bool end_of_line = false;
    std::istringstream tmp(line);
    while(!end_of_line) { //loop elements in row of input file
      std::vector<double> pt;
      int N=2; //number of dimensions of each points, only support 2D for now
      for(int i=0; i<N; i++) { //only supports points in 2D for now
        double val;
        if(tmp >> val) {
          pt.push_back(val);
        }
        else {
          end_of_line = true; //if end of line is reached, then move to next polygon
        }
      }
      if(!end_of_line) {
        obs.pts.push_back(pt);
      }
    }
    obstacles_.push_back(obs);
  }

  //close file
  input_file.close();

  //print polygons (only for testing)
  std::cout << "\nLoaded Obstacles:\n";
  int k = 0;
  for(auto obs : obstacles_) {
    std::cout << "obstacle[" << k << "]:" << std::endl;
    k++; 
    for(int i=0; i<obs.pts.size(); i++) {
      std::cout << "pt " << i << " =";
      for(int j=0; j<obs.pts[i].size(); j++) {
        std::cout << " " << obs.pts[i][j];
      }
      std::cout << std::endl;
    }
  }

  return true;
};

}
