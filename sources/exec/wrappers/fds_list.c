/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 10:41:45 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/11 13:59:16 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Attempt at writting functions that are wrappers for classic dup2,
	open, close and pipe functions that manipulate file descriptors but that 
	also keep track of a linked list of open file descriptors during the whole
	duration of the program. The nodes will be allocated with gclstnewcpy
	so that they're not deleted when the function returns.
	Function will be prefixed with `s_` with the s meaning : "store" to 
	signal the user that the file descriptor will be stored.
	Function will return :
		. -2 if there is an allocation error
		. The return value specified in the man otherwise
*/

int	s_open(const char *pathname, int flags, mode_t mode)
{
	struct s_list	**fdlist;
	struct s_list	*newnode;
	int				fd;

	fdlist = get_fdlist();
	if (! mode)
		fd = open(pathname, flags);
	else
		fd = open(pathname, flags, mode);
	if (fd == -1)
		return (-1);
	newnode = gc_lstnew_cpy(&fd, sizeof fd);
	if (! newnode)
	{
		close(fd);
		return (-2);
	}
	ft_lstadd_front(fdlist, newnode);
	return (fd);
}

static int	equal(const int *a, const int *b)
{
	return (*a != *b);
}

int	s_close(int fd)
{
	struct s_list	**fdlist;
	struct s_list	*fdaddress;

	fdlist = get_fdlist();
	fdaddress = ft_list_find(*fdlist, &fd, equal);
	if (! fdaddress)
		return (0);
	del_node(fdlist, fdaddress, free_node);
	return (close(fd));
}

/*
	Here we attempt to dup2 before trying to create the new node.
	Thus, the newfd will be closed if the dup2 call succeeds but
	the new node can't be created. Be sure to take that into
	account while using this function
*/
int	s_dup2(int oldfd, int newfd)
{
	struct s_list	**fdlist;
	struct s_list	*newnode;

	if (dup2(oldfd, newfd) == -1)
		return (-1);
	fdlist = get_fdlist();
	newnode = ft_list_find(*fdlist, &newfd, equal);
	if (newnode)
		return (newfd);
	newnode = gc_lstnew_cpy(&newfd, sizeof newfd);
	if (! newnode)
	{
		close(newfd);
		return (-2);
	}
	ft_lstadd_front(fdlist, newnode);
	return (newfd);
}

int	s_pipe(int pipefd[2])
{
	struct s_list	**fdlist;
	struct s_list	*read_node;
	struct s_list	*write_node;

	if (pipe(pipefd) == -1)
		return (-1);
	fdlist = get_fdlist();
	read_node = gc_lstnew_cpy(pipefd, sizeof * pipefd);
	if (! read_node)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (-2);
	}
	write_node = gc_lstnew_cpy(pipefd + 1, sizeof * pipefd);
	if (! write_node)
	{
		gc_lstdelone(read_node, free_node);
		close(pipefd[0]);
		close(pipefd[1]);
		return (-2);
	}
	ft_lstadd_front(fdlist, read_node);
	ft_lstadd_front(fdlist, write_node);
	return (0);
}
