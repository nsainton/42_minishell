/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:33:22 by nsainton          #+#    #+#             */
/*   Updated: 2023/05/22 14:35:52 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct s_linetest
{
	const char	*test;
	const char	*expected;
};
typedef struct s_linetest	t_linetest;

struct s_teststab
{
	t_linetest	*tests;
	size_t		len;
	size_t		size;
};
typedef struct s_teststab	t_teststab;

static int	test_line(t_cchar *line, char **tmp_line, char *buffer, t_csizet size)
{
	FILE	*stream;
	FILE	*original_stdout;

	stream = fmemopen(buffer, size, "w");
	if (! stream)
	{
		perror("fmemopen");
		return (EXIT_FAILURE);
	}
	original_stdout = stdout;
	stdout = stream;
	*tmp_line = copy_line(line);
	stdout = original_stdout;
	fclose(stream);
	return (EXIT_SUCCESS);
}

static void	fail(t_cchar *expected, t_cchar *output, int testno)
{
	ft_printf("%sTest Failed : %d\n%s", RED, testno, CRESET);
	if (! *output)
		ft_printf("The test was not detected as invalid\n");
	else
	{
		ft_printf("Expected : %s\n", expected);
		ft_printf("True output : %s\n", output);
	}
}

static int	addtest(t_teststab *tests, t_cchar *testline, t_cchar *expected)
{
	t_linetest	*newtests;
	size_t	size;

	if (tests->len == tests->size)
	{
		size = tests->size;
		newtests = gcrealloc(tests->tests, size * sizeof *newtests\
		, 2 * size * sizeof *newtests);
		if (! newtests)
			return (EXIT_FAILURE);
		tests->size = 2 * size;
		tests->tests = newtests;
	}
	(tests->tests + tests->len)->test = testline;
	(tests->tests + tests->len)->expected = expected;
	tests->len ++;
	return (EXIT_SUCCESS);
}

static int	init_tests(t_teststab *tests)
{
	t_linetest	*test;

	test = gccalloc(PARSER_SIZE, sizeof *test);
	if (! test)
		return (EXIT_FAILURE);
	tests->tests = test;
	tests->len = 0;
	tests->size = PARSER_SIZE;
	return (EXIT_SUCCESS);
}

static int	create_tests()
{
	t_teststab	tests;

	if (init_tests(&tests))
		return (EXIT_FAILURE);
	addtest(&tests, "echo bonjour >>", SERROR "newline'");
	return (EXIT_SUCCESS);
}

static int	valid_test(t_linetest *line, int testno)
{
	char	*tmp_line;
	char	buffer[100];

	tmp_line = NULL;
	*buffer = 0;
	ft_printf("Test for line : %s\n", line->test);
	if (! test_line(line->test, &tmp_line, buffer, 100))
		return (EXIT_FAILURE);
	if (! tmp_line && ft_strcmp(line->expected, buffer))
	{
		fail(line->expected, buffer, testno);
		return (0);
	}
	if (tmp_line && ft_strnstr(line->expected, "syntax error", ft_strlen(line->expected) - ft_strlen("syntax error")))
	{
		fail(line->expected, buffer, testno);
		return (0);
	}
	ft_printf("%sTest Succeeded : %d\n%s", GRN, testno, CRESET);
	return (1);
}

int	test(void)
{
	valid_test(NULL, 10);
	return (create_tests());
}
