/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:32:39 by tzara             #+#    #+#             */
/*   Updated: 2025/05/16 10:53:21 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// !! attention car s'il y a un chiffre apres le $, il ne sera pas oris en compte mais par contre s'il y en a + c'est cuit

void	init_data(t_data **data)
{
	(*data) = malloc(sizeof(t_data));
	if (!(*data))
		exit (1);
	(*data)->cmd = NULL;
	(*data)->env = NULL;
	(*data)->token = NULL;
	(*data)->signal = 0;
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
	//data = malloc(sizeof(t_data));
	init_data(&data);
	ctrl_c_signal = data;
	get_env(&(*data).env, envp);
	// print_env(&(*data).env);
	while (1)
	{
		line = readline(G "minishell> " RST);
		if (!line)
		{
			free_env(&(*data).env);
			free_all(&(*data), NULL, NULL);
			printf("exit\n");
			break ;
		}
		add_history(line);
		good_line = pre_token(line);
		// ?? OPEN_QUOTE
		tokenizer(data, good_line);
		if (!check_syntax(&(*data).token))
		{
			free_token(&(*data).token);
			free(line);
			free(good_line);
			continue ;
		}
		get_cmd((*data).token, &(*data).cmd, &(*data).env, data);
		handle_here_doc((*data).cmd, &(*data).env, data);
		if (data->signal == 130)
		{
			data->signal = 0;
			continue;
		}
		exec_mini(data);
		// print_token(&(*data).token);
		// print_cmd(&(*data).cmd);
		// waitpid();
		// ft_reset_cmd();
		free_all(&(*data), line, good_line);
	}
	free(data);
	rl_clear_history();
	return (0);
}
