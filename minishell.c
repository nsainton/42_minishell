/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:08:42 by avedrenn          #+#    #+#             */
/*   Updated: 2023/04/14 16:04:26 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	//char	*line;
	t_env	*my_env;

	if (argc > 1 || !argv)
		return (1);
	//sigaction(SIGINT, sig_handler);
	my_env = get_my_env(envp);
	/* while (1)
	{
		line = readline("minishell>");
		if (!line)
			break ;
		printf("%s\n", line);
		//parse_line(line);
	} */
	export_env(my_env, "fneuwof");
	free_gc(1);
	return (errno);

}
