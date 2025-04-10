/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzara <tzara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:32:39 by tzara             #+#    #+#             */
/*   Updated: 2025/04/10 15:32:18 by tzara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <signal.h>

// #define BUF_SIZE 1024

// void	read_fd(int fd)
// {
// 	char	buffer[BUF_SIZE + 1];
// 	ssize_t	bytes_read;

// 	while ((bytes_read = read(fd, buffer, BUF_SIZE)) > 0)
// 	{
// 		buffer[bytes_read] = '\0';
// 		printf("%s", buffer); // ou write(1, buffer, bytes_read);
// 	}
// }

void	handle_sig_c(int signals)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void)signals;
}

int	main(int argc, char **argv, char **envp)
{
	t_token	*token;
	t_cmd	*cmd;
	t_env	*env;
	char	*line;
	char	*good_line;

	(void)argv;
	(void)envp;
	token = NULL;
	cmd = NULL;
	env = NULL;
	if (argc != 1)
		return (1);
	signal(SIGINT, handle_sig_c); // ctrl-C
	signal(SIGQUIT, SIG_IGN);     // ctrl-\"
	while (1)
	{
		line = readline(G "minishell> " RST);
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
		handle_here_doc(cmd, &env);
		// print_token(&token);
		// print_cmd(&cmd);
		// waitpid();
		// ft_reset_cmd();
		free_token(&token);
		free_cmd(&cmd);
	}
	return (0);
}
