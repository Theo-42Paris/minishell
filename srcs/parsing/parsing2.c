/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 16:56:33 by kjolly            #+#    #+#             */
/*   Updated: 2025/03/18 15:54:16 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    check_cmd_args(t_token **token)
{
	int		count;
	t_token	*current;
	t_token *prev;

	current = *token;
	prev = NULL;
	count = 0;
	while (current)
	{
		if (((count == 0 && current->type == 1) || (prev && (!strncmp(prev->data,
			"|", ft_strlen(prev->data)) && current->type == 1))))
			current->cmd = 1;
		else
			current->cmd = 0;
		count++;
		prev = current;
		current = current->next;
	}
}

void	token_to_cmd(t_token **token, t_cmd **cmd)
{
	t_token	*current;

	current = *token;
	while (current)
	{
		if -> cmd
		if -> redir
		if -> pipe
		current = current->next;
	}
}

// int	syntax_node(int start, int end, t_token *current, t_token *prev)
// {
// 	if (start == 1)
// 	{
// 		if (current->type == 2)
// 			return (ft_printf("minishell: syntax error near unexpected token '|'\n"));
// 		else if (current->type != 2 && current->type != 1)
// 			return (ft_printf("minishell: syntax error near unexpected token 'newline'\n"));
// 		return (0);
// 	}
// 	else if (start > 1)
// 	{
// 		if (prev->type == 2 && (current->type != 1 && current->type != 2))
// 			return (ft_printf("minishell: syntax error near unexpected token 'newline'\n"));
// 		else if (current->type != 1  && prev->type != 1)
// 			return (ft_printf("minishell: syntax error near unexpected token '%s'\n", current->data));
// 		return (0);
// 	}
// 	else if (end == 1)
// 	{
// 		if (current->type == 2)
// 			return (ft_printf("minishell: syntax error near unexpected token '|'\n"));
// 		else if (current->type != 1 && current->type != 2 && (prev->type == 1 || prev->type == 2))
// 			return (ft_printf("minishell: syntax error near unexpected token 'newline'\n"));
// 		else if (current->type != 1 && current->type != 2 && (prev->type != 1 && prev->type != 2))
// 			return (ft_printf("minishell: syntax error near unexpected token '%s'\n", current->data));
// 		return (0);
// 	}
// 	return (0);
// }

// void	check_syntax(t_token **token)
// {
// 	t_token	*current;
// 	t_token *prev;
// 	int		start;
// 	int		end;

// 	start = 1;
// 	end = 0;
// 	prev = NULL;
// 	current = *token;
// 	while (current)
// 	{
// 		if (current->next == NULL)
// 			end = 1;
// 		if (syntax_node(start, end, current, prev))
// 			break ;
// 		ft_printf("------ %d ------\n", start);
// 		start++;
// 		ft_printf("-- -- %d -- --\n", end);
// 		prev = current;
// 		current = current->next;
// 	}
// }
