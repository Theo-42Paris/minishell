/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:32:39 by tzara             #+#    #+#             */
/*   Updated: 2025/04/09 18:05:24 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)envp;
	t_token	*token;
	t_cmd	*cmd;
	t_env	*env;
	char	*line;
	char	*good_line;

	token = NULL;
	cmd = NULL;
	env = NULL;
	if (argc != 1)
		return (1);
	while (1)
	{
		line = readline(G"minishell> "RST);
		if (!line)
		{
			ft_printf("exit\n");
			free(line);
			break ;
		}
		add_history(line);
		get_env(&env, envp);
		good_line = pre_token(line);
		tokenizer(&token, good_line);
		if (!check_syntax(&token))
		{
			free_token(&token);
			free(line);
			continue ;
		}
		get_cmd(token, &cmd);
		handle_here_doc(cmd);
		// print_token(&token);
		print_cmd(&cmd);
		// waitpid();
		// ft_reset_cmd();
		// remettre tt data a 0 pour la pro cmd
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
