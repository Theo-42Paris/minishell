/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:32:39 by tzara             #+#    #+#             */
/*   Updated: 2025/03/13 17:21:59 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int main(int argc, char **argv, char **envp)
{
	t_token *token;
	char 	*str;

	token = NULL;
	while(1)
	{
		str = readline("minishell> ");
		add_history(str);
		if (!str)
		{
			ft_printf("exit\n");
			break ;
		}
		add_history(str);
		parsing(&token, str);
	}
	return (0);
}
