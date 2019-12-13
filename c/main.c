#include <Python.h>

PyObject *pModule;

void startInterpreter () {
  int isInitialized = Py_IsInitialized();
  if (isInitialized == 0)
    Py_Initialize();

  int threadsInitialized = PyEval_ThreadsInitialized();
  if (threadsInitialized == 0)
    PyEval_InitThreads();
}

void appendSysPath (char* path) {
  char *appendPathStr;
  size_t len = (size_t)snprintf(NULL, 0, "import sys;sys.path.append(r\"%s\")", path);
  appendPathStr = (char *)malloc(len + 1);
  snprintf(appendPathStr, len + 1, "import sys;sys.path.append(r\"%s\")", path);

  PyRun_SimpleString(appendPathStr);
  free(appendPathStr);
}

void openFile (char* fileName) {
  PyObject *pName;
  pName = PyUnicode_DecodeFSDefault(fileName);
  pModule = PyImport_Import(pName);
  Py_DECREF(pName);
}

int add(int a, int b) {
  char * fnName = "add";
  PyObject *pFunc, *pArgs;
  pFunc = PyObject_GetAttrString(pModule, fnName);
  int callable = PyCallable_Check(pFunc);

  if (pFunc != NULL && callable == 1) {
    PyObject *pArgs = PyTuple_New(2);
    // PyTuple_SetItem()
  } else {
    // broke
  }
}
