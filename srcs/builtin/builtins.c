/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzara <tzara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:26:18 by tzara             #+#    #+#             */
/*   Updated: 2025/04/10 15:36:28 by tzara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_isbuiltin(t_cmd *cmd)
{
	char	*str;

	if (!cmd || !cmd->value)
		return (1);
	str = cmd->value;
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
	if (!data || !cmd || !cmd->value)
		return (1);
	if (ft_strlen(cmd->value) == 0)
	{
		ft_putstr_fd("Minishell : cmd not found\n", 2);
		return (1);
	}
	if (ft_strcmp(cmd->value, "pwd") == 0)
		return (ft_pwd(cmd));
	// if (ft_strcmp(cmd->value, "env") == 0)
	// 	return (ft_print_env(data));
	// if (ft_strcmp(cmd->value, "cd") == 0)
	// 	return (ft_cd(data->env, cmd));
	if (ft_strcmp(cmd->value, "echo") == 0)
		return (ft_echo(data, cmd));
	// if (ft_strcmp(cmd->value, "export") == 0)
	// 	return (ft_export(data, cmd));
	// if (ft_strcmp(cmd->value, "unset") == 0)
	// 	return (ft_unset(data, cmd));
	// if (ft_strcmp(cmd->value, "exit") == 0)
	// 	return (ft_exit(data, cmd));
	return (1);
}
