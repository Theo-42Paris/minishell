/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmd_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzara <tzara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:46:54 by kjolly            #+#    #+#             */
/*   Updated: 2025/04/11 17:40:08 by tzara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_redir	*new_redir(t_token *current)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->arg = ft_strdup(current->next->data);
	if (!new->arg)
	{
		free(new);
		return (NULL);
	}
	new->token = current->token;
	new->fd_here_doc = -1;
	new->next = NULL;
	return (new);
}

t_redir	*last_redir(t_redir *redir)
{
	while (redir)
	{
		if (redir->next == NULL)
			return (redir);
		redir = redir->next;
	}
	return (redir);
}

void	add_redir(t_redir **redir, t_redir *new)
{
	t_redir	*last;

	if (redir)
	{
		if (*redir)
		{
			last = last_redir(*redir);
			last->next = new;
		}
		else
			*redir = new;
	}
}

void	fill_redir(t_redir **redir, t_token *current)
{
	t_redir	*new;

	new = new_redir(current);
	if (!new)
		return ;
	add_redir(redir, new);
}
