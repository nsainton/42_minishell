#include "minishell.h"

int set_data(t_data *d)
{
    d->prev_pipe = -1;
	d->index = -1;
	d->pid = gc_calloc(d->cmds_nb, sizeof(int));
	if (!d->pid)
		return (1);
    d->cmds_nb = ft_arrlen((void *)d->cmds)
    if (!d->cmds_nb)
        return (1);
    return (0);
}

int exec_pipeline(t_data *d)
{
    
}