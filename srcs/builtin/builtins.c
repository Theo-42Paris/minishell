/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzara <tzara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:26:18 by tzara             #+#    #+#             */
/*   Updated: 2025/05/20 15:18:18 by tzara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (ft_strcmp(cmd->args[0], "cd") == 0 || ft_strcmp(cmd->args[0],
			"echo") == 0 || ft_strcmp(cmd->args[0], "pwd") == 0
		|| ft_strcmp(cmd->args[0], "export") == 0 || ft_strcmp(cmd->args[0],
			"unset") == 0 || ft_strcmp(cmd->args[0], "env") == 0
		|| ft_strcmp(cmd->args[0], "exit") == 0)
		return (1);
	return (0);
}

int	child_builtin(t_cmd *cmd)
{
	char	*str;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	str = cmd->args[0];
	if (ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "pwd") == 0
		|| ft_strcmp(str, "env") == 0)
		return (1);
	return (0);
}

int	parent_builtin(t_cmd *cmd)
{
	char	*str;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	str = cmd->args[0];
	if (ft_strcmp(str, "cd") == 0 || ft_strcmp(str, "export") == 0
		|| ft_strcmp(str, "unset") == 0 || ft_strcmp(str, "exit") == 0)
		return (1);
	return (0);
}

int	ft_exec_builtin(t_data *data, t_cmd *cmd, t_exec *mini)
{
	if (!data || !cmd || !cmd->args)
		return (1);
	if (ft_strlen(cmd->args[0]) == 0)
	{
		ft_putstr_fd("Minishell : cmd not found\n", 2);
		return (1);
	}
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (ft_pwd(cmd));
	if (ft_strcmp(cmd->args[0], "env") == 0)
		return (ft_env(data->env));
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (ft_cd(data->env, cmd));
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (ft_echo(cmd));
	if (ft_strcmp(cmd->args[0], "export") == 0)
		return (ft_export(data->cmd->args, &data->env));
	if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (ft_unset(cmd->args, &data->env));
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (ft_exit(data, cmd, mini));
	return (1);
}
