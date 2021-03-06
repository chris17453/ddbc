#include <Python.h>
/*****************************
 * Python 2.7 Extension
 *****************************/

static PyObject * spam_system(PyObject *self, PyObject *args){
    const char *command;
    int sts;

    if (!PyArg_ParseTuple(args, "s", &command))
        return NULL;
    sts = system(command);
    return Py_BuildValue("i", sts);
}