#include "../../include/minishell.h"

int last_exit_status(int status)
{
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    return (1);
}

void expand(char *line)
{
    int i = 0;
    int j = 0;
    char *value;
    char *var_name;
    int start;
    int len;

    while (line[i])
    {
        if (line[i] == '$')
        {
            i++; // passe le $
            if (line[i] == '?')
            {
                ft_printf("%d\n", last_exit_status); // affiche le code d'exit
                i++;
            }
            else if (line[i] == '$')
            {
                ft_printf("%d\n", getpid()); // $$ affiche le pid
                i++;
            }
            else if (isalnum(line[i])) // si c un char ca veut dire c une variable de env
            {
                start = i; //pour savoir ou commence la variable pour malloc
                while (isalnum(line[i]))
                    i++;
                len = i - start;
                var_name = malloc(sizeof(char) * (len + 1));
                if (!var_name)
                    return ;
                strncpy(var_name, &line[start], len); // copie le nom de la variable
                var_name[j] = '\0';
                value = getenv(var_name); // sensé retourner la valeur de la variable d'environnement
                // todo : parser la variable d'environnement comme pipex 
                // todo : kyllian = neuille supreme
                // todo | theo = suceur
                free(var_name);
                if (value != NULL)
                    ft_printf("%d", value); // affiche la valeur de la variable
            }
            else
                ft_printf("$"); // si c pas une variable d'environnement il prend le $ comme un char
                // j'ai mit des printf pour tester mais il faut les remplacer jpense 
        }
        i++;
    }
}
