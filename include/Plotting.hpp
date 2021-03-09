// -*-c++-*-
//-----------------------------------------------------------------------------
/**
 * @file  Roadmap.hpp
 *
 * <br>@b Author(s):    Jared Strader
 * <br>@b Date:         9/5/20
 *
 */
//-----------------------------------------------------------------------------

#ifndef Plotting_HPP
#define Plotting_HPP

#include <Roadmap.hpp>
#include <matplot/matplot.h>

namespace mpl
{

class Plotting {
  public:
      /** \brief Default parameters for plots */
      std::string PARAM_VERTEX_TYPE = ".b";
      std::string PARAM_EDGE_TYPE = "-k";

      /** \brief Default constructor. */
      inline Plotting(){};

      /** \brief Plot roadmap. */
      void plotRoadmap(const Roadmap & roadmap);

  private:
    /** \brief Extracts vertex set from roadmap represents as points in space */
    const void extractVertices(const Roadmap & roadmap,
                                     std::vector<double> & X,
                                     std::vector<double> & Y) const;

    /** \brief Extracts adjacency list from roadmap */
    const void extractAdjacencyList(const Roadmap & roadmap,
                                          std::vector<std::vector<int>> & E) const;

};


}

#endif // Plotting_HPP
