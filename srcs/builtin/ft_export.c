/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzara <tzara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:19:18 by tzara             #+#    #+#             */
/*   Updated: 2025/04/22 16:17:24 by tzara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*find_env_var(char *arg, t_env *env)
{
	int	name_len;

	name_len = 0;
	while (arg[name_len] && arg[name_len] != '=')
		name_len++;
	while (env)
	{
		if (ft_strncmp(env->env, arg, name_len) == 0 && env->env[name_len] == '=')
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	add_or_update_env(char *arg, t_env **env_ptr)
{
	t_env	*found;
	t_env	*new_node;
	t_env	*tmp;

	found = find_env_var(arg, *env_ptr);
	if (found) //si la var existe deja
	{
		free(found->env); // free l'ancienne version
		found->env = ft_strdup(arg); //on copie la nv
		return (found->env == NULL);
	}
	new_node = malloc(sizeof(t_env)); //si il existe pas on le cree 
	if (!new_node)
		return (1);
	new_node->env = ft_strdup(arg); //met la valuer de arg en tant que valeur de new node
	if (!new_node->env)
	{
		free(new_node);
		return (1);
	}
	new_node->next = NULL; //si la liste est vide (env -i)
	if (!*env_ptr)
		*env_ptr = new_node;
	else //sinon on l'ajoute a la fin
	{
		tmp = *env_ptr;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
	return (0);
}

int	process_export_arg(char *arg, t_env **env_ptr)
{
	int		len;
	int		ret;
	char	*tmp;

	if (!is_valid_identifier(arg))
	{
		print_export_error(arg);
		return (1);
	}
	if (!ft_strchr(arg, '=')) //si ya pas de = 
	{
		len = ft_strlen(arg);
		tmp = malloc(len + 1);
		if (!tmp)
			return (1);
		ft_strcpy(tmp, arg);
		tmp[len] = '\0';
		ret = add_or_update_env(tmp, env_ptr);
		free(tmp);
		return (ret);
	}
	return (add_or_update_env(arg, env_ptr)); //si ya un =
}

// todo | a trier dans l'odre alhabetique de con AAAAAAAAHHHHHH
int	print_env_list(t_env *env)
{
	while (env)
	{
		write(1, "export ", 8);
		write(1, env->env, ft_strlen(env->env));
		write(1, "\n", 1);
		env = env->next;
	}
	return (0);
}

int	ft_export(char **args, t_env **env_ptr)
{
	int	i;
	int	exit_code;

	if (args[1] == NULL)
		return (print_env_list(*env_ptr));
	i = 1;
	exit_code = 0;
	while (args[i])
	{
		if (process_export_arg(args[i], env_ptr) != 0)
			exit_code = 1;
		i++;
	}
	return (exit_code);
}
