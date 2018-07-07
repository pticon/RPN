#ifndef __STRINGS_H__
#define __STRINGS_H__

#include <stdlib.h>
#include <string.h>

#include "rpn.h"


static inline enum rpn_code
string_concatenate(struct elt *dst, const struct elt *e1, const struct elt *e2)
{
	int len1 = strlen(e1->c);
	int len2 = strlen(e2->c);
	int len3 = len1 + len2 + 1;

	if ( (dst->c = malloc(len3 * sizeof(char))) == NULL )
		return RPN_MEMORY;

	strncpy(dst->c, e1->c, len1);
	strncpy(dst->c + len1, e2->c, len3);

	return RPN_OK;
}

#endif /* __STRINGS_H__ */
