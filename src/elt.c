#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rpn.h"


static void
elt_init(struct elt *e)
{
	e->c = NULL;
	INIT_LIST_HEAD(&e->list);
}

struct elt *
elt_new(void)
{
	struct elt	*e;

	if ( (e = malloc(sizeof(struct elt))) == NULL )
		return NULL;

	elt_init(e);

	return e;
}

void
elt_free(struct elt *e)
{
	if ( !e )
		return;

	if ( e->type == ELT_T_STR && e->c )
		free(e->c);

	free(e);
}

enum rpn_code
elt_copy(struct elt *dst, const struct elt *src)
{
	switch ( (dst->type = src->type) )
	{
		case ELT_T_INT:
		dst->i = src->i;
		break;

		case ELT_T_FLOAT:
		dst->f = src->f;
		break;

		case ELT_T_STR:
		if ( (dst->c = strdup(src->c)) == NULL )
			return RPN_MEMORY;
		break;

		case ELT_T_MAX:
		return RPN_NOT_SUPPORTED;
	}

	return RPN_OK;
}

void
elt_print(const struct elt *e)
{
	if ( !e )
	{
		printf("NULL\n");
		return;
	}

	switch ( e->type )
	{
		case ELT_T_INT:
		printf("%d\n", e->i);
		break;

		case ELT_T_FLOAT:
		printf("%f\n", e->f);
		break;

		case ELT_T_STR:
		printf("%s\n", e->c);
		break;

		case ELT_T_MAX:
		break;
	}
}

enum rpn_code
elt_migrate(struct elt *e, enum elt_type type)
{
	enum elt_type old = e->type;

	if ( type == ELT_T_FLOAT && old == ELT_T_INT )
	{
		e->type = ELT_T_FLOAT;
		e->f = e->i;
		return RPN_OK;
	}

	return RPN_NOT_SUPPORTED;
}
