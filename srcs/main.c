/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:32:39 by tzara             #+#    #+#             */
/*   Updated: 2025/03/24 15:49:42 by kjolly           ###   ########.fr       */
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
		i++;
		current = current->next;
	}
}

void	print_redir(t_redir *token)
{
	t_redir	*current;

	current = token;
	while (current)
	{
		printf("la redir : %s\n", current->arg);
		printf("son type : %d\n", current->type);
		current = current->next;
	}
}

void	print_tab(char **tab)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			write(1, &tab[i][j], 1);
			j++;
		}
		i++;
	}
}

void	print_cmd(t_cmd **cmd)
{
	t_cmd	*current_cmd;
	int		i;
	
	i = 0;
	current_cmd = *cmd;
	while (current_cmd)
	{
		printf("j'entre dans la commande %d --\n", i);
		printf("liste des redir ---------------------------\n");
		print_redir(current_cmd->redir);
		printf("la commande :%s\n", current_cmd->cmd);
		printf("liste des args-----------------------------\n");
		print_tab(current_cmd->args);
		printf("je sors de cette commande\n\n");
		current_cmd = current_cmd->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)envp;
	t_token	*token;
	t_cmd	*cmd;
	char	*line;

	token = NULL;
	cmd = NULL;
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
		check_syntax(&token);
		// token_to_cmd(&cmd, &token);
		test(&token, &cmd);
		//todo | comment gerer si cmd est NULL ?
		//todo | si check_syntax est ok on fait le reste, sinon il faut free (faire un "if ... else" ???)
		print_stack(&token);
		printf("-------------------------------------\n\n");
		print_cmd(&cmd);
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
