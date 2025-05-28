/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:32:39 by tzara             #+#    #+#             */
/*   Updated: 2025/05/28 17:26:16 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_data		*g_ctrl_c_signal = NULL;

static int	init_minishell(int argc, char **envp, t_data **data)
{
	if (argc != 1)
		return (1);
	signal(SIGINT, handle_sig_c);
	signal(SIGQUIT, SIG_IGN);
	init_data(data);
	g_ctrl_c_signal = *data;
	get_env(&(*data)->env, envp);
	return (0);
}

static int	lexer_et_syntax(t_data *data, char *line)
{
	char	*good_line;

	if (!line)
		return (1);
	add_history(line);
	good_line = pre_token(line);
	tokenizer(data, good_line);
	data->line = line;
	data->good_line = good_line;
	if (!check_syntax(&data->token))
	{
		free_all(data);
		return (0);
	}
	return (0);
}

static int	handle_commands(t_data *data)
{
	get_cmd(data->token, &data->cmd, data);
	handle_here_doc(data->cmd, data);
	if (data->signal == 1)
	{
		data->signal = 0;
		data->exit_code = 130;
		free_all(data);
		return (0);
	}
	exec_mini(data);
	free_all(data);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	char	*line;

	(void)argv;
	(void)envp;
	if (init_minishell(argc, envp, &data))
		return (1);
	while (1)
	{
		line = readline(G "minishell> " RST);
		if (!line)
		{
			free_et_exit(data);
			break ;
		}
		if (lexer_et_syntax(data, line))
			continue ;
		handle_commands(data);
	}
	return (0);
}
