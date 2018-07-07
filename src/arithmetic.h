#ifndef __ARITHMETIC_H__
#define __ARITHMETIC_H__

enum rpn_code
func_addition(struct list_head *stack);

enum rpn_code
func_substraction(struct list_head *stack);

enum rpn_code
func_multiplication(struct list_head *stack);

enum rpn_code
func_division(struct list_head *stack);

enum rpn_code
func_power(struct list_head *stack);

enum rpn_code
func_incrementation(struct list_head *stack);

enum rpn_code
func_absolute(struct list_head *stack);

#endif /* __ADDITION_H__ */
