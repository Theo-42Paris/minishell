/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzara <tzara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:25:36 by tzara             #+#    #+#             */
/*   Updated: 2025/05/20 12:27:46 by tzara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_pwd(t_cmd *cmd)
{
	char	*cwd;

	if (!cmd->args || !cmd->args[0])
		return (1);
	if (cmd->args[1] && ft_is_option(cmd->args[1]))
		return (ft_putstr_fd("minishell: pwd: options are not allowed\n", 2),
			2);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_putstr_fd("minishell: ", 2), perror(cmd->args[0]), 1);
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
	free(cwd);
	return (0);
}
