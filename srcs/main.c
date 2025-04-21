/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:32:39 by tzara             #+#    #+#             */
/*   Updated: 2025/04/21 16:28:43 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// !! attention car s'il y a un chiffre apres le $, il ne sera pas oris en compte mais par contre s'il y en a + c'est cuit
// ? histoire-geo, niveau 6eme chapitre 1 : le croissant fertile

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
	data = malloc(sizeof(t_data));
	get_env(&(*data).env, envp);
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
		tokenizer(&(*data).token, good_line);
		if (!check_syntax(&(*data).token))
		{
			free_token(&(*data).token);
			free(line);
			free(good_line);
			continue ;
		}
		get_cmd((*data).token, &(*data).cmd, &(*data).env);
		handle_here_doc((*data).cmd, &(*data).env);
		exec_mini(data);
		// print_token(&(*data).token);
		// print_cmd(&(*data).cmd);
		// waitpid();
		// ft_reset_cmd();
		free_all(&(*data), line, good_line);
	}
	rl_clear_history();
	return (0);
}
