#include <Python.h>
#include <structmember.h>
#include <stdio.h>
#include "kraken_api.h"

typedef struct {
	/* makro that brings in the standard python object fields */	
	PyObject_HEAD
	/* Type-specific fields go here. */

	struct kraken_api *kr_api;

} kr_public;

static int kr_public_traverse(kr_private *self, visitproc visit, void *arg){

	Py_VISIT(self->kr_api);

	return 0;
}

/* 
module = PyImport_ImportModule("testPython");
*/

static void kr_public_dealloc(kr_private* self){

	printf("dealloc called\n");
	kraken_clean(&(self->kr_api));
	Py_TYPE(self)->tp_free((PyObject*)self);
}
static PyObject *kr_public_new(PyTypeObject *type, PyObject *args, PyObject *kwds){
	/* use this function to initialize variabled */
	printf("Kraken new executed\n");
	kr_public *self;
	self = (kr_public *)type->tp_alloc(type, 0);

	return (PyObject *)self;
}


/* pass api- and secret-key durin initialization */
static int kr_public_init(kr_private *self, PyObject *args, PyObject *kwds){

	printf("public init executed\n");

	const char *api_key = "";
        const char *sec_key = "";

	if(!PyArg_ParseTuple(args, "ss", &api_key, &sec_key))
		       return -1;

	printf("api-key: %s\n", api_key);
	printf("sec-key: %s\n", sec_key);

	printf("calling kraken_init\n");
	
	kraken_init(&(self->kr_api), api_key, sec_key);

	printf("key in kraken struct: %s\n", self->kr_api->s_api_key);

	printf("kraken_init called\n");
	return 0;
}



static PyMemberDef kr_public_members[] = {
	{NULL} /* Sentinel */
};


static PyGetSetDef kr_public_getseters[] = {

	{NULL}
};



static PyObject *kr_public_set_opt(kr_private* self, PyObject* args){


	char *py_option = NULL, *py_value = NULL;

	if (!PyArg_ParseTuple(args, "ss", &py_option, &py_value))
		return NULL;

#if 0
	if(!(PyUnicode_Check(py_option))){
		PyErr_SetString(PyExc_TypeError, "\"Option\" must be a string object");
		return -1;
	}
	if(!(PyUnicode_Check(py_value))){
		PyErr_SetString(PyExc_TypeError, "\"Value\" must be a string object");
		return -1;
	}
#endif

	kraken_set_opt(&(self->kr_api), py_option, py_value);
	/* there are no void functions in Python, 
	* macro "Py_RETURN_NONE" necessary */
	Py_RETURN_NONE ;	
}






static PyObject *kr_public_result(kr_private *self){

	return PyUnicode_FromString(self->kr_api->s_result);
}

static PyMethodDef kr_public_methods[] = {
	{"set_opt", (PyCFunction)kr_public_set_opt, METH_VARARGS, "Set optionals for the API calls"},
	{"result", (PyCFunction)kr_public_result, METH_VARARGS, "Return the result of an API call"},
	{NULL}	/* Sentinel */
};



static PyTypeObject kr_public_Type = {

	PyVarObject_HEAD_INIT(NULL, 0)
	"kr_public.Kr_private",   /* tp_name */
	sizeof(kr_public),	   /* tp_basicsize */
	0,                         /* tp_itemsize */
	(destructor)kr_public_dealloc,   /* tp_dealloc */
	0,                         /* tp_print */
	0,                         /* tp_getattr */
	0,                         /* tp_setattr */
	0,                         /* tp_reserved */
	0,                         /* tp_repr */
	0,                         /* tp_as_number */
	0,                         /* tp_as_sequence */
	0,                         /* tp_as_mapping */
	0,                         /* tp_hash  */
	0,                         /* tp_call */
	0,                         /* tp_str */
	0,                         /* tp_getattro */
	0,                         /* tp_setattro */
	0,                         /* tp_as_buffer */
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,        /* tp_flags */
	"public objects",           /* tp_doc */
	(traverseproc)kr_public_traverse,
	0,
	0,
	0,
	0,
	0,
	kr_public_methods,
	kr_public_members,
	kr_public_getseters,
	0,
	0,
	0,
	0,
	0,
	(initproc)kr_public_init,
	0,
	kr_public_new,
};

static PyModuleDef kr_publicmodule = {
	PyModuleDef_HEAD_INIT,
	"kr_public",
	"Module that inherits public API functions.",
	-1,
	NULL, NULL, NULL, NULL, NULL
};

PyMODINIT_FUNC PyInit_kr_public(void){

	printf("PyInit_kr_public called\n");

	PyObject* m;

	if (PyType_Ready(&kr_public_Type) < 0)
		return NULL;

	m = PyModule_Create(&kr_publicmodule);
	if (m == NULL)
		return NULL;

	Py_INCREF(&kr_public_Type);
	PyModule_AddObject(m, "kr_public", (PyObject *)&kr_public_Type);

	return m;
}
