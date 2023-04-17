/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:44:59 by nsainton          #+#    #+#             */
/*   Updated: 2023/04/16 17:43:53 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(void)
{
	char	*line;
	size_t	index = 0;

	line = strdup("Li");
	if (! line)
		return (0);
	printf("line[0] : %s\n", line);
	while (strlen(line) > 1)
	{
		free(line);
		index ++;
		line = readline("Wesh>");
		if (! line)
			return (0);
		printf("line[%ld] : %s\n", index, line);
	}
	free(line);
	return (0);
}
