/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:32:39 by tzara             #+#    #+#             */
/*   Updated: 2025/04/16 16:13:28 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	signal(SIGINT, handle_sig_c);// ctrl-C
	signal(SIGQUIT, SIG_IGN);// ctrl-\"
	get_env(&env, envp);
	while (1)
	{
		line = readline(G "minishell> " RST);
		if (!line)
		{
			ft_printf("exit\n");
			free_env(&env);
			break ;
		}
		add_history(line);
		good_line = pre_token(line);
		tokenizer(&token, good_line);
		if (!check_syntax(&token))
		{
			free_token(&token);
			free(line);
			free(good_line);
			continue ;
		}
		get_cmd(token, &cmd);
		handle_here_doc(cmd, &env);
		// print_token(&token);
		print_cmd(&cmd);
		// waitpid();
		// ft_reset_cmd();
		free_token(&token);
		free_env(&env);
		free_cmd(&cmd);
		free(good_line);
		free(line);
	}
	rl_clear_history();
	return (0);
}
