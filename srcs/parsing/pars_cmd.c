/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzara <tzara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 09:09:42 by kjolly            #+#    #+#             */
/*   Updated: 2025/04/11 17:40:16 by tzara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_data_cmd(t_token *token, t_cmd **cmd, t_token **current)
{
	*current = token;
	if (!token || !cmd)
		return ;
	if (!(*cmd))
		fill_cmd(cmd, *current);
}

int	check_tok(t_token *current)
{
	if (current->token == REDIR_IN || current->token == REDIR_OUT
		|| current->token == DELIMITER || current->token == APPEND)
		return (1);
	else
		return (0);
}

void	get_cmd(t_token *token, t_cmd **cmd)
{
	t_token	*current;
	t_token	*prev;
	int		i;

	i = 0;
	prev = NULL;
	init_data_cmd(token, cmd, &current);
	while (current && current->token != PIPE)
	{
		if (check_tok(current) == 1)
		{
			if (current->next)
				fill_redir(&((*cmd)->redir), current);
			prev = current;
			current = current->next;
		}
		if (current && current->token == WORD && (!prev
				|| !is_delimiteur(prev->token)))
			(*cmd)->args[i++] = ft_strdup(current->data);
		prev = current;
		current = current->next;
	}
	(*cmd)->args[i] = NULL;
	get_cmd_2(current, cmd);
}

void	get_cmd_2(t_token *current, t_cmd **cmd)
{
	if (current && current->token == PIPE)
		current = current->next;
	if (current)
	{
		fill_cmd(&((*cmd)->next), current);
		get_cmd(current, &((*cmd)->next));
	}
}

// void	get_cmd(t_token *token, t_cmd **cmd)
// {
// 	t_token	*current;
// 	t_token	*prev;
// 	int		i;

// 	i = 0;
// 	prev = NULL;
// 	init_data_cmd(token, cmd, &current);
// 	while (current && current->token != PIPE)
// 	{
// 		if (check_tok(current) == 1)
// 		{
// 			if (current->next)
// 				fill_redir(&((*cmd)->redir), current);
// 			prev = current;
// 			current = current->next;
// 		}
// 		if (current && current->token == WORD && (!prev
				//|| !is_delimiteur(prev->token)))
// 			(*cmd)->args[i++] = ft_strdup(current->data);
// 		prev = current;
// 		current = current->next;
// 	}
// 	(*cmd)->args[i] = NULL;
// 	if (current && current->token == PIPE)
// 		current = current->next;
// 	if (current)
// 	{
// 		fill_cmd(&((*cmd)->next), current);
// 		get_cmd(current, &((*cmd)->next));
// 	}
// }
