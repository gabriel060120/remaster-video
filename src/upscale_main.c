#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <stdlib.h>
#include <string.h>

void call_from_python(PyObject *module, const char *restrict funcname, char *restrict infname, char *restrict outfname)
{
    PyGILState_STATE state = PyGILState_Ensure();

    PyObject* fn     = PyObject_GetAttrString(module, funcname);
    PyObject* args   = Py_BuildValue("(ss)", infname, outfname);
    PyObject *result = PyObject_CallObject(fn, args);
    Py_DECREF(args);

    if (!PyCallable_Check(fn)) {
        fprintf(stderr, "%s: função esperada\n", __func__);
        goto ERROR_CLEANUP;
    }

    if (PyErr_Occurred()) {
        PyErr_Print();
        goto ERROR_CLEANUP;
    }

    if (!PyUnicode_Check(result)) {
        fprintf(stderr, "%s: string esperada\n", __func__);
        goto ERROR_CLEANUP;
    }

    PyObject *bytes = PyUnicode_AsEncodedString(result, "UTF-8", "strict");
    if (!bytes) {
        PyErr_Print();
        goto ERROR_CLEANUP;
    }
    char *res = PyBytes_AS_STRING(bytes);
    res = strdup(res);

    assert(!strcmp(res, "MOCK"));
    Py_DECREF(result);

    PyGILState_Release(state);
    free(res);

ERROR_CLEANUP:
    Py_XDECREF(result);
    PyGILState_Release(state);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <in-filename> <out-filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    setenv("PYTHONPATH", ".", 1);
    Py_Initialize();

    PyObject *modulename = PyUnicode_FromString((char *) "mock-module.mock_upscale");
    PyObject *module     = PyImport_Import(modulename);
    Py_DECREF(modulename);
    if (!module) {
        fprintf(stderr, "%s: módulo não encontrado\n", __func__);
        return EXIT_FAILURE;
    }

    call_from_python(module, "upscale", "/ex/emp/lo", "nome");

    Py_Finalize();
    return EXIT_SUCCESS;
}
