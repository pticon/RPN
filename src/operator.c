#include <stdio.h>
#include <string.h>

#include "rpn.h"


static enum rpn_code
operator_print(struct list_head *stack);

static enum rpn_code
quit(struct list_head *stack);

static struct operator	operators [] =
{
	{"abs",		0,	func_absolute,		"absolute value"},
	{"add",		'+',	func_addition,		"addition"},
	{"deep",	0,	stack_depth,		"stack depth"},
	{"div",		'/',	func_division,		"division"},
	{"drop",	0,	stack_drop,		"drop the last element on the stack"},
	{"dup",		'd',	stack_duplicate,	"duplicate the last element on the stack"},
	{"flush",	'f',	stack_free,		"flush the stack"},
	{"help",	'h',	operator_print,		"print operators"},
	{"inc",		0,	func_incrementation,	"incremente the last element"},
	{"++",		0,	func_incrementation,	"incremente the last element"},
	{"mul",		'*',	func_multiplication,	"multiplication"},
	{NULL,		'x',	func_multiplication,	"multiplication"},
	{NULL,		'.',	func_multiplication,	"multiplication"},
	{"pow",		'^',	func_power,		"power"},
	{"print",	'p',	stack_print,		"print stack"},
	{"quit",	'q',	quit,			"quit " PROGNAME},
	{"sub",		'-',	func_substraction,	"substraction"},
	{"swap",	's',	stack_swap,		"swap the last 2 element on the stack"},
};

#define FOREACH_OPERATOR(_i, _op)	\
	for( _i = 0, _op = &operators[0] ; \
		_i < ARRAY_SIZE(operators) ; \
		_i++, _op = &operators[_i] )

static enum rpn_code
quit(struct list_head *stack)
{
	infinite = 0;

	return RPN_OK;
}


static enum rpn_code
operator_print(struct list_head *stack)
{
	int			i;
	const struct operator	*op;

	FOREACH_OPERATOR(i, op)
	{
		if ( op->name && op->c )
			printf("%-20s(%c)\t: %s\n", op->name, op->c, op->help);
		else if ( op->name )
			printf("%-20s\t: %s\n", op->name, op->help);
		else if ( op->c )
			printf("%c\t\t\t: %s\n", op->c, op->help);
	}

	return RPN_OK;
}

static const struct operator *
get_operator_by_name_char(const char c)
{
	int			i;
	const struct operator	*op;

	FOREACH_OPERATOR(i, op)
		if ( op->c && op->c == c )
			return op;

	return NULL;
}

static const struct operator *
get_operator_by_name_string(const char *str)
{
	int			i;
	const struct operator	*op;

	FOREACH_OPERATOR(i, op)
		if ( op->name && !strcmp(op->name, str) )
			return op;

	return NULL;
}

const struct operator *
get_operator_by_name(const char *str)
{
	if ( !str )
		return NULL;

	if ( strlen(str) == 1 )
		return get_operator_by_name_char(str[0]);

	return get_operator_by_name_string(str);
}
