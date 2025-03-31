/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjolly <kjolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 14:08:09 by kjolly            #+#    #+#             */
/*   Updated: 2025/03/31 09:24:13 by kjolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*new_env(char *envp)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->env = ft_strdup(envp);
	env->next = NULL;
	return (env);
}

t_env	*last_env(t_env *env)
{
	while (env)
	{
		if (env->next == NULL)
			return (env);
		env = env->next;
	}
	return (env);
}

void	add_env(t_env **env, t_env *new)
{
	t_env	*last;

	if (env)
	{
		if (*env)
		{
			last = last_env(*env);
			last->next = new;
		}
		else
			*env = new;
	}
}

void	fill_env(char *envp, t_env **env)
{
	t_env *new;

	new = new_env(envp);
	if (!new)
		return ;
	add_env(env, new);
}

void	get_env(t_env **env, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		fill_env(envp[i], env);
		i++;
	}
}
