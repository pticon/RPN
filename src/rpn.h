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
	RPN_INVALID_OPERATOR,
};

extern int
infinite;

const char *
rpn_geterr(enum rpn_code err);

int
rpn_input(char *buf, int size);


#include "list.h"
#include "arithmetic.h"
#include "array.h"
#include "elt.h"
#include "float.h"
#include "integer.h"
#include "operator.h"
#include "stack.h"
#include "string.h"


/* Lex stuffs
 */
#define ECHO

int yylex(struct list_head *stack);
#define YY_DECL int yylex(struct list_head *stack)

#define YY_NO_INPUT
#define YY_NO_UNPUT

#define YY_INPUT(buf, result, max_size)	(result = rpn_input(buf, max_size))


#endif /* __RPN_H__ */
