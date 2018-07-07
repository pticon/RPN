#ifndef __RPN_H__
#define __RPN_H__


#define PROGNAME		"rpn"
#define VERSION			"1.0"


enum rpn_code
{
	RPN_OK = 0,
	RPN_STACK_EMPTY,
	RPN_NOT_SAME_TYPE,
	RPN_MEMORY,
	RPN_NOT_SUPPORTED,
};

extern int
infinite;

const char *
rpn_geterr(enum rpn_code err);


#include "list.h"
#include "arithmetic.h"
#include "array.h"
#include "elt.h"
#include "float.h"
#include "integer.h"
#include "operator.h"
#include "stack.h"
#include "string.h"

#endif /* __RPN_H__ */
