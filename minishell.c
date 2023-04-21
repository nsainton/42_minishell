/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:08:42 by avedrenn          #+#    #+#             */
/*   Updated: 2023/04/21 18:15:08 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**args;
	t_env	*my_env;
	t_command cmd;
	int	i;
	int	opt;

	if (argc > 1 || !argv)
		return (1);
	init_sig();
	my_env = get_my_env(envp);
	cmd.args = gcmalloc (1000);
	cmd.options = gcmalloc (1000);
	ft_bzero(cmd.args, 1000);
	ft_bzero(cmd.options, 1000);
	while (1)
	{
		i = opt = 0;
		line = readline("minishell> ");
		if (line[0])
		{
			args = gc_split(line, ' ');
			cmd.command = args[0];
			if (args[1])
			{
				if (args[1][0] == '-')
				{
					cmd.options[0] = args[1];
					opt = 1;
				}
				else
					cmd.options[0] = NULL;
				while (args[i + opt + 1])
				{
					cmd.args[i] = args[1 + opt + i];
					printf("args[%d] = %s\n", i, cmd.args[i]);
					i ++;
				}
				cmd.args[i] = 0;
			}
			else
			{
				cmd.args[0] = NULL;
				cmd.options[0] = NULL;
			}
			which_builtin(&cmd, my_env);
			cmd.command[0] = 0;
			cmd.options[0] = 0;
			cmd.args[0] = 0;
		}
	}
	free_gc();
	return (errno);
}


/* char	**allocate_strings_array(t_csizet size)
{
	char	**array;
	size_t	index;

	if (! (array = gccalloc(size, sizeof * array)))
		return (NULL);
	index = 0;
	while (index < size)
	{
		if (! (*(array + index) = gccalloc(1, sizeof ** array)))
			return (NULL);
		index ++;
	}
	return (array);
}

void	print_array(char *const*array, t_csizet size)
{
	size_t	index;

	index = 0;
	while (index < size)
	{
		ft_printf("array[%u] : %p\n", index, *(array + index));
		index ++;
	}
	ft_printf("array : %p\n", array);
}

void print_strings(char *const *array)
{
	size_t	index;

	ft_printf("This is the strings array address : %p\n", array);
	index = 0;
	while (*(array + index))
	{
		ft_printf("array[%u] : %s\n", index, *(array + index));
		index ++;
	}
}
*/

//int	main(int ac, char **av)
/*
int	main(void)
{
	char	*line;
	char	*trimmed;
	char	**strings_array;
	void	*node;
	void	*rnode;
	//char	**split;

	//sigaction(SIGINT, sig_handler);
	line = readline("minishell>");
	if (! line)
		return (EXIT_FAILURE);
	if (ft_strlen(line) < 2 || gc_add(line))
	{
		free(line);
		return (EXIT_FAILURE);
	}
	while (ft_strlen(line) > 1)
	{
		if (! line)
			break ;
		ft_printf("%s\n", line);
		if (! (trimmed = gc_strtrim(line, " ")))
			break ;
		ft_printf("Trimmed line : %s\n", trimmed);
		line = readline("minishell>");
		if (gc_add(line))
		{
			free(line);
			break ;
		}
		//parse_line(line);
	}
	*/
	/*
	for (size_t index = 0; index < 10 * TRASH_SIZE + 10; index ++)
	{
		line = gcmalloc(1);
		if (! line)
			break ;
		if (index == 3)
			node = line;
		if (index == 5)
			rnode = line;
		if (index == 20 && (! (strings_array = allocate_strings_array(index))))
			return (free_gc(EXIT_FAILURE));
	}
	ft_printf("This is the len : %u\n", gc_len());
	print_collector();
	int error = free_nodes(10, 0);
	if (error)
		ft_printf("This is the error : %d\n", error);
	else
		ft_printf("This is the len : %u\n", gc_len());
	print_collector();
	ft_printf("This is the saved node :%p\n", node);
	free_node(node, 0);
	print_collector();
	ft_printf("This is the node to realloc : %p\n", rnode);
	rnode = gcrealloc(rnode, 1, 3);
	ft_printf("This is the realloced' node : %p\n", rnode);
	if (! rnode)
		return (free_gc(NOT_IN_COLLECTOR));
	print_collector();
	print_array(strings_array, 20);
	free_array_strings_size(strings_array, 20, 0);
	print_collector();
	if (ac < 3)
		return (NO_ERROR);
	print_collector();
	split = gc_split(av[1], **(av + 2));
	print_collector();
	if (! split)
	{
		free_gc();
		return (ALLOCATION_ERROR);
	}
	print_strings(split);
	*/
	/*
	print_collector();
	free_gc();
	return (EXIT_SUCCESS);
}
*/
