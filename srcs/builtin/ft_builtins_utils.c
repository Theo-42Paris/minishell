/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzara <tzara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:18:35 by tzara             #+#    #+#             */
/*   Updated: 2025/05/20 15:23:38 by tzara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_is_option(char *str)
{
	if (!str || ft_strcmp(str, "--") == 0 || ft_strcmp(str, "-") == 0)
		return (0);
	if (*str == '-' && *(str + 1) != '\0')
		return (1);
	return (0);
}

int	ft_env(t_env *env)
{
	while (env)
	{
		if (ft_strchr(env->env, '='))
			ft_putendl_fd(env->env, 1);
		env = env->next;
	}
	return (0);
}

void	ft_pwd_lignes(char *pwd, t_env **env)
{
	if (pwd)
	{
		process_export_arg(pwd, env);
		free(pwd);
	}
}
