/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:44:52 by kjolly            #+#    #+#             */
/*   Updated: 2025/05/19 15:18:38 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sig_c_child_hd(int signals)
{
	(void)signals;
	if (ctrl_c_signal)
	{
		printf("\n");
		close(ctrl_c_signal->fd_hd);
		free_all(ctrl_c_signal);
		free_env(&ctrl_c_signal->env);
		free(ctrl_c_signal);
		rl_clear_history();
	}
	exit (130);	
}

void	handle_sig_c(int signals)
{
	(void)signals;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	if (ctrl_c_signal)
	{
		ctrl_c_signal->exit_code = 130;
		ctrl_c_signal->signal = 0;
	}
}
