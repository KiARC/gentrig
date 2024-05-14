#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <math.h>
#include <numpy/arrayobject.h>
#include <corecrt_math_defines.h>

#define DEFINE_TRIG_FUNCTIONS(name, expr_sin, expr_cos)             \
    static PyObject *sin##name##_c(PyObject *dummy, PyObject *args) \
    {                                                               \
        double x;                                                   \
        if (!PyArg_ParseTuple(args, "d", &x))                       \
            return NULL;                                            \
        double res = expr_sin;                                      \
        return Py_BuildValue("d", res);                             \
    }                                                               \
    static PyObject *cos##name##_c(PyObject *dummy, PyObject *args) \
    {                                                               \
        double x;                                                   \
        if (!PyArg_ParseTuple(args, "d", &x))                       \
            return NULL;                                            \
        double res = expr_cos;                                      \
        return Py_BuildValue("d", res);                             \
    }                                                               \
    static PyObject *tan##name##_c(PyObject *dummy, PyObject *args) \
    {                                                               \
        double x;                                                   \
        if (!PyArg_ParseTuple(args, "d", &x))                       \
            return NULL;                                            \
        double res = (expr_sin) / (expr_cos);                       \
        return Py_BuildValue("d", res);                             \
    }                                                               \
    static PyObject *csc##name##_c(PyObject *dummy, PyObject *args) \
    {                                                               \
        double x;                                                   \
        if (!PyArg_ParseTuple(args, "d", &x))                       \
            return NULL;                                            \
        double res = 1.0 / (expr_sin);                              \
        return Py_BuildValue("d", res);                             \
    }                                                               \
    static PyObject *sec##name##_c(PyObject *dummy, PyObject *args) \
    {                                                               \
        double x;                                                   \
        if (!PyArg_ParseTuple(args, "d", &x))                       \
            return NULL;                                            \
        double res = 1.0 / (expr_cos);                              \
        return Py_BuildValue("d", res);                             \
    }                                                               \
    static PyObject *cot##name##_c(PyObject *dummy, PyObject *args) \
    {                                                               \
        double x;                                                   \
        if (!PyArg_ParseTuple(args, "d", &x))                       \
            return NULL;                                            \
        double res = (expr_cos) / (expr_sin);                       \
        return Py_BuildValue("d", res);                             \
    }

DEFINE_TRIG_FUNCTIONS(p, pow(cbrt(3.0 * x), 2.0), cbrt(3.0 * x))

DEFINE_TRIG_FUNCTIONS(l, x, 1.0)

/*
Polygonal Trig is a special case from the macro in
that it includes asecond argument for number of sides
*/
#define sec(x) (1.0 / cos(x))
#define cot(x) (1.0 / tan(x))

#define calc_k_p                                       \
    double k = floor((x / 2.0) * cot(M_PI / n) + 0.5); \
    double p = ((x / 2.0) * cot(M_PI / n) + 0.5) - floor((x / 2.0) * cot(M_PI / n) + 0.5);

#define expr_sinpoly sec(M_PI / n) * (sin((M_PI / n) * (2 * k - 1)) * (1 - p) + sin((M_PI / n) * (2 * k + 1)) * p)
#define expr_cospoly sec(M_PI / n) * (cos((M_PI / n) * (2 * k - 1)) * (1 - p) + cos((M_PI / n) * (2 * k + 1)) * p)

static PyObject *sinpoly_c(PyObject *dummy, PyObject *args)
{
    double x;
    double n;
    if (!PyArg_ParseTuple(args, "dd", &x, &n))
        return NULL;
    calc_k_p;
    double res = expr_sinpoly;
    return Py_BuildValue("d", res);
}
static PyObject *cospoly_c(PyObject *dummy, PyObject *args)
{
    double x;
    double n;
    if (!PyArg_ParseTuple(args, "dd", &x, &n))
        return NULL;
    calc_k_p;
    double res = expr_cospoly;
    return Py_BuildValue("d", res);
}
static PyObject *tanpoly_c(PyObject *dummy, PyObject *args)
{
    double x;
    double n;
    if (!PyArg_ParseTuple(args, "dd", &x, &n))
        return NULL;
    calc_k_p;
    double res = (expr_sinpoly) / (expr_cospoly);
    return Py_BuildValue("d", res);
}
static PyObject *cscpoly_c(PyObject *dummy, PyObject *args)
{
    double x;
    double n;
    if (!PyArg_ParseTuple(args, "dd", &x, &n))
        return NULL;
    calc_k_p;
    double res = 1 / (expr_sinpoly);
    return Py_BuildValue("d", res);
}
static PyObject *secpoly_c(PyObject *dummy, PyObject *args)
{
    double x;
    double n;
    if (!PyArg_ParseTuple(args, "dd", &x, &n))
        return NULL;
    calc_k_p;
    double res = 1 / (expr_cospoly);
    return Py_BuildValue("d", res);
}
static PyObject *cotpoly_c(PyObject *dummy, PyObject *args)
{
    double x;
    double n;
    if (!PyArg_ParseTuple(args, "dd", &x, &n))
        return NULL;
    calc_k_p;
    double res = (expr_cospoly) / (expr_sinpoly);
    return Py_BuildValue("d", res);
}

static PyMethodDef GentrigMethods[] = {
    {"sinp", sinp_c,
     METH_VARARGS,
     "Parabolic sine function"},
    {"cosp", cosp_c,
     METH_VARARGS,
     "Parabolic cosine function"},
    {"tanp", tanp_c,
     METH_VARARGS,
     "Parabolic tangent function"},
    {"cscp", cscp_c,
     METH_VARARGS,
     "Parabolic cosecant function"},
    {"secp", secp_c,
     METH_VARARGS,
     "Parabolic secant function"},
    {"cotp", cotp_c,
     METH_VARARGS,
     "Parabolic cotangent function"},
    {"sinl", sinl_c,
     METH_VARARGS,
     "Linear sine function"},
    {"cosl", cosl_c,
     METH_VARARGS,
     "Linear cosine function"},
    {"tanl", tanl_c,
     METH_VARARGS,
     "Linear tangent function"},
    {"cscl", cscl_c,
     METH_VARARGS,
     "Linear cosecant function"},
    {"secl", secl_c,
     METH_VARARGS,
     "Linear secant function"},
    {"cotl", cotl_c,
     METH_VARARGS,
     "Linear cotangent function"},
    {"sinpoly", sinpoly_c,
     METH_VARARGS,
     "Polygonal sine function"},
    {"cospoly", cospoly_c,
     METH_VARARGS,
     "Polygonal cosine function"},
    {"tanpoly", tanpoly_c,
     METH_VARARGS,
     "Polygonal tangent function"},
    {"cscpoly", cscpoly_c,
     METH_VARARGS,
     "Polygonal cosecant function"},
    {"secpoly", secpoly_c,
     METH_VARARGS,
     "Polygonal secant function"},
    {"cotpoly", cotpoly_c,
     METH_VARARGS,
     "Polygonal cotangent function"},
    {NULL, NULL, 0, NULL} /* Sentinel */
};

static struct PyModuleDef gentrig_module_def = {
    PyModuleDef_HEAD_INIT,
    "_gentrig",
    "Internal \"_gentrig\" module",
    -1,
    GentrigMethods};

PyMODINIT_FUNC PyInit_gentrig(void)
{
    return PyModule_Create(&gentrig_module_def);
}