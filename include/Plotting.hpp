// -*-c++-*-
//-----------------------------------------------------------------------------
/**
 * @file    Plotting.hpp
 * @author  Jared Strader
 */
//-----------------------------------------------------------------------------

#ifndef Plotting_HPP
#define Plotting_HPP

#include <Roadmap.hpp>
#include <matplot/matplot.h>

namespace mpl
{

namespace plt = matplot;

class Plotting {
  public:
      /** \brief Visualization parameters for plots initialized as defaults */
      std::string PARAM_VERTEX_TYPE = ".b";
      std::string PARAM_EDGE_TYPE = "-k";
      int PARAM_EDGE_WIDTH = 1;
      std::string PARAM_PATH_VERTEX_TYPE = ".g";
      std::string PARAM_PATH_EDGE_TYPE = "-g";
      int PARAM_PATH_EDGE_WIDTH = 2;
      std::string PARAM_POLYGON_FILL_TYPE = "r";
      std::string PARAM_POLYGON_EDGE_TYPE = "-k";
      int PARAM_MARKER_SIZE = 4;

      /** \brief Default constructor. */
      inline Plotting(){};

      /** \brief Plot roadmap. */
      void plotRoadmap(const Roadmap & roadmap) ;

      /** \brief Plot path */
      void plotPath(const Roadmap              & roadmap, 
                    const std::vector<int>     & path);

      /** \brief Plot polygons */
      void plotPolygons(const Roadmap & roadmap);

  private:
    /** \brief Extracts vertex set from roadmap represents as points in space */
    const void extractVertices(const Roadmap             & roadmap,
                                     std::vector<double> & X,
                                     std::vector<double> & Y) const;

    /** \brief Extracts adjacency list from roadmap */
    const void extractAdjacencyList(const Roadmap                       & roadmap,
                                          std::vector<std::vector<int>> & E) const;

};


}

#endif // Plotting_HPP
