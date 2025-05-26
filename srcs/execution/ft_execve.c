/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:31:37 by kjolly            #+#    #+#             */
/*   Updated: 2025/05/26 12:23:21 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_ligne(t_data *data, t_exec *mini, char *path)
{
	free(mini->pidarray);
	free(path);
	free_all(data);
	data->exit_code = 1;
	rl_clear_history();
	exit(1);
}

void	do_execve_bonus(t_exec *mini, t_cmd *tmp_cmd, char *path, t_data *data)
{
	char	**exec_env;
	int		ex;

	exec_env = env_for_exec((*data).env);
	if (!exec_env)
	{
		ft_putstr_fd("malloc error: environment setup failed\n", 2);
		ft_ligne(data, mini, path);
	}
	if (execve(path, tmp_cmd->args, exec_env) == -1)
	{
		free(mini->pidarray);
		free_str(exec_env);
		perror(tmp_cmd->args[0]);
		if (access(path, F_OK) == -1)
		{
			ex = 127;
			free_bonus_ex(data, ex, path);
		}
		else
		{
			ex = 126;
			free_bonus_ex(data, ex, path);
		}
	}
}

static void	ft_cmd_nul(t_data *data, t_exec *mini)
{
	data->exit_code = 0;
	free_exec(data, mini);
	exit(0);
}

void	ft_ligne_builtin(int ret, t_data *data, t_exec *mini, t_cmd *tmp_cmd)
{
	ret = ft_exec_builtin(data, tmp_cmd, mini);
	data->exit_code = ret;
	free_exec(data, mini);
	exit(ret);
}

void	exec(t_exec *mini, t_cmd *tmp_cmd, t_data *data)
{
	char	*path;
	int		ret;

	ret = 0;
	path = NULL;
	if (is_builtin(tmp_cmd))
		ft_ligne_builtin(ret, data, mini, tmp_cmd);
	if (!tmp_cmd->args[0] || tmp_cmd->args[0][0] == '\0')
		ft_cmd_nul(data, mini);
	if (ft_strchr(tmp_cmd->args[0], '/'))
		path = ft_strdup(tmp_cmd->args[0]);
	else
	{
		path = get_path(tmp_cmd->args[0], data->env);
		if (!path)
		{
			ft_putstr_fd("command not found: ", 2);
			ft_putendl_fd(tmp_cmd->args[0], 2);
			data->exit_code = 127;
			free_exec(data, mini);
			exit(127);
		}
	}
	do_execve_bonus(mini, tmp_cmd, path, data);
}
