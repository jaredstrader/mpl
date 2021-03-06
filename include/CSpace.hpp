// -*-c++-*-
//-----------------------------------------------------------------------------
/**
 * @file  CSpace.hpp
 *
 * <br>@b Author(s):    Jared Strader
 * <br>@b Date:         9/5/20
 *
 */
//-----------------------------------------------------------------------------

#ifndef CSpace_HPP
#define CSpace_HPP

#include <utils.hpp>

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cassert>

namespace mpl
{

class CSpace {
  public:
    /** \brief Default constructor. Does nothing. */
    inline CSpace() {};

    /** \brief Default constructor. Init configuration space without
    obstacles. */
    inline CSpace(const std::vector<double> & minimums,
                  const std::vector<double> & maximums)
    :minimums_(minimums), 
     maximums_(maximums) {};

     /** \brief */
     const std::vector<double> getMinimums() const {return minimums_;};

     /** \brief */
     const std::vector<double> getMaximums() const {return maximums_;};

    /** \brief Load minimum and maximum values for each dimension of 
    configuration space from specified file */
    bool loadConfigurationSpace(std::string filepath);

    /** \brief Load vertices defining polygon obstacles from specified file */
    bool loadObstacles(std::string filepath);

    /** \brief Returns true if all configurations in pts belongs to the 
    free configuration space and false if any configuration in pts is in 
    the interior of an obstacle*/
    bool isFree(std::vector< std::vector<double> > pts) const;

    /** \brief Returns true if configuration config belongs to the free 
    configuration space and false if configuration config is in the interior 
    of an obstacle*/
    bool isFree(std::vector<double> pt) const;

  private:
    /** \brief Struct for defining obstacles where pts[i] is a vector 
    representing the ith vertex of the polygon representing the obstacle */
    struct Obstacle {
      std::vector< std::vector<double> > pts;
    };
    
    /** \brief List of obstacles represented as an std::vector  */
    std::vector<Obstacle> obstacles_;

    /** \brief Configuration space represented as minimums and maximums of
    each dimension */
    std::vector<double> minimums_;
    std::vector<double> maximums_;

    /** \brief A python interpreter obejct required for accessing python 
    scripts. This object calls Py_Initialize() and Py_Finalize() */
    // CPyInstance cpy_instance_;

};

}

#endif // CSpace_HPP
