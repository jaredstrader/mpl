//MINIMUM WORKING EXAMPLE AXIS TICKS
#include <matplot/matplot.h>
#include <set>

int main( int argc, char** argv )
{
  // std::vector<std::pair<size_t,size_t>> edges = {{0,1},{0,2},{0,3},{1,2},{1,3},{2,3}};
  // std::vector<double> x_data = { 0.2, -0.1, 1.1, 1.3};
  // std::vector<double> y_data = {-0.1,  0.8, 0.3, 1.2};

  // auto g = matplot::graph(edges);
  // g->show_labels(false);
  // g->x_data(x_data);
  // g->y_data(y_data);

  // matplot::axis(matplot::square);
  // matplot::xlabel("X");
  // matplot::ylabel("Y");
  // matplot::show();

  std::vector<double> X = {0,1,std::nan(""),0,0};
  std::vector<double> Y = {0,1,std::nan(""),1,0};
  matplot::plot(X,Y);
  matplot::axis(matplot::square);
  matplot::xlabel("X");
  matplot::ylabel("Y");
  matplot::show();

  return 0;
}
