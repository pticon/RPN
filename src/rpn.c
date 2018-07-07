#include <stdio.h>

#include "rpn.h"


const char *
rpn_geterr(enum rpn_code err)
{
	const char	*c = NULL;

	switch ( err )
	{
		case RPN_OK:
		c = "No error";
		break;

		case RPN_STACK_EMPTY:
		c = "Empty stack";
		break;

		case RPN_NOT_SAME_TYPE:
		c = "Not same type";
		break;

		case RPN_MEMORY:
		c = "Out of memory";
		break;

		case RPN_NOT_SUPPORTED:
		c = "Not supported";
		break;
	}

	return c;
}
