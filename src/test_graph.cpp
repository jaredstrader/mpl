// -*-c++-*-
//-----------------------------------------------------------------------------
/**
 * @file  test_graph.cpp
 *
 * <br>@b Author(s):    Jared Strader
 * <br>@b Date:         9/5/20
 *
 */
//-----------------------------------------------------------------------------

#include <Graph.hpp>

#include <iostream>

int main( int argc, char** argv )
{
  std::cout << "Running test_graph..." << std::endl;

  /*
   * Create the following graph
   * 0-1
   * |X|
   * 2-3
   *  \|
   *   4
   */
  mpl::Graph G(5);
  G.addEdgeUndirected(0,1,1);
  G.addEdgeUndirected(0,2,1);
  G.addEdgeUndirected(0,3,1.414);
  G.addEdgeUndirected(1,2,1.414);
  G.addEdgeUndirected(1,3,1);
  G.addEdgeUndirected(2,3,1);
  G.addEdgeUndirected(2,4,1.414);
  G.addEdgeUndirected(3,4,1);

  G.algBellmanFord(0);
  G.algDijkstras(0);
  G.algFloydWarshall();

  std::cout << "Terminating..." << std::endl;
  return 0;
}
