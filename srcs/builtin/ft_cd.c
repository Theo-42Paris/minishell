/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzara <tzara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 09:30:56 by tzara             #+#    #+#             */
/*   Updated: 2025/05/20 15:23:03 by tzara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_pwd_env(t_env **env)
{
	char	*cwd;
	char	*old_pwd;
	char	*pwd;
	t_env	*pwd_env;

	pwd_env = find_env_var("PWD=", *env);
	if (pwd_env)
		old_pwd = ft_strjoin("OLDPWD=", pwd_env->env + 4);
	else
		old_pwd = ft_strdup("OLDPWD=");
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		free(old_pwd);
		return ;
	}
	pwd = ft_strjoin("PWD=", cwd);
	free(cwd);
	if (old_pwd)
	{
		process_export_arg(old_pwd, env);
		free(old_pwd);
	}
	ft_pwd_lignes(pwd, env);
}

int	cd_to_home(t_env *env)
{
	char	*home_path;
	t_env	*home_env;
	int		ret;

	home_env = find_env_var("HOME=", env);
	if (!home_env)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	home_path = home_env->env + 5;
	ret = chdir(home_path);
	if (ret == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(home_path);
		return (1);
	}
	return (0);
}

int	cd_to_previous(t_env *env)
{
	t_env	*old_env;
	char	*old_path;
	int		move;

	old_env = find_env_var("OLDPWD=", env);
	if (!old_env)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (1);
	}
	old_path = old_env->env + 7;
	move = chdir(old_path);
	if (move == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(old_path);
		return (1);
	}
	ft_putendl_fd(old_path, 1);
	return (0);
}

int	cd_to_path(char *path)
{
	int	ret;

	ret = chdir(path);
	if (ret == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(path);
		return (1);
	}
	return (0);
}

int	ft_cd(t_env *env, t_cmd *cmd)
{
	int	ret;

	if (!cmd->args[1] || ft_strcmp(cmd->args[1], "~") == 0)
		ret = cd_to_home(env);
	else if (ft_strcmp(cmd->args[1], "-") == 0)
		ret = cd_to_previous(env);
	else
		ret = cd_to_path(cmd->args[1]);
	if (ret == 0)
		update_pwd_env(&env);
	return (ret);
}
