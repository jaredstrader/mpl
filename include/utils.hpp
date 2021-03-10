// -*-c++-*-
//-----------------------------------------------------------------------------
/**
 * @file  utils.hpp
 *
 * <br>@b Author(s):    Jared Strader
 * <br>@b Date:         11/22/19
 */
//-----------------------------------------------------------------------------

#ifndef Utils_HPP
#define Utils_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <assert.h>

namespace utils
{
  /** \brief Compute if integer is prime or not prime */
  bool isPrime(const int & n);

  /** \brief Compute binary representation of decimel number.*/
  //TODO: check if e.g. convertDecimalToBinary(10) = [1,0,1,0]
  //      or if e.g. convertDecimalToBinary(10) = [0,1,0,1] and
  //      add to brief
  std::vector<int> convertDecimalToBinary(int n);

  /** \brief Compute x^y where the inputs and outputs are doubles */
  double powd(const double & x, const int & y);

  /** \brief Compute Euclidean distance between a pair of points */
  double dist(const std::vector<double> p1, const std::vector<double> p2);

  /** \brief Compute area of a triangle using the shoelace formula */
  double area_of_triangle(const std::pair<double, double> pt1,
                          const std::pair<double, double> pt2,
                          const std::pair<double, double> pt3);

  /** \brief  Compute the difference between angles in radians where the 
  difference (i.e., beta - alpha) is given between -180 and 180 */
  double angleDifference(double alpha, double beta);

  /** \brief  Return diagonal matrix using elements of vector as diagonal 
  entries where matrix(3*i + j) is the element of the ith row and jth column*/
  std::vector<double> diag(std::vector<double> vals);

  /** \brief  Return true if 2D point is inside polygon represented by 
  vertices where vertices[i] = [x, y] */
  bool inPolygon(std::vector<double> point, std::vector< std::vector<double> > vertices);
}

#endif // Utils_HPP