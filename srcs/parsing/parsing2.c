/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 16:56:33 by kjolly            #+#    #+#             */
/*   Updated: 2025/03/17 15:47:59 by kjolly           ###   ########.fr       */
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
// todo | vas falloir faire +
void	syntax_node(int start, t_token *current, t_token *prev)
{
	if (start == 1 && current->type == 2)
		ft_printf("minishell: syntax error near unexpected token '|'\n");
	if (current->type == 2)
	if (current->type == 3)
	if (current->type == 4)
	if (current->type == 5)
	if (current->type == 6)
}

void	check_syntax(t_token **token)
{
	t_token	*current;
	t_token *prev;
	int		start;

	start = 1;
	prev = NULL;
	current = *token;
	while (current)
	{
		syntax_node(start, current, prev);
		start = 0;
		prev = current;
		current = current->next;
	}
}
