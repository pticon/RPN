#ifndef __OPERATOR_H__
#define __OPERATOR_H__

#include "rpn.h"


struct operator
{
	const char	*name;
	const char	c;
	enum rpn_code	(*apply)(struct list_head *);
	const char	*help;
};

const struct operator *
get_operator_by_name(const char *str);

#endif /* __OPERATOR_H__ */
