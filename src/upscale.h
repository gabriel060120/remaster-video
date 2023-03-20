#ifndef UPSCALE_H_
#define UPSCALE_H_ 1

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject *python_initialize(const char *modulestr);
void python_finalize(void);
void call_from_python(PyObject *module,
                      const char *funcname,
                      const char *infname,
                      const char *outfname);

#ifdef __cplusplus
}
#endif

#endif
