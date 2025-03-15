/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzara <tzara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:32:39 by tzara             #+#    #+#             */
/*   Updated: 2025/03/15 12:31:36 by tzara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	if (!data || argc != 1)
		return (-1);
	while (1)
	{
		data->line = readline("minishell> ");
		if (!data->line)
			break ;
		if (data->line[0] != '\0')
			add_history(data->line);
		if (ft_token(data) == 1 && ft_parsing(data) == 1)
			execute();
		// waitpid();
		ft_reset_cmd();
			// remettre tt data a 0 pour la pro cmd    cat | "grep error"
	}
	if (isatty(STDIN_FILENO))
	{
		ft_printf("exit\n");
		rl_clear_history();
		free_all_data();
	}
	return (0);
}
