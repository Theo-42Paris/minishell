/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmd_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzara <tzara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:45:11 by kjolly            #+#    #+#             */
/*   Updated: 2025/04/11 17:40:07 by tzara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_args_nb(t_token *token)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = token;
	while (tmp)
	{
		if (tmp->token == WORD)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

t_cmd	*new_cmd(t_token *current)
{
	t_cmd	*cmd;
	int		i;

	i = get_args_nb(current);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = malloc(sizeof(char *) * (i + 1));
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	cmd->cmd = NULL;
	cmd->redir = NULL;
	cmd->next = NULL;
	cmd->args[i] = NULL;
	return (cmd);
}

t_cmd	*last_cmd(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->next == NULL)
			return (cmd);
		cmd = cmd->next;
	}
	return (cmd);
}

void	add_cmd(t_cmd **cmd, t_cmd *head)
{
	t_cmd	*last;

	if (cmd)
	{
		if (*cmd)
		{
			last = last_cmd(*cmd);
			last->next = head;
		}
		else
			*cmd = head;
	}
}

void	fill_cmd(t_cmd **cmd, t_token *current)
{
	t_cmd	*head;

	head = new_cmd(current);
	if (!head)
		return ;
	add_cmd(cmd, head);
}
