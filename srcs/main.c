/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:32:39 by tzara             #+#    #+#             */
/*   Updated: 2025/03/19 13:42:29 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	stack_free(t_token **token)
{
	t_token	*tmp;

	if (!token)
		return ;
	while (*token)
	{
		tmp = (*token)->next;
		free((*token)->data);
		free(*token);
		*token = tmp;
	}
	*token = NULL;
}

void	print_stack(t_token **token)
{
	t_token	*current;
	int i = 0;
	current = *token;
	while (current)
	{
		printf("est il une commande: %d\n", current->cmd);
		printf("qui est il: %s\n", current->data);
		printf("quel type: %d\n", current->type);
		printf("------------------------\n");
		printf("%d\n", i);
		i++;
		current = current->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)envp;
	t_token	*token;
	// t_cmd	*cmd;
	char	*line;

	token = NULL;
	if (argc != 1)
		return (1);
	while (1)
	{
		line = readline(G"minishell> "RST);
		//todo | faire le parsing des pipes et redir avant la tokenization
		//todo | gerer le cas ou tout est coller
		if (!line)
		{
			ft_printf("exit\n");
			break ;
		}
		tokenizer(&token, line);
		//todo | malloc a securiser ici
		check_cmd_args(&token);
		// cmd = token_to_cmd(&token);
		//todo | comment gerer si cmd est NULL ?
		check_syntax(&token);
		//todo | si check_syntax est ok on fait le reste, sinon il faut free (faire un "if ... else" ???)
		// print_stack(&token);
		add_history(line);
		// waitpid();
		// ft_reset_cmd();
		// remettre tt data a 0 pour la pro cmd    cat | "grep error"
		stack_free(&token);
	}
	// if (isatty(STDIN_FILENO))
	// {
	// 	ft_printf("exit\n");
	// 	rl_clear_history();
	// 	free_all_data();
	// }
	return (0);
}
