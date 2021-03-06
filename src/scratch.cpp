#include <PyHelper.hpp>

CPyObject stlVectorToPythonList_Long(std::vector<int> input) {
    CPyObject pList, pVal;
    pList = PyList_New(input.size());

    for(int i=0; i<input.size(); i++) {
      pVal = PyLong_FromLong(input[i]);
      PyList_SetItem(pList, i, pVal);
    }

    pList.AddRef();
    return pList;
}

CPyObject stlVectorToPythonList_Double(std::vector<double> input) {
  CPyObject pList, pVal;
  pList = PyList_New(input.size());

  for(int i=0; i<input.size(); i++) {
    pVal = PyFloat_FromDouble(input[i]);
    PyList_SetItem(pList, i, pVal);
  }

  pList.AddRef();
  return pList;
}

int main( int argc, char** argv )
{
  CPyInstance cpy_instance_;

  std::vector<int> X = {0,1,2,3,4};
  std::vector<int> Y = {5,6,7,8,9};
  std::vector<int> index_i = {0,1,2,3,4};
  std::vector<int> index_j=  {4,3,2,1,0};

  CPyObject pName = PyString_FromString("MyModule");
  CPyObject pModule = PyImport_Import(pName);

  CPyObject pArgs = PyTuple_New(4);      

  CPyObject pObj;
  pObj = stlVectorToPythonList_Long(X);
  PyTuple_SetItem(pArgs, 0, pObj);
  pObj = stlVectorToPythonList_Long(Y);
  PyTuple_SetItem(pArgs, 1, pObj);
  pObj = stlVectorToPythonList_Long(index_i);
  PyTuple_SetItem(pArgs, 2, pObj);
  pObj = stlVectorToPythonList_Long(index_j);
  PyTuple_SetItem(pArgs, 3, pObj);

  if(pModule) {
    CPyObject pFunc = PyObject_GetAttrString(pModule, "MyFunction");
    if(pFunc && PyCallable_Check(pFunc)) {
      CPyObject pRetValue = PyObject_CallObject(pFunc, pArgs);
    }
    else {
      std::cout << "ERROR: Calling MyFunction()\n";
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
