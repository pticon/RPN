#ifndef __ELT_H__
#define __ELT_H__

#include "rpn.h"


enum elt_type
{
	ELT_T_INT,
	ELT_T_FLOAT,
	ELT_T_STR,

	ELT_T_MAX,
};

struct elt
{
	enum elt_type		type;
	union
	{
		int		i;
		float		f;
		char		*c;
	};
	struct list_head	list;
};

struct elt *
elt_new(void);

void
elt_free(struct elt *e);

void
elt_print(const struct elt *e);

enum rpn_code
elt_copy(struct elt *dst, const struct elt *src);

enum rpn_code
elt_migrate(struct elt *e, enum elt_type type);

#endif /* __ELT_H__ */
