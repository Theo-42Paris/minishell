/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:18:39 by kjolly            #+#    #+#             */
/*   Updated: 2025/04/09 18:37:17 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_token(t_token **token)
{
	t_token	*current;

	current = *token;
	while (current)
	{
		printf("qui est il: %s\n", current->data);
		printf("quel type: %d\n", current->token);
		printf("exp = %d\n", current->exp);
		printf("------------------------\n");
		current = current->next;
	}
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s ", tab[i]);
		i++;
	}
}

void    print_cmd(t_cmd **cmd)
{
	t_cmd *print;

	print = *cmd;
	while (print)
	{
		print_tab(print->args);
		printf("\n--- inside ---\n");
		print_redir(&print->redir);
		printf("--- outside ---\n");
		print = print->next;
	}
}

void    print_redir(t_redir **redir)
{
	t_redir *tmp;

	tmp = *redir;
	while (tmp)
	{
		ft_printf("arg = %s\n", tmp->arg);
		ft_printf("type = %d\n", tmp->token);
		ft_printf("fd = %d\n", tmp->fd_here_doc);
		tmp = tmp->next;
	}
}
