#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "rpn.h"

#include "rpn_lex.h"

int infinite;

static int	(*rpn_input_p)(char *, int size);

int
rpn_input(char *buf, int size)
{
	return rpn_input_p(buf, size);
}

static void
usage(void)
{
	printf("usage: " PROGNAME " [options] [file]\n");
	printf("options:\n");
	printf("\t-h: display this and exit\n");
	printf("\t-v: print version information and exit\n");
}

static void
version(void)
{
	printf(PROGNAME " " VERSION "\n");
}

static int
process(void)
{
	int			ret;
	DEFINE_LIST_HEAD(stack);

	ret = yylex(&stack);

	stack_free(&stack);

	return ret;
}

static int
get_input_readline(char *buf, int size)
{
	char	*c;
	size_t	len;
	int	ret;

	while ( 1 )
	{
		if ( !infinite )
			return 0;

		if ( (c = readline("[" PROGNAME "] ")) )
			add_history(c);
		else
			return 0;

		if ( (len = strlen(c)) != 0 )
			break;
	}

	len++;
	ret = len < size ? len : size;

	memcpy(buf, c, ret);

	free(c);

	return ret;
}

static int
interactive(void)
{
	version();

	infinite = 1;

	rpn_input_p = get_input_readline;

	return process();
}

static int
get_input_file(char *buf, int size)
{
	int	ret;

	errno = 0;

	while ( (ret = (int)fread(buf, 1, (size_t) size, yyin)) == 0 && ferror(yyin) )
	{
		if( errno != EINTR)
			return 0;

		errno = 0;
		clearerr(yyin);
	}

	return ret;
}

static int
process_file(const char *file)
{
	FILE	*f;
	int	ret;

	if ( (f = fopen(file, "r")) == NULL )
	{
		perror(file);
		return -1;
	}

	yyin = f;

	rpn_input_p = get_input_file;

	ret = process();

	fclose(f);

	return ret;
}

int
main(int argc, char *argv[])
{
	int	c,
		ret;

	while ( (c = getopt(argc, argv, "hv")) != -1 )
	{
		switch ( c )
		{
			case 'h':
			usage();
			return 0;

			case 'v':
			version();
			return 0;

			default:
			fprintf(stderr, "Unknown option %c\n", (char) c);
			return -1;
		}
	}

	argv += optind;
	argc -= optind;

	if ( argc == 0 )
		return interactive();

	for ( c = 0 ; c < argc ; c++ )
		if ( (ret = process_file(argv[c])) )
			return ret;

	return 0;
}
