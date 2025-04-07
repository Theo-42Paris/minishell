#include "../../include/minishell.h"

int	final_len_exp(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		i++;
	while (str[i])
	{
		len++;
		i++;
	}
	return (len);
}

int	get_len_expand(char *src, t_env **env)
{
	int		i;
	int		j;
	char	*dst;
	t_env	*tmp;

    printf("je suis la4\n");
	i = 0;
	j = 0;
	dst = NULL;
	tmp = *env;
	while (src[i] && src[i] != '$')
		i++;
	if (src[i] == '$')
		i++;
    printf("je suis la5\n");
	while (src[i] && (src[i] != ' ' && src[i] != '\t'))
    // ! PROBLEME !!!!
		dst[j++] = src[i++];
    while (tmp)
	{
		if (ft_strncmp(dst, tmp->env, ft_strlen(dst)) == 0)
			return (final_len_exp(tmp->env));
		tmp = tmp->next;
	}
	return (0);
}

int	cmp_env(char *env, char *new_env)
{
	int i;

	i = 0;
	while (env[i] && new_env[i] && env[i] == new_env[i])	
		i++;
	return (env[i] - new_env[i]);
}

char	*line_with_expand(char *src, int *len, t_env **env)
{
	int		i;
	int		j;
	int		k;
	int		len2;
	char	*new_expand;
	t_env	*tmp;

	tmp = *env;
	i = 0;
	j = 0;
	k = 0;
    printf("je suis la3\n");
	len2 = get_len_expand(src, env);
	new_expand = malloc(sizeof(char) * ((*len) + len2) + 1);
	if (!new_expand)
		return (NULL);
	while (src[i] && src[i] != '$')
		new_expand[j++] = src[i++];
	if (src[i] == '$')
	{
		i++;
		while (tmp)
		{
			if (cmp_env(&src[i], tmp->env) == 0)
				break;
			tmp = tmp->next;
		}
		while (tmp && tmp->env[k] && tmp->env[k] != '=')
			k++;
		while (tmp->env[k])
		new_expand[j++] = tmp->env[k++];
		while (src[i] && (src[i] != ' ' && src[i] != '\t'))
			i++;
		if (src[i])
		{
			while (src[i])
			{
				new_expand[j++] = src[i++];
			}
		}
	}
	new_expand[j] = '\0';
	return (new_expand);
}

char	*handle_expand(char	*src, t_env **env)
{
	int		len = 0;
	int		i = 0;
	char	*expand;

	while (src[i] && src[i] != '$')
	{
		len++;
		i++;
	}
	if (src[i] == '$')
	{
		while (src[i] && (src[i] != ' ' && src[i] != '\t'))
			i++;
		if (src[i])
		{
			while (src[i])
			{
				len++;
				i++;
			}
		}
        printf("je suis la2\n");
		expand = line_with_expand(src, &len, env);
		free(src);
		if (!expand)
			return (NULL);
		return (expand);
	}
	else
		return (src);
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
