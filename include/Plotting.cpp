// -*-c++-*-
//-----------------------------------------------------------------------------
/**
 * @file    Plotting.cpp
 * @author  Jared Strader
 */
//-----------------------------------------------------------------------------

#include <Plotting.hpp>

namespace mpl
{

//////////////////////////////////////////////////////////////////////////////
//                                PUBLIC
//////////////////////////////////////////////////////////////////////////////

void Plotting::
plotRoadmap(const Roadmap & roadmap) {
  //vertices
  std::vector<double> X;
  std::vector<double> Y;
  extractVertices(roadmap, X, Y);

  //edges
  std::vector<std::vector<int>> E;
  extractAdjacencyList(roadmap, E);

  //plot edges
  std::vector<double> x;
  std::vector<double> y;
  for(auto e : E) {
    x.push_back(X[e[0]]);
    x.push_back(X[e[1]]);
    x.push_back(std::nan(""));
    y.push_back(Y[e[0]]);
    y.push_back(Y[e[1]]);
    y.push_back(std::nan(""));
  }
  plt::hold(plt::on);
  auto h1 = plt::plot(x,y,PARAM_EDGE_TYPE.c_str());
  h1->line_width(PARAM_EDGE_WIDTH);

  //plot vertices
  plt::hold(plt::on);
  auto h2 = plt::plot(X,Y,PARAM_VERTEX_TYPE.c_str());
  h2->marker_size(PARAM_MARKER_SIZE);

  //show plot
  plt::axis(plt::square);
  const std::vector<double> mins = roadmap.cspace_.getMinimums();
  const std::vector<double> maxs = roadmap.cspace_.getMaximums();
  plt::xlim({mins[0], maxs[0]});
  plt::ylim({mins[1], maxs[1]});
  plt::xlabel("X");
  plt::ylabel("Y");

  return;
};

void Plotting::
plotPath(const Roadmap          & roadmap, 
         const std::vector<int> & path) {
  //vertices
  std::vector<double> X;
  std::vector<double> Y;
  extractVertices(roadmap, X, Y);
  std::vector<double> x_pts;
  std::vector<double> y_pts;
  for(int i=0; i<path.size(); i++) {
    x_pts.push_back(X[path[i]]);
    y_pts.push_back(Y[path[i]]);
  }

  //edges
  std::vector<double> x;
  std::vector<double> y;
  for(int i=0; i<path.size()-1; i++) {
    x.push_back(X[path[i]]);
    x.push_back(X[path[i+1]]);
    y.push_back(Y[path[i]]);
    y.push_back(Y[path[i+1]]);
  }
  
  //plot edges
  plt::hold(plt::on);
  auto h1 = plt::plot(x,y,PARAM_PATH_EDGE_TYPE.c_str());
  h1->line_width(PARAM_PATH_EDGE_WIDTH);

  //plot vertices
  plt::hold(plt::on);
  auto h2 = plt::plot(x_pts,y_pts,PARAM_PATH_VERTEX_TYPE.c_str());
  h2->marker_size(PARAM_MARKER_SIZE);

  return;
};

void Plotting::
plotPolygons(const Roadmap & roadmap) {
  std::vector<CSpace::Obstacle> polygons = roadmap.cspace_.getObstacles();
  
  std::vector<double> x;
  std::vector<double> y;
  for(auto p : polygons) {
    for(int i=0; i<p.pts.size(); i++) {
      std::vector<double> pt = p.pts[i];
      assert(pt.size()==2);
      x.push_back(pt[0]);
      y.push_back(pt[1]);
    }
    x.push_back(p.pts[0][0]);
    y.push_back(p.pts[0][1]);
    x.push_back(std::nan(""));
    y.push_back(std::nan(""));
  }

  plt::hold(plt::on);
  plt::fill(x,y,"r");
  plt::hold(plt::on);
  plt::plot(x,y,PARAM_POLYGON_EDGE_TYPE.c_str());

  return;
};

//////////////////////////////////////////////////////////////////////////////
//                                PRIVATE
//////////////////////////////////////////////////////////////////////////////

const void Plotting::
extractVertices(const Roadmap             & roadmap,
                      std::vector<double> & X,
                      std::vector<double> & Y) const {
  std::vector<std::vector<double>> V = roadmap.samples_;
  X.clear();
  Y.clear();
  X.resize(V.size());
  Y.resize(V.size());
  for(int i=0; i<V.size(); i++) {
    X[i] = V[i][0];
    Y[i] = V[i][1];
  }
  return;
};

const void Plotting::
extractAdjacencyList(const Roadmap                       & roadmap,
                           std::vector<std::vector<int>> & E) const {
  E.clear();
  for(int i=0; i<roadmap.G_->n_; i++) {
    for(auto edge : roadmap.G_->adj_[i]) {
      assert(i == edge.src_);
      int idx_i = edge.src_;
      int idx_j = edge.dst_;
      std::vector<int> e = {idx_i,idx_j};
      E.push_back(e);
    }
  }
  return;
};

}