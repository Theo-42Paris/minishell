/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzara <tzara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:32:39 by tzara             #+#    #+#             */
/*   Updated: 2025/03/26 11:59:33 by tzara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
			free(line);
			break ;
		}
		add_history(line);
		tokenizer(&token, line);
		//todo | malloc a securiser ici
		// check_cmd_args(&token);
		if (!check_syntax(&token))
		{
			free_token(&token);
			free(line);
			continue ;
		}
		// token_to_cmd(&cmd, &token);
		test(token, &cmd);
		//todo | comment gerer si cmd est NULL ?
		//todo | si check_syntax est ok on fait le reste, sinon il faut free (faire un "if ... else" ???)
		// print_token(&token);
		print_cmd(&cmd);
		// waitpid();
		// ft_reset_cmd();
		// remettre tt data a 0 pour la pro cmd cat | "grep error"
		free_token(&token);
		free_cmd(&cmd);
	}
	// if (isatty(STDIN_FILENO))
	// {
	// 	ft_printf("exit\n");
	// 	rl_clear_history();
	// 	free_all_data();
	// }
	return (0);
}
