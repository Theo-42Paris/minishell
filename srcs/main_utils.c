/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzara <tzara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 22:41:37 by tzara             #+#    #+#             */
/*   Updated: 2025/05/28 13:20:29 by tzara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_data(t_data **data)
{
	(*data) = malloc(sizeof(t_data));
	if (!(*data))
	{
		rl_clear_history();
		exit(1);
	}
	ft_bzero(*data, sizeof(t_data));
}

void	free_et_exit(t_data *data)
{
	free_all(data);
	printf("exit\n");
	free_env(&data->env);
	free(data);
	rl_clear_history();
}

void	handle_sig_quit(int signals)
{
	(void)signals;
}
