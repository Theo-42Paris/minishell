/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:26:18 by tzara             #+#    #+#             */
/*   Updated: 2025/04/21 16:33:38 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_isbuiltin(t_cmd *cmd)
{
	char	*str;

	if (!cmd || !cmd->args[0])
		return (0);
	str = cmd->args[0];
	if (ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "cd") == 0
		|| ft_strcmp(str, "pwd") == 0 || ft_strcmp(str, "export") == 0
		|| ft_strcmp(str, "unset") == 0 || ft_strcmp(str, "env") == 0
		|| ft_strcmp(str, "exit") == 0)
		return (1);
	return (0);
}

int	ft_is_option(char *str)
{
	if (!str || ft_strcmp(str, "--") == 0 || ft_strcmp(str, "-") == 0)
		return (0);
	if (*str == '-' && *(str + 1) != '\0')
		return (1);
	return (0);
}

int	ft_exec_builtin(t_data *data, t_cmd *cmd)
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
	// if (ft_strcmp(cmd->cmd, "env") == 0)
	// 	return (ft_print_env(data));
	// if (ft_strcmp(cmd->cmd, "cd") == 0)
	// 	return (ft_cd(data->env, cmd));
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (ft_echo(cmd));
	// if (ft_strcmp(cmd->cmd, "export") == 0)
	// 	return (ft_export(cmd));
	// if (ft_strcmp(cmd->cmd, "unset") == 0)
	// 	return (ft_unset(cmd));
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (ft_exit(data, cmd));
	return (1);
}
