/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:32:39 by tzara             #+#    #+#             */
/*   Updated: 2025/05/17 16:31:54 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// ?? probleme si ligne vide, ' ' ou '\t', problemem avec certains builtin : echo, pwd, env, exit

void	init_data(t_data **data)
{
	(*data) = malloc(sizeof(t_data));
	if (!(*data))
	{
		rl_clear_history();
		exit (1);
	}
	ft_bzero(*data, sizeof(t_data));
}

t_data *ctrl_c_signal = NULL;

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	char	*line;
	char	*good_line;

	(void)argv;
	(void)envp;
	if (argc != 1)
		return (1);
	signal(SIGINT, handle_sig_c);// ctrl-C
	signal(SIGQUIT, SIG_IGN);// ctrl-\"
	init_data(&data);
	ctrl_c_signal = data;
	get_env(&(*data).env, envp);
	while (1)
	{
		line = readline(G "minishell> " RST);
		if (!line)
		{
			free_all(&(*data));
			printf("exit\n");
			break ;
		}
		add_history(line);
		good_line = pre_token(line);
		// ?? OPEN_QUOTE
		tokenizer(data, good_line);
		if (!check_syntax(&(*data).token))
		{
			free_all(data);
			continue ;
		}
		data->line = line;
		data->good_line = good_line;
		get_cmd((*data).token, &(*data).cmd, data);
		handle_here_doc((*data).cmd, data);
		if (data->signal == 1)
		{
			data->signal = 0;
			data->exit_code = 130;
			free_all(&(*data));
			continue;
		}
		exec_mini(data);
		// print_token(&(*data).token);
		// print_cmd(&(*data).cmd);
		// waitpid();
		// ft_reset_cmd();
		free_all(&(*data));
	}
	free_env(&data->env);
	free(data);
	rl_clear_history();
	return (0);
}
