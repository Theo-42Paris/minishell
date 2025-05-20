/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzara <tzara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:44:52 by kjolly            #+#    #+#             */
/*   Updated: 2025/05/20 12:33:02 by tzara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sig_c_child_hd(int signals)
{
	(void)signals;
	if (g_ctrl_c_signal)
	{
		printf("\n");
		close(g_ctrl_c_signal->fd_hd);
		free_all(g_ctrl_c_signal);
		free_env(&g_ctrl_c_signal->env);
		free(g_ctrl_c_signal);
		rl_clear_history();
	}
	exit(130);
}

void	handle_sig_c(int signals)
{
	(void)signals;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	if (g_ctrl_c_signal)
	{
		g_ctrl_c_signal->exit_code = 130;
		g_ctrl_c_signal->signal = 0;
	}
}
