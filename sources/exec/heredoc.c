#include "minishell.h"

int heredoc(t_command *command)
{
  struct s_heredoc_infos hd;
  size_t len;
  size_t i;
  int    err;

  if (! *command->heredocs)
    return (EXIT_SUCCESS);
  len = tablen(*command->heredocs, sizeof **command->heredocs);
  if (! len)
    return (EXIT_SUCCESS);
  i = 0;
  // ft_printf("This is the len : %u\n", len);
  while (i < len)
    {
      //      ft_printf("Waiting for heredoc\n");
      err = getheredoc(&hd, *command->heredocs + i);
      if (err > 0)
	return (EXIT_FAILURE);
      //  ft_printf("This is the original fd : %d\n", (*command->heredocs + i)->fd);
      // ft_printf("This is the read fd for heredoc : %d\n", hd.read_fd);
      if (! err && (dup2(hd.read_fd, (*command->heredocs + i)->fd) == -1))
	return (EXIT_FAILURE);
      close(hd.read_fd);
      i++;
    }
  return (EXIT_SUCCESS);
}
