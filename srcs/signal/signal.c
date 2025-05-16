/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:44:52 by kjolly            #+#    #+#             */
/*   Updated: 2025/05/16 12:50:05 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void handle_sig_c(int signals)
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
