// -*-c++-*-
//-----------------------------------------------------------------------------
/**
 * @file  Roadmap.cpp
 *
 * <br>@b Author(s):    Jared Strader
 * <br>@b Date:         9/5/20
 *
 */
//-----------------------------------------------------------------------------

#include <Roadmap.hpp>

namespace mpl
{

void Roadmap::
runPRM(int iterations, double radius, double step_size) {
  run(iterations, radius, step_size, UNIFORM);
};

void Roadmap::
runQRM(int iterations, double radius, double step_size) {
  run(iterations, radius, step_size, HAMMERSLEY);
};

void Roadmap::
runLRM(int iterations, double radius, double step_size) {
  run(iterations, radius, step_size, LATTICE);
};

void Roadmap::
run(int iterations, double radius, double step_size, int sample_type) {
  //sample points in configuration space
  samples_.clear();
  switch(sample_type) {
    case Roadmap::UNIFORM:
      samples_ = sampleUniform(iterations);
      break;
    case Roadmap::HAMMERSLEY:
      samples_ = sampleHammersley(iterations);
      break;
    case Roadmap::LATTICE:
      samples_ = sampleLattice(iterations);
      break;
  }

  //init graph
  int n = samples_.size();
  G_ = new Graph(n);

  //add edges
  for(int i=0; i<samples_.size(); i++) {
    for(int j=0; j<samples_.size(); j++)  {
      if(i != j) {
        if(utils::dist(samples_[i], samples_[j]) > radius) {
          continue;
        }

        //check if path is collision free
        std::vector< std::vector<double> > path;
        bool success = steer(samples_[i], samples_[j], radius, step_size, path);

        //if collision free, add edge with weight
        if(success) {
          double w = utils::dist(samples_[i], samples_[j]);
          G_->addEdgeDirected(i,j,w);
        }
      }
    }
  }

  //print edges
  // G_->printEdges();

  // Plotter plotter;
  // plotter.plotRoadmap(samples_, G_->getEdges());
  // plotter.plotRoadmap();
};

// void Roadmap::
// addVertex(std::vector<double> point) {};

void Roadmap::
getPath(const std::vector<double> & start, 
        const std::vector<double> & goal) {
  double max_val;

  //index of start vertex
  max_val = 1e9;
  double start_idx = -1;
  for(int i=0; i<samples_.size(); i++) {
    double val = utils::dist(start, samples_[i]);
    if(val < max_val) {
      max_val = val;
      start_idx = i;
    }
  }

  //index of goal vertex
  max_val = 1e9;
  double goal_idx = -1;
  for(int i=0; i<samples_.size(); i++) {
    double val = utils::dist(goal, samples_[i]);
    if(val < max_val) {
      max_val = val;
      goal_idx = i;
    }
  }

  //search graph for shortest path
  G_->runDijkstras(start_idx);
};

std::vector< std::vector<double> > Roadmap::
sampleUniform(int n) {
  std::cout << "sampling configuration space (UNIFORM)" << std::endl;
  std::vector< std::vector<double> > sampled_points;
  int iter = 0;
  double x;
  double y;
  unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 rng(seed);
  std::uniform_real_distribution<double> x_dist(cspace_.getMinimums()[0], 
                                                cspace_.getMaximums()[0]);
  std::uniform_real_distribution<double> y_dist(cspace_.getMinimums()[1], 
                                                cspace_.getMaximums()[1]);
  while(iter < n) {
    //sample from uniform
    x = x_dist(rng);
    y = y_dist(rng);

    if(!cspace_.isFree({x,y})) { //check if in free space
      iter++;
      continue;
    }
    sampled_points.push_back({x, y}); //add to sampled points
    iter++;
  }

  return sampled_points;
};

std::vector< std::vector<double> > Roadmap::
sampleHammersley(int n) {
  std::cout << "sampling config space (HAMMERSLEY)" << std::endl;
  std::vector< std::vector<double> > sampled_points;
  int iter = 0;
  int k    = 1;
  double x;
  double y;
  while(iter < n) {
    //needed for calculating x and y (see paper)
    if(utils::isPrime(k)) {
      iter++;
    }
    else {
      k++;
      continue;
    }

    //x
    x = cspace_.getMinimums()[0] + static_cast<double>(iter) 
      / static_cast<double>(n) 
      * (cspace_.getMaximums()[0] - cspace_.getMinimums()[0]); 

    //y
    std::vector<int> b = utils::convertDecimalToBinary(iter);
    y = 0;
    for(int i=0; i<b.size(); i++) {
      y = y + static_cast<double>(b[i])/utils::powd(k,i+1);
    }
    y = cspace_.getMinimums()[1] 
      + y*(cspace_.getMaximums()[1] - cspace_.getMinimums()[1]);

    
    if(!cspace_.isFree({x,y})) { //check if point in free space
      continue;
    }

    sampled_points.push_back({x, y}); //add to sampled points
  }

  return sampled_points;
};

std::vector< std::vector<double> > Roadmap::
sampleLattice(int n) {
  std::cout << "sampling config space (LATTICE)" << std::endl;
  std::vector< std::vector<double> > sampled_points;
  int iter = 0;
  double alpha = (std::sqrt(5.0) + 1.0) / 2.0; //golden ratio
  double x;
  double y;
  while(iter < n) {
    //x
    x = cspace_.getMinimums()[0] + static_cast<double>(iter) / 
      static_cast<double>(n) *
      (cspace_.getMaximums()[0] - cspace_.getMinimums()[0]);

    //y
    double f = static_cast<double>(iter)*alpha 
      - static_cast<long>((static_cast<double>(iter)*alpha));
    y = cspace_.getMinimums()[1] 
      + f*(cspace_.getMaximums()[1] - cspace_.getMinimums()[1]);

    if(!cspace_.isFree({x,y})) { //check if point in free space
      iter++;
      continue;
    }

    sampled_points.push_back({x, y}); //add to sampled points
    iter++;
  }

  return sampled_points;
};

bool Roadmap::
steer(const std::vector<double>                & x,
      const std::vector<double>                & y,
            double                               radius,
            double                               step_size,
            std::vector< std::vector<double> > & path) const {
  assert(x.size() == y.size());

  bool success = false;
  double err = utils::dist(x, y);
  path.clear();
  path.push_back(x);
  while(1) {
    std::vector<double> z = path.back();
    z = step(z, y, step_size);

    //break if any point in path not in free space
    if(!cspace_.isFree(z)) { 
      success = false;
      break;
    } 

    //break if distance exceeds radius
    if(utils::dist(x, z) > radius) {
      break;
    }
    
    //break before path passes target
    if (utils::dist(z, y) - err >= 0) {
      break;
    }

    err = utils::dist(z, y);
    path.push_back(z);
    success=true;
  }

  return success;
}

std::vector<double> Roadmap::
step(const std::vector<double> & x,
     const std::vector<double> & y,
           double                step_size) const {
  assert(x.size() == y.size());

  double norm = utils::dist(x,y);
  std::vector<double> z;
  for(int i=0; i<x.size(); i++) {
    z.push_back( step_size*(y[i] - x[i])/norm );
  }

  return z;
}

}