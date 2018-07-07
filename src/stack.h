#ifndef __STACK_H__
#define __STACK_H__

#include "rpn.h"


#define STACK_PUSH_RESULT	(1<<0)
#define STACK_PUSH_INPUT	(1<<1)
#define STACK_PUSH_ALL		(STACK_PUSH_RESULT|STACK_PUSH_INPUT)

enum rpn_code
stack_print(struct list_head *stack);

enum rpn_code
stack_free(struct list_head *stack);

enum rpn_code
stack_push(struct list_head *stack, const char *str);

enum rpn_code
stack_duplicate(struct list_head *stack);

enum rpn_code
stack_drop(struct list_head *stack);

enum rpn_code
stack_depth(struct list_head *stack);

enum rpn_code
stack_swap(struct list_head *stack);

enum rpn_code
stack_apply_one(struct list_head *stack, int flags,
	enum rpn_code (*apply[ELT_T_MAX])(struct elt *,
					const struct elt *));

enum rpn_code
stack_apply_two(struct list_head *stack, int flags,
	enum rpn_code (*apply[ELT_T_MAX])(struct elt *,
					const struct elt *,
					const struct elt *));

#endif /* __STACK_H__ */
