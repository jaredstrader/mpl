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
  matplot::plot(x,y,PARAM_EDGE_TYPE.c_str());

  //plot vertices
  matplot::hold(matplot::on);
  auto h = matplot::plot(X,Y,PARAM_VERTEX_TYPE.c_str());

  //show plot
  matplot::axis(matplot::square);
  const std::vector<double> mins = roadmap.cspace_.getMinimums();
  const std::vector<double> maxs = roadmap.cspace_.getMaximums();
  matplot::xlim({mins[0], maxs[0]});
  matplot::ylim({mins[1], maxs[1]});
  matplot::xlabel("X");
  matplot::ylabel("Y");
  matplot::show();
};

//////////////////////////////////////////////////////////////////////////////
//                                PRIVATE
//////////////////////////////////////////////////////////////////////////////

const void Plotting::
extractVertices(const Roadmap             & roadmap,
                      std::vector<double> & X,
                      std::vector<double> & Y) const {
  std::vector<std::vector<double>> V = roadmap.getVertices();
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