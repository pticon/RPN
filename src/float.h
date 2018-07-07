#ifndef __FLOAT_H__
#define __FLOAT_H__

#include <math.h>

#include "rpn.h"


static inline enum rpn_code
float_addition(struct elt *dst, const struct elt *e1, const struct elt *e2)
{
	dst->f = e1->f + e2->f;

	return RPN_OK;
}

static inline enum rpn_code
float_substraction(struct elt *dst, const struct elt *e1, const struct elt *e2)
{
	dst->f = e1->f - e2->f;

	return RPN_OK;
}

static inline enum rpn_code
float_multiplication(struct elt *dst, const struct elt *e1, const struct elt *e2)
{
	dst->f = e1->f * e2->f;

	return RPN_OK;
}

static inline enum rpn_code
float_division(struct elt *dst, const struct elt *e1, const struct elt *e2)
{
	dst->f = e1->f / e2->f;

	return RPN_OK;
}

static inline enum rpn_code
float_power(struct elt *dst, const struct elt *e1, const struct elt *e2)
{
	dst->f = powf(e1->f, e2->f);

	return RPN_OK;
}

static inline enum rpn_code
float_incrementation(struct elt *dst, const struct elt *src)
{
	dst->f = src->f + 1;

	return RPN_OK;
}

static inline enum rpn_code
float_absolute(struct elt *dst, const struct elt *src)
{
	dst->f = src->f;

	if ( dst->f < 0 )
		dst->f = - dst->f;

	return RPN_OK;
}

#endif /* __FLOAT_H__ */
