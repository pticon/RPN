#include <stdio.h>

#include "rpn.h"


enum rpn_code
func_addition(struct list_head *stack)
{
	static enum rpn_code (*additions[ELT_T_MAX])(struct elt*,
					const struct elt*,
					const struct elt*) =
	{
		integer_addition,
		float_addition,
		string_concatenate,
	};

	return stack_apply_two(stack, STACK_PUSH_RESULT, additions);
}

enum rpn_code
func_substraction(struct list_head *stack)
{
	static enum rpn_code (*substractions[ELT_T_MAX])(struct elt*,
					const struct elt*,
					const struct elt*) =
	{
		integer_substraction,
		float_substraction,
		NULL,
	};

	return stack_apply_two(stack, STACK_PUSH_RESULT, substractions);
}

enum rpn_code
func_multiplication(struct list_head *stack)
{
	static enum rpn_code (*multiplications[ELT_T_MAX])(struct elt*,
					const struct elt*,
					const struct elt*) =
	{
		integer_multiplication,
		float_multiplication,
		NULL,
	};

	return stack_apply_two(stack, STACK_PUSH_RESULT, multiplications);
}

enum rpn_code
func_division(struct list_head *stack)
{
	static enum rpn_code (*divisions[ELT_T_MAX])(struct elt*,
					const struct elt*,
					const struct elt*) =
	{
		integer_division,
		float_division,
		NULL,
	};

	return stack_apply_two(stack, STACK_PUSH_RESULT, divisions);
}

enum rpn_code
func_power(struct list_head *stack)
{
	static enum rpn_code (*powers[ELT_T_MAX])(struct elt*,
					const struct elt*,
					const struct elt*) =
	{
		integer_power,
		float_power,
		NULL,
	};

	return stack_apply_two(stack, STACK_PUSH_RESULT, powers);
}

enum rpn_code
func_incrementation(struct list_head *stack)
{
	static enum rpn_code (*incs[ELT_T_MAX])(struct elt*,
					const struct elt*) =
	{
		integer_incrementation,
		float_incrementation,
		NULL,
	};

	return stack_apply_one(stack, STACK_PUSH_RESULT, incs);
}

enum rpn_code
func_absolute(struct list_head *stack)
{
	static enum rpn_code (*abs[ELT_T_MAX])(struct elt*,
					const struct elt*) =
	{
		integer_absolute,
		float_absolute,
		NULL,
	};

	return stack_apply_one(stack, STACK_PUSH_RESULT, abs);
}
