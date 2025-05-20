/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzara <tzara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:16:45 by tzara             #+#    #+#             */
/*   Updated: 2025/05/20 12:27:51 by tzara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	swap_str(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	sort_env_array(char **env_array, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp(env_array[i], env_array[j]) > 0)
				swap_str(&env_array[i], &env_array[j]);
			j++;
		}
		i++;
	}
}

char	**create_env_array(t_env *env, int size)
{
	char	**env_array;
	int		i;

	i = 0;
	env_array = malloc(sizeof(char *) * (size + 1));
	if (!env_array)
		return (NULL);
	while (env)
	{
		env_array[i++] = env->env;
		env = env->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

void	print_export_line(char *env_line)
{
	char	*equal_sign;
	int		var_len;

	equal_sign = ft_strchr(env_line, '=');
	if (equal_sign)
	{
		var_len = equal_sign - env_line;
		write(1, env_line, var_len + 1);
		write(1, "\"", 1);
		write(1, equal_sign + 1, ft_strlen(equal_sign + 1));
		write(1, "\"\n", 2);
	}
	else
	{
		write(1, env_line, ft_strlen(env_line));
		write(1, "\n", 1);
	}
}

void	print_env_array(char **env_array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		write(1, "export ", 7);
		print_export_line(env_array[i]);
		i++;
	}
}
