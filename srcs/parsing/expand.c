#include "../../include/minishell.h"

// int get_len_src(char *src)
// {
// 	int i;
// 	int	len;

// 	i = 0;
// 	len = 0;
// 	while (src[i])
// 	{
// 		if (src[i] == '$')
// 			while (src[i] && src[i] != ' ' && src[i] != '\t')
// 				i++;
// 		len++;
// 		i++;
// 	}
// 	return (len);
// }


char	*find_path(t_env **env, char *tmp)
{
	t_env	*env_tmp;

	env_tmp = *env;
	while (env_tmp)
	{
		if (ft_strncmp(env_tmp->env, tmp, ft_strlen(tmp)) == 0 
			&& env_tmp->env[ft_strlen(tmp)] == '=')
			return (env_tmp->env + ft_strlen(tmp) + 1);
		env_tmp = env_tmp->next;
	}
	return (NULL);
}

char	*get_expand(int len_src, char *tmp, char *src, t_env **env)
{
	char	*env_find;
	char	*good_line;
	int 	i = 0;
	int		j = 0;
	int		k = 0;

	env_find = find_path(env, tmp); //kjolly
	if (!env_find)
		return (ft_strdup(""));
	good_line = malloc(sizeof(char) * (len_src + ft_strlen(env_find)) + 1);
	if (!good_line)
		return (NULL);
	while (src[i])
	{
		if (src[i] == '$')
		{
			i++;
			while (env_find[k])
				good_line[j++] = env_find[k++];
			while (src[i] && src[i] != ' ' &&  src[i] != '\t')
				i++;
		}
		if (src[i])
			good_line[j++] = src[i++];
	}
	good_line[j] = '\0';
	return (good_line);
}

int	size_of_var(char *src)
{
	int i;
	int	len;

	i = 0;
	len = 0;
	while (src[i])
	{
		if (src[i] == '$')
		{
			i++;
			while (src[i] && src[i] != ' ' && src[i] != '\t')
			{
				len++;
				i++;
			}
		}
		i++;
	}
	return (len);
}

char	*one_expand(char *src, t_env **env)
{
	char	*exp;
	char	*tmp;
	int		len_src;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(char) * size_of_var(src) + 1);
	if (!tmp)
		return (NULL);
	while (src[i])
	{
		if (src[i] == '$')
		{
			i++;
			while (src[i] && src[i] != ' ' && src[i] !='\t')
				tmp[j++] = src[i++];
		}
		i++;
	}
	tmp[j] = '\0';
	len_src = i - j;
	exp = get_expand(len_src, tmp, src, env);
	if (!exp)
		return (NULL);
	return (exp);
}

char	*make_beleck(/*int status_exp, */char *src, t_env **env/*, int count*/)
{
	char	*final;

	// if (count == 1)
	// {
		final = one_expand(src, env);
		if (!final)
			return (NULL);
	// }
	// else
	// {
	// 	final = multi_expand(src, env);
	// 	if (!final)
	// 		return (NULL);
	// }
	return (final);
}

char	*handle_expand(char	*src, t_env **env)
{
	// ? src = current_word
	// todo | fusioner src et le resultat de get_env
	int		i = 0;
	int		count = 0;
	int		status_exp;
	char	*beleck;

	while (src[i])
	{
		if (src[i] == '$')
		{
			if (src[i + 1] == '?')
				status_exp = 2;
			else if (src[i + 1] != ' ' && src[i + 1] != '\t') //ca veux dire c un char
				status_exp = 1;
			count++;
		}
		i++;
	}
	if (count == 0)
		return (src);
	beleck = make_beleck(src, env);
	return (beleck);
}

// int last_exit_status(int status)
// {
//     if (WIFEXITED(status))
//         return (WEXITSTATUS(status));
//     return (1);
// }

// void expand(char *line)
// {
//     int i = 0;
//     int j = 0;
//     char *value;
//     char *var_name;
//     int start;
//     int len;

//     while (line[i])
//     {
//         if (line[i] == '$')
//         {
//             i++; // passe le $
//             if (line[i] == '?')
//             {
//                 ft_printf("%d\n", last_exit_status); // affiche le code d'exit
//                 i++;
//             }
//             else if (line[i] == '$')
//             {
//                 ft_printf("%d\n", getpid()); // $$ affiche le pid
//                 i++;
//             }
//             else if (isalnum(line[i])) // si c un char ca veut dire c une variable de env
//             {
//                 start = i; //pour savoir ou commence la variable pour malloc
//                 while (isalnum(line[i]))
//                     i++;
//                 len = i - start;
//                 var_name = malloc(sizeof(char) * (len + 1));
//                 if (!var_name)
//                     return ;
//                 strncpy(var_name, &line[start], len); // copie le nom de la variable
//                 var_name[j] = '\0';
//                 value = getenv(var_name); // sensé retourner la valeur de la variable d'environnement
//                 // todo : parser la variable d'environnement comme pipex 
//                 // todo : kyllian = neuille supreme
//                 // todo | theo = suceur
//                 free(var_name);
//                 if (value != NULL)
//                     ft_printf("%d", value); // affiche la valeur de la variable
//             }
//             else
//                 ft_printf("$"); // si c pas une variable d'environnement il prend le $ comme un char
//                 // j'ai mit des printf pour tester mais il faut les remplacer jpense 
//         }
//         i++;
//     }
// }

// int	final_len_exp(char *str)
// {
// 	int	i;
// 	int	len;tmp[j++] 

// 	i = 0;
// 	len = 0;
// 	while (str[i] && str[i] != '=')
// 		i++;
// 	if (str[i] == '=')
// 		i++;
// 	while (str[i])
// 	{
// 		len++;
// 		i++;
// 	}
// 	return (len);
// }

// int	get_len_expand(char *src, t_env **env)
// {
// 	int		i;
// 	int		j;
// 	int		stat;
// 	int		count;
// 	char	*dst;
// 	t_env	*tmp;

// 	i = 0;
// 	j = 0;
// 	count = 0;
// 	stat = 0;
// 	dst = NULL;
// 	tmp = *env;
// 	while (src[i] && src[i] != '$')
// 		i++;
// 	if (src[i] == '$')
// 		i++;
// 	stat = i;
// 	while (src[i] && (src[i] != ' ' && src[i] != '\t'))
// 	{
// 		count++;
// 		i++;
// 	}
// 	dst = malloc(sizeof(char) * (count + 1));
// 	if (!dst)
// 		return (0);
// 	while (src[i] && (src[i] != ' ' && src[i] != '\t'))
// 		dst[j++] = src[stat++];
// 	dst[j] = '\0';
//     while (tmp)
// 	{
// 		if (ft_strncmp(dst, tmp->env, ft_strlen(dst)) == 0)
// 			return (final_len_exp(tmp->env));
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }

// int	cmp_env(char *env, char *new_env)
// {
// 	int i;

// 	i = 0;
// 	while (env[i] && new_env[i] && env[i] == new_env[i])	
// 		i++;
// 	return (env[i] - new_env[i]);
// }

// char	*line_with_expand(char *src, int *len, t_env **env)
// {
// 	int		i;
// 	int		j;
// 	int		k;
// 	int		len2 = 0;
// 	char	*new_expand;
// 	t_env	*tmp;

// 	tmp = *env;
// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	len2 = get_len_expand(src, env);
// 	new_expand = malloc(sizeof(char) * (((*len) + len2) + 1));
// 	if (!new_expand)
// 		return (NULL);
// 	while (src[i] && src[i] != '$')
// 		new_expand[j++] = src[i++];
// 	if (src[i] == '$')
// 	{
// 		i++;
// 		while (tmp)
// 		{
// 			if (cmp_env(&src[i], tmp->env) == 0)
// 				break;
// 			tmp = tmp->next;
// 		}
// 		while (tmp && tmp->env[k] && tmp->env[k] != '=')
// 			k++;
// 		while (tmp->env[k])
// 		new_expand[j++] = tmp->env[k++];
// 		while (src[i] && (src[i] != ' ' && src[i] != '\t'))
// 			i++;
// 		if (src[i])
// 		{
// 			while (src[i])
// 			{
// 				new_expand[j++] = src[i++];
// 			}
// 		}
// 	}
// 	new_expand[j] = '\0';
// 	return (new_expand);
// }

// char	*handle_expand(char	*src, t_env **env)
// {
// 	int		len = 0;
// 	int		i = 0;
// 	char	*expand;

// 	while (src[i] && src[i] != '$')
// 	{
// 		len++;
// 		i++;
// 	}
// 	if (src[i] == '$')
// 	{
// 		while (src[i] && (src[i] != ' ' && src[i] != '\t'))
// 			i++;
// 		if (src[i])
// 		{
// 			while (src[i])
// 			{
// 				len++;
// 				i++;
// 			}
// 		}
// 		expand = line_with_expand(src, &len, env);
// 		free(src);
// 		if (!expand)
// 			return (NULL);
// 		return (expand);
// 	}
// 	else
// 		return (src);
// }
