#include <stdio.h>
#include <string.h>

#include "rpn.h"


enum rpn_code
stack_print(struct list_head *stack)
{
	struct elt	*e;

	list_for_each_entry_prev(e, stack, list)
		elt_print(e);

	return RPN_OK;
}

enum rpn_code
stack_free(struct list_head *stack)
{
	struct elt	*e,
			*tmp;

	list_for_each_entry_safe(e, tmp, stack, list)
	{
		list_del(&e->list);
		elt_free(e);
	}

	INIT_LIST_HEAD(stack);

	return RPN_OK;
}

enum rpn_code
stack_push(struct list_head *stack, const char *str)
{
	struct elt	*e;
	int		len;

	if ( (e = elt_new()) == NULL )
		return RPN_MEMORY;

	len = strlen(str);

	if ( len && str[0] == '\'' && str[len-1] == '\'' )
	{
		e->type = ELT_T_STR;
		if ( (e->c = strndup(str+1, len-2)) == NULL )
		{
			elt_free(e);
			return RPN_MEMORY;
		}
	}
	else if ( strstr(str, ".") )
	{
		e->type = ELT_T_FLOAT;
		sscanf(str, "%f", &e->f);
	}
	else
	{
		e->type = ELT_T_INT;
		sscanf(str, "%d", &e->i);
	}

	list_push(stack, e, list);

	return RPN_OK;
}

enum rpn_code
stack_duplicate(struct list_head *stack)
{
	static enum rpn_code (*duplicates[ELT_T_MAX])(struct elt *,
						const struct elt *) =
	{
		elt_copy,
		elt_copy,
		elt_copy,
	};

	return stack_apply_one(stack, STACK_PUSH_ALL, duplicates);
}

enum rpn_code
stack_drop(struct list_head *stack)
{
	struct elt	*e = list_pop(stack, struct elt, list);

	if ( e == NULL )
		return RPN_STACK_EMPTY;

	elt_free(e);

	return RPN_OK;
}

enum rpn_code
stack_depth(struct list_head *stack)
{
	struct elt	*e;
	int		deep = 0;
	char		str[256];

	list_for_each_entry(e, stack, list)
		deep++;

	snprintf(str, sizeof(str), "%d\n", deep);

	return stack_push(stack, str);
}

enum rpn_code
stack_swap(struct list_head *stack)
{
	struct elt	*e1 = list_pop(stack, struct elt, list),
			*e2 = list_pop(stack, struct elt, list);
	enum rpn_code	ret;

	if ( e1 == NULL || e2 == NULL )
	{
		ret = RPN_STACK_EMPTY;
		goto err;
	}

	list_push(stack, e1, list);
	list_push(stack, e2, list);

	return RPN_OK;
err:
	if ( e2 )
		list_push(stack, e2, list);

	if ( e1 )
		list_push(stack, e1, list);

	return ret;
}

enum rpn_code
stack_apply_one(struct list_head *stack, int flags,
	enum rpn_code (*apply[ELT_T_MAX])(struct elt *, const struct elt *))
{
	struct elt	*e1 = list_pop(stack, struct elt, list),
			*e2 = NULL;
	int		ret;

	if ( e1 == NULL )
	{
		ret = RPN_STACK_EMPTY;
		goto err;
	}

	if ( apply[e1->type] == NULL )
	{
		ret = RPN_NOT_SUPPORTED;
		goto err;
	}

	if ( (e2 = elt_new()) == NULL )
	{
		ret = RPN_MEMORY;
		goto err;
	}

	e2->type = e1->type;

	if ( (ret = apply[e2->type](e2, e1)) )
		goto err;

	if ( flags & STACK_PUSH_INPUT )
		list_push(stack, e1, list);
	else
		elt_free(e1);

	if ( flags & STACK_PUSH_RESULT )
		list_push(stack, e2, list);
	else
		elt_free(e2);

	return RPN_OK;
err:
	if ( e2 )
		elt_free(e2);

	if ( e1 )
		list_push(stack, e1, list);

	return ret;
}

enum rpn_code
stack_apply_two(struct list_head *stack, int flags,
	enum rpn_code (*apply[ELT_T_MAX])(struct elt *,
					const struct elt *,
					const struct elt *))
{
	struct elt	*e1 = list_pop(stack, struct elt, list),
			*e2 = list_pop(stack, struct elt, list),
			*e3 = NULL;
	enum rpn_code	ret;

	if ( e1 == NULL || e2 == NULL )
	{
		ret = RPN_STACK_EMPTY;
		goto err;
	}

	if ( e1->type != e2->type )
	{
		if ( e1->type > e2->type )
			ret = elt_migrate(e2, e1->type);
		else
			ret = elt_migrate(e1, e2->type);

		if ( ret )
			goto err;
	}

	if ( (e3 = elt_new()) == NULL )
	{
		ret = RPN_MEMORY;
		goto err;
	}

	e3->type = e1->type;

	if ( apply[e3->type] == NULL )
	{
		ret = RPN_NOT_SUPPORTED;
		goto err;
	}

	if ( (ret = apply[e3->type](e3, e2, e1)) )
		goto err;

	if ( flags & STACK_PUSH_INPUT )
	{
		list_push(stack, e2, list);
		list_push(stack, e1, list);
	}
	else
	{
		elt_free(e2);
		elt_free(e1);
	}

	if ( flags & STACK_PUSH_RESULT )
		list_push(stack, e3, list);
	else
		elt_free(e3);

	return RPN_OK;
err:
	if ( e3 )
		elt_free(e3);

	if ( e2 )
		list_push(stack, e2, list);

	if ( e1 )
		list_push(stack, e1, list);

	return ret;
}
