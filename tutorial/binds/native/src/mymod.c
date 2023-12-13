#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <mymod.h>

PyObject *my_sqr_func_bind(PyObject *self, PyObject *args)
{
    if (PyTuple_Size(args) != 1) {
        PyErr_SetString(self, "my_sqr_func must have only one arg");
    }

    PyObject *obj = PyTuple_GetItem(args, 0);
    if (PyFloat_Check(obj)) {
        PyErr_Print();
    }

    double val = PyFloat_AsDouble(obj);
    val = my_sqr_func(val);
    return Py_BuildValue("d", val);
}

static PyMethodDef methods[] = {
    {"my_sqr_func", my_sqr_func_bind, METH_VARARGS, "Function to sqr any float value"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef mymod = {
    PyModuleDef_HEAD_INIT,
    .m_name  = "mymod",
    .m_doc = "Test module",
    .m_size = -1,
    .m_methods = methods,
};

PyMODINIT_FUNC
PyInit_mymod(void) {
    PyObject *mod = PyModule_Create(&mymod);
    return mod;
}