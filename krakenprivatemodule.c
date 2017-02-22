#include <Python.h>
#include <structmember.h>
#include <stdio.h>
#include "kraken_api.h"

typedef struct {
	/* makro that brings in the standard python object fields */	
	PyObject_HEAD
	/* Type-specific fields go here. */

	struct kraken_api *kr_api;

} kr_private;

static int kr_private_traverse(kr_private *self, visitproc visit, void *arg){

	Py_VISIT(self->kr_api);

	return 0;
}

/* 
module = PyImport_ImportModule("testPython");
*/

static void kr_private_dealloc(kr_private* self){

	printf("dealloc called\n");
	kraken_clean(&(self->kr_api));
	Py_TYPE(self)->tp_free((PyObject*)self);
}
static PyObject *kr_private_new(PyTypeObject *type, PyObject *args, PyObject *kwds){
	/* use this function to initialize variabled */
	printf("Kraken new executed\n");
	kr_private *self;
	self = (kr_private *)type->tp_alloc(type, 0);

	return (PyObject *)self;
}


/* pass api- and secret-key durin initialization */
static int kr_private_init(kr_private *self, PyObject *args, PyObject *kwds){

	printf("private init executed\n");

	const char *api_key = NULL;
        const char *sec_key = NULL;

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



static PyMemberDef kr_private_members[] = {
	{NULL} /* Sentinel */
};


static PyGetSetDef kr_private_getseters[] = {

	{NULL}
};



static PyObject *kr_private_set_opt(kr_private* self, PyObject* args){


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





static PyObject *kr_private_add_order(kr_private *self, PyObject *args){

	char* type	= NULL;
	char* ordertype = NULL; 
	char* asset	= NULL;
	char* volume	= NULL;
	char* arg_1	= NULL;
	char* arg_2	= NULL;

	if (!PyArg_ParseTuple(args, "ssss|ss", &type, &ordertype, &asset, &volume, &arg_1, &arg_2))
		return NULL;

	printf("calling add_order from python\n");

	self->kr_api->priv_func->add_order(&(self->kr_api), "buy", "stop-loss-profit", "XXBTZEUR", "0.43", "0.2", "0.1");
	printf("add_order called\n");
	Py_RETURN_NONE ;
}

static PyObject *kr_private_cancel_order(kr_private *self, PyObject *args){

	char* order_id = NULL;

	if (!PyArg_ParseTuple(args, "s", &order_id))
		return NULL;

	self->kr_api->priv_func->cancel_order(&(self->kr_api), order_id);

	Py_RETURN_NONE;
}

static PyObject *kr_private_account_balance(kr_private *self){

	self->kr_api->priv_func->get_account_balance(&(self->kr_api));

	Py_RETURN_NONE ;
}

static PyObject *kr_private_trade_balance(kr_private *self){

	self->kr_api->priv_func->get_trade_balance(&(self->kr_api));

	Py_RETURN_NONE ;
}

static PyObject *kr_private_open_orders(kr_private *self){

	self->kr_api->priv_func->get_open_orders(&(self->kr_api));

	Py_RETURN_NONE ;
}

static PyObject *kr_private_closed_orders(kr_private *self){

	self->kr_api->priv_func->get_closed_orders(&(self->kr_api));

	Py_RETURN_NONE ;
}

static PyObject *kr_private_query_order_info(kr_private *self, PyObject *args){

	char* order_id = NULL;

	if (!PyArg_ParseTuple(args, "s", &order_id))
		return NULL;

	self->kr_api->priv_func->query_order_info(&(self->kr_api), order_id);

	Py_RETURN_NONE ;
}

static PyObject *kr_private_get_trade_history(kr_private *self){

	self->kr_api->priv_func->get_trades_history(&(self->kr_api));

	Py_RETURN_NONE ;
}

static PyObject *kr_private_query_trades_info(kr_private *self, PyObject *args){

	char* order_id = NULL;

	if (!PyArg_ParseTuple(args, "s", &order_id))
		return NULL;

	self->kr_api->priv_func->query_trades_info(&(self->kr_api), order_id);

	Py_RETURN_NONE ;
}

static PyObject *kr_private_get_open_positions(kr_private *self, PyObject *args){

	char* order_id = NULL;

	if (!PyArg_ParseTuple(args, "s", &order_id))
		return NULL;

	self->kr_api->priv_func->get_open_positions(&(self->kr_api), order_id);

	Py_RETURN_NONE ;
}

static PyObject *kr_private_get_ledgers_info(kr_private *self){

	self->kr_api->priv_func->get_ledgers_info(&(self->kr_api));

	Py_RETURN_NONE ;
}

static PyObject *kr_private_query_ledgers(kr_private *self, PyObject *args){

	char* order_id = NULL;

	if (!PyArg_ParseTuple(args, "s", &order_id))
		return NULL;

	self->kr_api->priv_func->query_ledgers(&(self->kr_api), order_id);

	Py_RETURN_NONE ;
}

static PyObject *kr_private_get_trade_volume(kr_private *self){

	self->kr_api->priv_func->get_trade_volume(&(self->kr_api));

	Py_RETURN_NONE ;
}

static PyObject *kr_public_server_time(kr_private *self){

	self->kr_api->pub_func->get_server_time(&(self->kr_api));

	Py_RETURN_NONE ;
}

static PyObject *kr_private_result(kr_private *self){

	return PyUnicode_FromString(self->kr_api->s_result);
}

static PyObject *kr_public_asset_info(kr_private *self){

	self->kr_api->pub_func->get_asset_info(&(self->kr_api));

	Py_RETURN_NONE ;
}

static PyObject *kr_public_get_tradeable_asset_pairs(kr_private *self){

	/* spelling mistake */
	self->kr_api->pub_func->get_tradable_asset_pairs(&(self->kr_api));

	Py_RETURN_NONE ;
}

static PyObject *kr_public_get_ticker_info(kr_private *self, PyObject *args){

	char* asset_pairs = NULL;

	if (!PyArg_ParseTuple(args, "s", &asset_pairs))
		return NULL;

	self->kr_api->pub_func->get_ticker_info(&(self->kr_api), asset_pairs);

	Py_RETURN_NONE ;
}

static PyObject *kr_public_get_ohlc_data(kr_private *self, PyObject *args){

	char* asset_pairs = NULL;

	if (!PyArg_ParseTuple(args, "s", &asset_pairs))
		return NULL;

	self->kr_api->pub_func->get_ohlc_data(&(self->kr_api), asset_pairs);

	Py_RETURN_NONE ;
}

static PyMethodDef kr_private_methods[] = {
	{"set_opt", (PyCFunction)kr_private_set_opt, METH_VARARGS, "Set optionals for the API calls"},
	{"add_order", (PyCFunction)kr_private_add_order, METH_VARARGS, "Execute an order"},
	{"cancel_order", (PyCFunction)kr_private_cancel_order, METH_VARARGS, "Cancel an order (by order-ID)"},
	{"account_balance", (PyCFunction)kr_private_account_balance, METH_NOARGS, "Query the account balance"},
	{"trade_balance", (PyCFunction)kr_private_trade_balance, METH_NOARGS, "Query the trade balance"},
	{"result", (PyCFunction)kr_private_result, METH_VARARGS, "Return the result of an API call"},
	{"open_orders", (PyCFunction)kr_private_open_orders, METH_VARARGS, "Get a list of open orders"},
	{"closed_orders", (PyCFunction)kr_private_closed_orders, METH_VARARGS, "Get a list of closed orders"},
	{"query_order_info", (PyCFunction)kr_private_query_order_info, METH_VARARGS, "Query order information"},
	{"get_trades_history", (PyCFunction)kr_private_get_trade_history, METH_VARARGS, "Get the trades history"},
	{"query_trades_info", (PyCFunction)kr_private_query_trades_info, METH_VARARGS, "Query trades information"},
	{"get_open_positions", (PyCFunction)kr_private_get_open_positions, METH_VARARGS, "Get a list of open positions"},
	{"get_ledgers_info", (PyCFunction)kr_private_get_ledgers_info, METH_VARARGS, "Get ledger information"},
	{"query_ledgers", (PyCFunction)kr_private_query_ledgers, METH_VARARGS, "Query ledger information"},
	{"get_trade_volume", (PyCFunction)kr_private_get_trade_volume, METH_VARARGS, "Get the trades volume"},
	{"get_server_time", (PyCFunction)kr_public_server_time, METH_VARARGS, "Get the current server time"},
	{"get_asset_info", (PyCFunction)kr_public_asset_info, METH_VARARGS, "Get the current server time"},
	{"get_tradeable_asset_pairs", (PyCFunction)kr_public_get_tradeable_asset_pairs, METH_VARARGS, "Get tradeable asset pairs"},
	{"get_ticker_info", (PyCFunction)kr_public_get_ticker_info, METH_VARARGS, "Get ticker information"},
	{"get_ohlc_data", (PyCFunction)kr_public_get_ohlc_data, METH_VARARGS, "Get OHLC data"},
	{NULL}	/* Sentinel */
};



static PyTypeObject kr_private_Type = {

	PyVarObject_HEAD_INIT(NULL, 0)
	"kr_private.Kr_private",   /* tp_name */
	sizeof(kr_private),	   /* tp_basicsize */
	0,                         /* tp_itemsize */
	(destructor)kr_private_dealloc,   /* tp_dealloc */
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
	"private objects",           /* tp_doc */
	(traverseproc)kr_private_traverse,
	0,
	0,
	0,
	0,
	0,
	kr_private_methods,
	kr_private_members,
	kr_private_getseters,
	0,
	0,
	0,
	0,
	0,
	(initproc)kr_private_init,
	0,
	kr_private_new,
};

static PyModuleDef kr_privatemodule = {
	PyModuleDef_HEAD_INIT,
	"kr_private",
	"Module that inherits private API functions.",
	-1,
	NULL, NULL, NULL, NULL, NULL
};

PyMODINIT_FUNC PyInit_kr_private(void){

	printf("PyInit_kr_private called\n");

	PyObject* m;

	if (PyType_Ready(&kr_private_Type) < 0)
		return NULL;

	m = PyModule_Create(&kr_privatemodule);
	if (m == NULL)
		return NULL;

	Py_INCREF(&kr_private_Type);
	PyModule_AddObject(m, "kr_private", (PyObject *)&kr_private_Type);

	return m;
}
