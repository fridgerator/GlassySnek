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

  if (pModule == NULL) {
    fprintf(stderr, "Failed to load python module\n");
  }
}

int add(int a, int b) {
  char * fnName = "add";
  PyObject *pFunc, *pArgs;
  pFunc = PyObject_GetAttrString(pModule, fnName);
  int callable = PyCallable_Check(pFunc);

  if (pFunc == NULL) fprintf(stderr, "pfunc is null\n");
  if (callable != 1) fprintf(stderr, "not callable\n");

  if (pFunc != NULL && callable == 1) {
    pArgs = PyTuple_New(2);
    PyTuple_SetItem(pArgs, 0, PyLong_FromLong(a));
    PyTuple_SetItem(pArgs, 1, PyLong_FromLong(b));
    PyObject *pValue;
    pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    int v = PyLong_AsDouble(pValue);
    return v;
  } else {
    // call did not work, do some error code stuff
    return -1;
  }
}
