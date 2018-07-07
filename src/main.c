#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "rpn.h"


int infinite;

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
process(char *(*get_input)(void *), void *priv)
{
	char			*input,
				*arg;
	const struct operator	*op;
	int			ret;
	DEFINE_LIST_HEAD(stack);

	infinite = 1;

	while ( infinite )
	{
		input = get_input(priv);

		if ( !input )
			break;

		for ( arg = strtok(input, " ") ; arg ; arg = strtok(NULL, " ") )
		{
			if ( (op = get_operator_by_name(arg)) != NULL )
				ret = op->apply(&stack);
			else
				ret = stack_push(&stack, arg);

			if ( ret )
				fprintf(stderr, "Error (%d): %s\n", ret,
					rpn_geterr(ret));
		}

		free(input);
	}

	stack_free(&stack);

	return 0;
}

static char *
get_input_readline(void *arg)
{
	char	*c;

	if ( (c = readline("[" PROGNAME "] ")) )
		add_history(c);

	return c;
}

static int
interactive(void)
{
	version();

	return process(get_input_readline, NULL);
}

static char *
get_input_file(void *arg)
{
	char	*line = NULL;
	size_t	n = 0;
	FILE	*f = arg;
	int	len;

	for (;;)
	{
		if ( getline(&line, &n, f) < 0 )
			return NULL;

		len = strlen(line);

		if ( len && line[len-1] == '\n' )
			line[--len] = '\0';

		if ( !len )
			continue;

		if ( line[0] == '#' )
			continue;

		break;
	}

	return line;
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

	ret = process(get_input_file, f);

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
