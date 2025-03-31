/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 09:09:42 by kjolly            #+#    #+#             */
/*   Updated: 2025/03/31 09:24:35 by kjolly           ###   ########.fr       */
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

void    fill_cmd(t_cmd **cmd, t_token *current)
{
	t_cmd	*head;

	head = new_cmd(current);
	if (!head)
		return ;
	add_cmd(cmd, head);
}

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
	t_redir *last;

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

void    get_cmd(t_token *token, t_cmd **cmd)
{
	t_token	*current;
	t_token	*prev;
	int		i;

	i = 0;
	prev = NULL;
	current = token;
	if (!token || !cmd)
		return ;
	if (!(*cmd)) // si c'est la premiere cmd et que ducoup c vide 
		fill_cmd(cmd, current);
	while (current && current->token != PIPE)
	{
		if (current->token == REDIR_IN || current->token == REDIR_OUT ||
			current->token == DELIMITER || current->token == APPEND)
		{
			if (current->next)
				fill_redir(&((*cmd)->redir), current);
			prev = current;
			current = current->next;
			// continue;
		}
		// if (prev && is_delimiteur(prev->token))
		// {
		// 	prev = current;
		// 	current = current->next;
		// }
		if (current->token == WORD && (!prev || !is_delimiteur(prev->token)))
		{
			printf("data : %s\n", current->data);
			(*cmd)->args[i] = ft_strdup(current->data);
			i++;
		}
		prev = current;
		current = current->next;
	}
	(*cmd)->args[i] = NULL;
	if (current && current->token == PIPE)
		current = current->next;
	if (current)
	{
		fill_cmd(&((*cmd)->next), current);
		get_cmd(current, &((*cmd)->next));
	}
}
