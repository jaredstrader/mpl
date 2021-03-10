// -*-c++-*-
//-----------------------------------------------------------------------------
/**
 * @file    Roadmap.hpp
 * @author  Jared Strader
 */
//-----------------------------------------------------------------------------

#ifndef Roadmap_HPP
#define Roadmap_HPP

#include <CSpace.hpp>
#include <Graph.hpp>
#include <utils.hpp>

#include <iostream>
#include <vector>
#include <random>
#include <chrono>

namespace mpl
{

class Roadmap {
  public:
      /** \brief Default constructor. Init configuration space without
      obstacles. */
      inline Roadmap(const std::vector<double> & minimums,
                     const std::vector<double> & maximums)
      :G_(NULL) {
        cspace_ = CSpace(minimums, maximums);
      };

      /** \brief If files are specified for configuration 
      space and obstacles, load data from files */
      inline Roadmap(std::string filepath_configuration_space,
                     std::string filepath_obstacles)
      :G_(NULL) {
        cspace_.loadConfigurationSpace(filepath_configuration_space);
        cspace_.loadObstacles(filepath_obstacles);
      };

      ////////////////////////////////////////////////////////////////////////
      //                            INTERFACE
      ////////////////////////////////////////////////////////////////////////

      /** \brief Generate probabilistic roadmap. Based on [1] and [2].
      [1] L. E. Kavraki, P. Švestka, J. C. Latombe, and M. H. Overmars, 
      “Probabilistic roadmaps for path planning in high-dimensional 
      configuration spaces,” IEEE Trans. Robot. Autom., 1996.
      [2] L. E. Kavraki, M. N. Kolountzakis, and J. C. Latombe, 
      “Analysis of probabilistic roadmaps for path planning,” IEEE 
      Trans. Robot. Autom., vol. 14, no. 1, pp. 166–171, 1998. */
      void runPRM(int iterations, double radius, double step_size);

      /** \brief Generate quasi-random roadmap. Based on [1].
      [1] M. S. Branicky, S. M. Lavalle, K. Olson, and L. Yang, 
      “Quasi-Randomized Path Planning,” in IEEE International Conference on 
      Robotics and Automation, 2001, pp. 1481–1487. */
      void runQRM(int iterations, double radius, double step_size);

      /** \brief Generate lattice roadmap. Based on [1]. 
      [1] S. M. LaValle and M. S. Branicky, “On the relationship between 
      classical grid search and probabilistic roadmaps,” Int. J. Rob. Res., 
      vol. 23, no. 7–8, pp. 673–692, 2004.*/
      void runLRM(int iterations, double radius, double step_size);

      /** \brief Add a vertex to roadmap. */
      // void addVertex(std::vector<double> point);

      /** \brief ... */
      std::vector<int> computePath(const std::vector<double> & src, 
                                   const std::vector<double> & dst);

      ////////////////////////////////////////////////////////////////////////
      //                              MEMBERS
      ////////////////////////////////////////////////////////////////////////
      /** \brief The configuration space represented as a CSpace object */
      CSpace cspace_;

      /** \brief The graph representing the roadmap. The graph may weigted
      or unweighted and directed or undirected. The edge weights may be 
      positive or negative as long as no negative cycles exist. */
      Graph * G_;

      /** \brief Sampled configurations where each index corresponds to the
      graph indices. For example samples[i] corresponds to G_[i] */
      std::vector< std::vector<double> > samples_;

      ////////////////////////////////////////////////////////////////////////
      //                              GETTERS
      ////////////////////////////////////////////////////////////////////////
      /** \brief Return vector of points where each point representd as
      a vector */
      // std::vector< std::vector<double> > getVertices() const {return samples_;};

      /** \brief Return pointer to graph representing the roadmap */
      // const Graph * getGraphPtr() const {return G_;};

  private:
    /** \brief Constants representing the sample types for the roadmap */
      static const unsigned int UNIFORM    = 1;
      static const unsigned int HAMMERSLEY = 2;
      static const unsigned int LATTICE    = 4;

    /** \brief Generate roadmap based on sample_type where UNIFORM
    uses uniform sample sets, HAMMERSLEY uses Hammersley sample sets
    and LATTICE uses lattice sample sets. */
    void run(int    iterations, 
             double radius, 
             double step_size, 
             int    sample_type);

    /** \brief Samples n points from uniformly from configuration space
    defined by cspace_. */
    std::vector< std::vector<double> > sampleUniform(int n);

    /** \brief Sample Hammersley point set distributed in configuration
    space defined by cspace_. */
    //TODO: automate connection radius
    std::vector< std::vector<double> > sampleHammersley(int n);

    /** \brief Sample lattice point set distributed in configuration
    space defined by cspace_. */
    //TODO: automate connection radius
    std::vector< std::vector<double> > sampleLattice(int n);

    /** \brief Given points x and y, returns a point z that is "closer" to y 
    than x. In other words, returns a point z that minimizes ||z-y|| under 
    the constraint ||z-x|| <= radius for a specified radius. See [*]. Here, 
    a vector of configuration is computed with the last point in the vector 
    being z.*/
    bool steer(const std::vector<double>                & x,
               const std::vector<double>                & y,
                     double                               radius,
                     double                               step_size,
                     std::vector< std::vector<double> > & path) const;

    /** \brief  Return point that is between x and y that is step_size
    closer to y than x. */
    std::vector<double> step(const std::vector<double> & x,
                             const std::vector<double> & y,
                                   double                step_size) const;

};


}

#endif // Roadmap_HPP
