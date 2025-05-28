/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzara <tzara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:44:52 by kjolly            #+#    #+#             */
/*   Updated: 2025/05/28 13:20:23 by tzara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// c pour la norme clc
char	*find_path_exec(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->env, "PATH=", 5) == 0)
			return (tmp->env + 5);
		tmp = tmp->next;
	}
	return (NULL);
}

// encore
char	*concat_path(char *path, char *cmd)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full_path);
}

// re
void	token_next(t_data *data, char *tmp)
{
	if (tmp && *tmp)
	{
		compl_token_list(&data->token, tmp);
		free(tmp);
	}
}

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
