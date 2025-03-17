/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:32:39 by tzara             #+#    #+#             */
/*   Updated: 2025/03/17 13:10:54 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_stack(t_token **token)
{
	t_token	*current;

	current = *token;
	while (current)
	{
		printf("est il une commande: %d\n", current->cmd);
		printf("qui est il: %s\n", current->data);
		printf("quel type: %d\n", current->type);
		printf("------------------------\n");
		current = current->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)envp;
	t_token	*token;
	char	*line;

	token = NULL;
	if (argc != 1)
		return (1);
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			ft_printf("exit\n");
			break ;
		}
		tokenizer(&token, line);
		check_cmd_args(&token);
		check_syntax(&token);
		print_stack(&token);
		add_history(line);
		// waitpid();
		// ft_reset_cmd();
		// remettre tt data a 0 pour la pro cmd    cat | "grep error"
	}
	// if (isatty(STDIN_FILENO))
	// {
	// 	ft_printf("exit\n");
	// 	rl_clear_history();
	// 	free_all_data();
	// }
	return (0);
}
