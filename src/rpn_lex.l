%{

#include <stdio.h>

#include "rpn.h"

%}


comment		(#.*)
space		([ 	]+)
newline		(\n)

digit		([0-9])
letter		([a-z]|[A-Z])
integer		([-+]?{digit}{digit}*)
float		({integer}\.({digit}*)?)
string		('({digit}|{letter})*')

absolute	(abs)
addition	(add|\+)
deep		(deep)
division	(div|\/)
drop		(drop)
duplicate	(dup|d)
flush		(flush|f)
help		(help|h)
incrementation	(inc|\+\+)
multiplication	(mul|\*|x|\.)
power		(pow|^)
print		(print|p)
quit		(quit|q)
substraction	(sub|-)
swap		(swap|s)
operator	({absolute}|{addition}|{deep}|{division}|{drop}|{duplicate}|{flush}|{help}|{incrementation}|{multiplication}|{power}|{print}|{quit}|{substraction}|{swap})

%%

{space}		|
{comment}	|
{newline}	;

{float}		|
{integer}	|
{string}	{
			int			ret;

			ret = stack_push(stack, yytext);

			if ( ret )
				fprintf(stderr, "Error (%d): %s\n", ret, rpn_geterr(ret));
		}

{operator}	{
			const struct operator	*op;
			int			ret;

			if ( (op = get_operator_by_name(yytext)) != NULL )
				ret = op->apply(stack);
			else
				ret = RPN_INVALID_OPERATOR;

			if ( ret )
				fprintf(stderr, "Error (%d): %s\n", ret, rpn_geterr(ret));
		}

%%
