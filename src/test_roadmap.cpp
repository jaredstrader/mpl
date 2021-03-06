// -*-c++-*-
//-----------------------------------------------------------------------------
/**
 * @file  test_roadmap.cpp
 *
 * <br>@b Author(s):    Jared Strader
 * <br>@b Date:         9/5/20
 *
 */
//-----------------------------------------------------------------------------

#include <Roadmap.hpp>

CPyObject stlVectorToPythonList_Long(std::vector<int> input) {
    CPyObject pList, pVal;
    pList = PyList_New(input.size());

    for(int i=0; i<input.size(); i++) {
      pVal = PyLong_FromLong(input[i]);
      PyList_SetItem(pList, i, pVal);
    }

    return pList;
}

//convert vector to list 
CPyObject stlVectorToPythonList_Double(std::vector<double> input) {
  CPyObject pList, pVal;
  pList = PyList_New(input.size());

  for(int i=0; i<input.size(); i++) {
    pVal = PyFloat_FromDouble(input[i]);
    PyList_SetItem(pList, i, pVal);
  }

  return pList;
}

int main( int argc, char** argv )
{
  std::cout << "Running test_world..." << std::endl;

  // std::cout << "\n******************Test Roadmap (mins, maxs)******************\n";
  // std::vector<double> mins = {-5, -10};
  // std::vector<double> maxs = { 5,  10};
  // mpl::Roadmap roadmap1(mins, maxs);

  // std::cout << "\n******************Test Roadmap GUI******************\n";
  // // mpl::Roadmap roadmap2;

  // std::cout << "\n******************Test Roadmap Load******************\n";
  // // mpl::Roadmap roadmap3("configuration_space.txt","obstacles.txt");

  // std::cout << "\n******************Test Roadmap Run******************\n";
  // roadmap1.runPRM(200, 1.2, 0.1);
  // roadmap1.getPath({0,0},{5,5});

  CPyInstance cpy_instance_;

  std::cout << "1" << std::endl;

  std::vector<double> X = {1,2,3,4,5,6,7,8,9,10};
  std::vector<double> Y = {11,12,13,14,15,16,17,18,19,20};
  std::vector<int> index_i = {1,2,3,4,5,6,7,8,9,10};
  std::vector<int> index_j= {11,12,13,14,15,16,17,18,19,20};

  for(int i=0; i<X.size(); i++) {
    std::cout << "x, y = " << X[i] << ", " << Y[i] << std::endl;
  }

  CPyObject pName = PyString_FromString("PlotterHelper");
  CPyObject pModule = PyImport_Import(pName);

  CPyObject pArgs = PyTuple_New(4);      

  std::cout << "2" << std::endl;

  CPyObject pX = stlVectorToPythonList_Double(X); //X is std::vector<double>
  CPyObject pY = stlVectorToPythonList_Double(Y); //Y is std::vector<double>
  CPyObject pi = stlVectorToPythonList_Long(index_i); //i is std::vector<int>
  CPyObject pj = stlVectorToPythonList_Long(index_j); //j is std::vector<int>

  std::cout << "3" << std::endl;

  PyTuple_SetItem(pArgs, 0, pX);
  PyTuple_SetItem(pArgs, 1, pY);
  PyTuple_SetItem(pArgs, 2, pi);
  PyTuple_SetItem(pArgs, 3, pj);

  std::cout << "4" << std::endl;

  if(pModule) {
    CPyObject pFunc = PyObject_GetAttrString(pModule, "plotRoadmap");
    if(pFunc && PyCallable_Check(pFunc)) {
      CPyObject pRetValue = PyObject_CallObject(pFunc, pArgs);
    }
    else {
      std::cout << "ERROR: Calling plotRoadmap()\n";
      return 0;
    }
    }
    else {
    std::cout << "ERROR: Module not imported" << std::endl;
    return 0;
  }


  std::cout << "Terminating..." << std::endl;
  return 0;
}
