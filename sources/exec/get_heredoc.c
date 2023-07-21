/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:38:38 by nsainton          #+#    #+#             */
/*   Updated: 2023/07/21 11:38:41 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int read_heredoc(const char *limiter, int write_fd)
{
  char *line;
  static unsigned int line_index;

  line_index++;
  line = readline(HEREDOC_PROMPT);
  while (line && ! ft_strcmp(line, limiter))
    {
      if (ft_putendl_fd(line, write_fd) == -1)
	return (EXIT_FAILURE);
      free(line);
      line = readline(HEREDOC_PROMPT);
    }
  if (! line)
    ft_dprintf(STDERR_FILENO, HEREDOC_WARNING, line_index, limiter);
  close(write_fd);
  return ((line != NULL) - 1);
}

int heredoc_open(const char *heredoc_name, struct s_heredoc_infos *hd)
{
  hd->write_fd = open(heredoc_name, O_EXCL | O_CREAT | O_WRONLY | O_TRUNC, \
  00600);
  if (hd->write_fd == -1)
    return (EXIT_FAILURE);
  hd->read_fd = open(heredoc_name, O_RDONLY);
  if (hd->read_fd == -1)
    {
      close(hd->write_fd);
      return (EXIT_FAILURE);
    }
  if (unlink(name) == -1)
    {
      close(hd->read_fd);
      close(hd->write_fd);
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}

void create_random_name(char *name, void *address)
{
  unsigned int random;
  char *tmp;
  
