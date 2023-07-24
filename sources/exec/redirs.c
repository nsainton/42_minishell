/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:16:50 by avedrenn          #+#    #+#             */
/*   Updated: 2023/07/24 19:01:27 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_redirs(t_data *d, t_command *cmd)
{
	int	i;
	i = 0;
	d->errnum = 0;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	if (!cmd->redirs && !cmd->heredocs)
		return (0);
	if (cmd->heredocs)
	{
		//ft_printf("There are some heredocs here \n");
		heredoc(cmd);
	}
    cmd->fds = gc_lstnew(NULL);
    while (cmd->redirs && cmd->redirs[i])
    {
        d->errnum = make_dups(cmd, cmd->redirs[i]);
        i ++; 
    }
	/* while (cmd->redirs && cmd->redirs[i])
	{
		if (cmd->redirs[i]->mode == 'r' || cmd->redirs[i]->mode == 'b')
			d->errnum = get_infile(cmd, cmd->redirs[i]);
		if (cmd->redirs[i]->mode == 'w')
			d->errnum = get_outfile(cmd, cmd->redirs[i], O_TRUNC);
		else if (cmd->redirs[i]->mode == 'a')
			d->errnum = get_outfile(cmd, cmd->redirs[i], O_APPEND);
		i ++;
	} */

	return (d->errnum);
}

int make_dups(t_command *cmd, t_redir   *redir)
{
    int new_fd;

    if (redir->fd == 0 && (redir->mode == 'r' || redir->mode == 'b'))
        return (get_infile(cmd, redir));
    else if (redir->fd == 1 && redir->mode == 'w')
        return (get_outfile(cmd, redir, O_TRUNC));
    else if (redir->fd == 1 && redir->mode == 'a')
        return (get_outfile(cmd, redir, O_APPEND));
    else
    {
        new_fd = open_file_fd(redir, );
        gc_lst_add_back();
    }
    //inverser
// 2>0
    return (0);
}

int open_file_fd(t_redirs *redir, char mode)
{
    int new_fd;

    if (r->file)
	{
		new_fd = open(r->file, O_CREAT | O_RDWR | mode, 0000644);
		if (new_fd < 0)
		{
			ft_dprintf(2, "outfile : %s : %s\n", r->file, strerror(errno));
			return (errno);
		}
        return (new_fd);
	}
}