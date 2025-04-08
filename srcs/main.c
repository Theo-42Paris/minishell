/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:32:39 by tzara             #+#    #+#             */
/*   Updated: 2025/04/07 15:47:02 by kjolly           ###   ########.fr       */
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
		//todo | faire le parsing des pipes et redir avant la tokenization
		//todo | gerer le cas ou tout est coller
		if (!line)
		{
			ft_printf("exit\n");
			free(line);
			break ;
		}
		add_history(line);
		get_env(&env, envp);
		good_line = pre_token(line);
		// printf("%s\n", good_line);
		tokenizer(&token, &env, good_line);
		//expand(good_line);
		//todo | malloc a securiser ici
		if (!check_syntax(&token))
		{
			free_token(&token);
			free(line);
			continue ;
		}
		get_cmd(token, &cmd);
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
