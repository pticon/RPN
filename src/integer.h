#ifndef __INTEGER_H__
#define __INTEGER_H__

#include <math.h>

#include "rpn.h"


static inline enum rpn_code
integer_addition(struct elt *dst, const struct elt *e1, const struct elt *e2)
{
	dst->i = e1->i + e2->i;

	return RPN_OK;
}

static inline enum rpn_code
integer_substraction(struct elt *dst, const struct elt *e1, const struct elt *e2)
{
	dst->i = e1->i - e2->i;

	return RPN_OK;
}

static inline enum rpn_code
integer_multiplication(struct elt *dst, const struct elt *e1, const struct elt *e2)
{
	dst->i = e1->i * e2->i;

	return RPN_OK;
}

static inline enum rpn_code
integer_division(struct elt *dst, const struct elt *e1, const struct elt *e2)
{
	dst->i = e1->i / e2->i;

	return RPN_OK;
}

static inline enum rpn_code
integer_power(struct elt *dst, const struct elt *e1, const struct elt *e2)
{
	dst->i = pow(e1->i, e2->i);

	return RPN_OK;
}

static inline enum rpn_code
integer_incrementation(struct elt *dst, const struct elt *src)
{
	dst->i = src->i + 1;

	return RPN_OK;
}

static inline enum rpn_code
integer_absolute(struct elt *dst, const struct elt *src)
{
	dst->i = src->i;

	if ( dst->i < 0 )
		dst->i = - dst->i;

	return RPN_OK;
}

#endif /* __INTEGER_H__ */
