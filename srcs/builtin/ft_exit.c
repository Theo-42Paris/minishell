/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzara <tzara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:32:28 by tzara             #+#    #+#             */
/*   Updated: 2025/05/20 16:01:39 by tzara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void		ft_non_numeric_exit(t_data *data, t_exec *mini, t_cmd *cmd);
void		free_exit(t_data *data, t_exec *mini);

static int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_count_args(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i])
		i++;
	return (i);
}

int	ft_exit(t_data *data, t_cmd *cmd, t_exec *mini)
{
	long	exit_code;
	int		temp_e;

	exit_code = 0;
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (ft_count_args(cmd) > 2)
	{
		write(1, "Minishell: exit: too many arguments\n", 37);
		return (1);
	}
	write(1, "exit\n", 5);
	if (ft_count_args(cmd) == 1)
	{
		temp_e = data->exit_code;
		free_exit(data, mini);
		exit(temp_e);
	}
	ft_non_numeric_exit(data, mini, cmd);
	exit_code = ft_atoll(cmd->args[1]) % 256;
	free_exit(data, mini);
	exit(exit_code);
}

void	ft_non_numeric_exit(t_data *data, t_exec *mini, t_cmd *cmd)
{
	if (!ft_isnumber(cmd->args[1]))
	{
		write(2, "minishell: exit: numeric argument required\n", 43);
		free_exit(data, mini);
		exit(2);
	}
}

void	free_exit(t_data *data, t_exec *mini)
{
	free_all(data);
	free_env(&data->env);
	free(mini->pidarray);
	free(data);
	rl_clear_history();
}
