/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzara <tzara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:25:36 by tzara             #+#    #+#             */
/*   Updated: 2025/04/16 16:27:21 by tzara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_pwd(t_cmd *cmd)
{
	char	*cwd;
	t_cmd	*arg;

	if (!cmd || !cmd->cmd)
		return (1);
	arg = cmd;
	if (arg->next && ft_is_option(arg->next->cmd))
		return (ft_putstr_fd("minishell: pwd: options are not allowed\n", 2),
			2);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_putstr_fd("minishell: ", 2), perror(arg->cmd), 1);
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
	free(cwd);
	return (0);
}
