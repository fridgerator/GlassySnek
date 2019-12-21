#include <Python.h>

PyObject *pModule;

typedef struct {
  const char* name;
  const char* desc;
  float coef;
  float min;
  float max;
  float mean;
  float median;
  float std;
  float first;
  float third;
  float value;
} Stat_t;

typedef struct {
  Stat_t med_inc;
  Stat_t house_age;
  Stat_t ave_rooms;
  Stat_t ave_bedrms;
  Stat_t latitude;
  Stat_t longitude;
} Indep_variables_t;

typedef struct {
  float intercept;
  Indep_variables_t indep_variables;
  Stat_t dep_variable;
} Output_t;

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

Stat_t build_stat_t(PyObject *pVal)
{
  Stat_t stat;
  PyObject *keys = PyDict_Keys(pVal);
  Py_ssize_t size = PyList_GET_SIZE(keys);

  for (Py_ssize_t i = 0; i < size; i++) {
    PyObject *key = PyList_GetItem(keys, i);
    PyObject *val = PyDict_GetItem(pVal, key);

    const char *cKey = PyUnicode_AsUTF8(key);

    if (strncmp(cKey, "name", 4) == 0) {
      stat.name = PyUnicode_AsUTF8(val);
    } else if (strncmp(cKey, "desc", 4) == 0) {
      stat.desc = PyUnicode_AsUTF8(val);
    } else if (strncmp(cKey, "coef", 4) == 0) {
      stat.coef = PyFloat_AsDouble(val);
    } else if (strncmp(cKey, "min", 3) == 0) {
      stat.min = PyFloat_AsDouble(val);
    } else if (strncmp(cKey, "max", 3) == 0) {
      stat.max = PyFloat_AsDouble(val);
    } else if (strncmp(cKey, "mean", 4) == 0) {
      stat.mean = PyFloat_AsDouble(val);
    } else if (strncmp(cKey, "median", 6) == 0) {
      stat.median = PyFloat_AsDouble(val);
    } else if (strncmp(cKey, "std", 3) == 0) {
      stat.std = PyFloat_AsDouble(val);
    } else if (strncmp(cKey, "first", 4) == 0) {
      stat.first = PyFloat_AsDouble(val);
    } else if (strncmp(cKey, "third", 5) == 0) {
      stat.third = PyFloat_AsDouble(val);
    } else if (strncmp(cKey, "value", 5) == 0) {
      stat.value = PyFloat_AsDouble(val);
    }
  }

  return stat;
}

Output_t build_regression_model(void)
{
  char * fnName = "build_regression_model";
  PyObject *pFunc, *pArgs;
  pFunc = PyObject_GetAttrString(pModule, fnName);
  int callable = PyCallable_Check(pFunc);

  if (pFunc == NULL) fprintf(stderr, "pfunc is null\n");
  if (callable != 1) fprintf(stderr, "not callable\n");

  Output_t output;

  if (pFunc != NULL && callable == 1) {
    pArgs = PyTuple_New(0);
    PyObject *pValue;
    pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    
    // convert python dict to Output_t
    PyObject *keys = PyDict_Keys(pValue);
    Py_ssize_t size = PyList_GET_SIZE(keys);

    for (Py_ssize_t i = 0; i < size; i++) {
      PyObject *key = PyList_GetItem(keys, i);
      PyObject *val = PyDict_GetItem(pValue, key);

      const char *cKey = PyUnicode_AsUTF8(key);

      if (strncmp(cKey, "intercept", 9) == 0) {
        output.intercept = PyFloat_AsDouble(val);
      } else if (strncmp(cKey, "indepVariables", 14) == 0) {
        Indep_variables_t indep_variables;

        PyObject *idepvKeys = PyDict_Keys(val);
        Py_ssize_t ipdepvSize = PyList_GET_SIZE(idepvKeys);

        for (Py_ssize_t y = 0; y < ipdepvSize; y++) {
          PyObject *ipdepvKey = PyList_GetItem(idepvKeys, y);
          PyObject *idepvVal = PyDict_GetItem(val, ipdepvKey);

          const char *idepvcKey = PyUnicode_AsUTF8(ipdepvKey);

          if (strncmp(idepvcKey, "MedInc", 6) == 0) {
            indep_variables.med_inc = build_stat_t(idepvVal);
          } else if (strncmp(idepvcKey, "HouseAge", 8) == 0) {
            indep_variables.house_age = build_stat_t(idepvVal);
          } else if (strncmp(idepvcKey, "AveRooms", 8) == 0) {
            indep_variables.ave_rooms = build_stat_t(idepvVal);
          } else if (strncmp(idepvcKey, "AveBedrms", 9) == 0) {
            indep_variables.ave_bedrms = build_stat_t(idepvVal);
          } else if (strncmp(idepvcKey, "Latitude", 8) == 0) {
            indep_variables.latitude = build_stat_t(idepvVal);
          } else if (strncmp(idepvcKey, "Longitude", 9) == 0) {
            indep_variables.longitude = build_stat_t(idepvVal);
          }
        }

        output.indep_variables = indep_variables;
      } else if (strncmp(cKey, "depVariable", 11) == 0) {
        output.dep_variable = build_stat_t(val);
      }
    }

  } else {
    fprintf(stderr, "something broke\n");
    // call did not work, do some error code stuff
  }

  return output;
}
