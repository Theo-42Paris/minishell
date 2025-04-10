/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzara <tzara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:23:00 by tzara             #+#    #+#             */
/*   Updated: 2025/04/10 15:36:21 by tzara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_valid_n_option(char *str)
{
	int	i;

	if (!str || str[0] != '-')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_data *data, t_cmd *cmd)
{
	t_cmd	*arg;
	int		newline;

	(void)data;
	arg = cmd->next;
	newline = 1;
	while (arg && is_valid_n_option(arg->value))
	{
		newline = 0;
		arg = arg->next;
	}
	while (arg)
	{
		ft_putstr_fd(arg->value, 1);
		if (arg->next)
			ft_putstr_fd(" ", 1);
		arg = arg->next;
	}
	if (newline)
		ft_putstr_fd("\n", 1);
	return (0);
}
