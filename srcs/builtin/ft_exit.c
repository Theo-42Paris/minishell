/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:32:28 by tzara             #+#    #+#             */
/*   Updated: 2025/05/02 11:26:53 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// todo | si exit sans rien quitte avec le dernier code de retour
// todo | si exit avec un nombre exit 42 quitte avec le code 42
// todo | si exit avec des lettre "abc" quitte avec le code 2 et write "numeric arg required"
// todo | si exit avec plus de 1 arg == write "too many arguments" et ne quitte pas

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

int	ft_exit(t_data *data, t_cmd *cmd)
{
	long	exit_code;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (ft_count_args(cmd) > 2)
	{
		write(1, "Minishell: exit: too many arguments\n", 37);
		return (1);
	}
	write(1, "exit\n", 5);
	if (ft_count_args(cmd) == 1)
		exit(data->signal);
	if (!ft_isnumber(cmd->args[1]))
	{
		write(2, "minishell: exit: numeric argument required\n", 43);
		// ft_free_all(data);
		exit(2);
	}
	exit_code = ft_atoll(cmd->args[1]) % 256; 
	// ft_free_all(data);
	exit(exit_code);
}
