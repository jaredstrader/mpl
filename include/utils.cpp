// -*-c++-*-
//-----------------------------------------------------------------------------
/**
 * @file  utils.hpp
 *
 * <br>@b Author(s):    Jared Strader
 * <br>@b Date:         11/22/19
 */
//-----------------------------------------------------------------------------

#include<utils.hpp>

namespace utils
{
  bool isPrime(const int & n) {
      if (n <= 1) { 
        return false;
      } 

      for (int i = 2; i < n; i++) { 
          if (n % i == 0) {
            return false;
          }
      }

      return true;
  };

  std::vector<int> convertDecimalToBinary(int n) {
      std::vector<int> b;
      
      if(n==0) {
        b.push_back(0);
      }
      else {
        while(n > 0) {
            b.push_back(n % 2);
            n = n/2;
        }
      }
      return b;
  };

  double powd (const double & x, const int & y) {
      double temp;
      if (y == 0) {
        return 1;
      }
      
      temp = powd (x, y / 2);
      if ((y % 2) == 0) {
          return temp * temp;
      } 
      else {
        if (y > 0) {
          return x * temp * temp;
        }
        else {
          return (temp * temp) / x;
        }
      }
  };

  double dist(const std::vector<double> p1, const std::vector<double> p2) {
    if(p1.size() != p2.size()) 
    {
      std::cout << "Error! p1.size() != p2.size() for computing distance!\n";
      exit(1); //TODO: remove exit
    }

    double val=0;
    for(int i=0; i<p1.size(); i++) 
    {
      double diff = p1[i] - p2[i];
      val = val + diff*diff;
    }
    val = std::sqrt(val);
    return val;
  };

  double area_of_triangle(const std::pair<double, double> pt1,
                          const std::pair<double, double> pt2,
                          const std::pair<double, double> pt3) {
      double a = pt1.first;
      double b = pt2.first;
      double c = pt3.first;
      double d = pt1.second;
      double e = pt2.second;
      double f = pt3.second;
      double g = 1;
      double h = 1;
      double i = 1;
      double det = a*(e*i - f*h) - b*(d*i-g*f) + c*(d*h - e*g);
      if(det < 0) {
        det = -1*det;
      }
      return 0.5*det;
  };

  double angleDifference(double alpha, double beta) {
      alpha = alpha*180.0/3.14159265;
      beta = beta*180.0/3.14159265;
      double diff = fmod(( beta - alpha + 180 ), 360) - 180;
      double result = diff < -180 ? diff + 360 : diff;
      return result*3.14159265/180.0;
  };

  std::vector<double> diag(std::vector<double> vals) {
      std::vector<double> M;
      int incr=0;
      for(int i=0; i<vals.size(); i++) {
          for(int j=0; j<vals.size(); j++) {
              if(i==j) {
                  M.push_back(vals[incr]);
                  incr++;
              }
              else {
                  M.push_back(0);
              }
          }
      }
      return M;
  };

  //http://www.eecs.umich.edu/courses/eecs380/HANDOUTS/PROJ2/InsidePoly.html
  bool inPolygon(std::vector<double> p, std::vector< std::vector<double> > vertices) {
    int N = vertices.size();
    int counter = 0;
    int i;
    double xinters;

    std::vector<double> p1;
    std::vector<double> p2;

    p1 = vertices[0];
    for (i=1;i<=N;i++) {
      p2 = vertices[i % N];
      if (p[1] > std::min(p1[1],p2[1])) {
        if (p[1] <= std::max(p1[1],p2[1])) {
          if (p[0] <= std::max(p1[0],p2[0])) {
            if (p1[1] != p2[1]) {
              xinters = (p[1]-p1[1])*(p2[0]-p1[0])/(p2[1]-p1[1])+p1[0];
              if (p1[0] == p2[0] || p[0] <= xinters)
                counter++;
            }
          }
        }
      }
      p1 = p2;
    }

    if (counter % 2 == 0)
      return false;
    else
      return true;
  };

}