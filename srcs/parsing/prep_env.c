/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzara <tzara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 14:08:09 by kjolly            #+#    #+#             */
/*   Updated: 2025/05/20 12:26:52 by tzara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

void	fill_env(char *envp, t_env **env)
{
	t_env	*new;
	t_env	*last;

	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->env = ft_strdup(envp);
	if (!new->env)
	{
		free(new);
		return ;
	}
	new->next = NULL;
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
