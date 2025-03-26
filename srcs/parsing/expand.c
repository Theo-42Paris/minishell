#include "../../include/minishell.h"

//status recup avec waitpid
int last_exit_status(int status)
{
    
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
                printf("%d\n", last_exit_status);
                i++;
            }
            else if (line[i] == '$')
            {
                printf("%d", getpid());
                i++;
            }
            else if (isalnum(line[i]))
            {
                start = i;
                while (isalnum(line[i]))
                    i++;
                len = i - start;
                var_name = malloc(sizeof(char) * (len + 1));
                if (!var_name)
                    return ;
                strncpy(var_name, &line[start], len);
                var_name[j] = '\0';
                value = getenv(var_name);
                free(var_name);
                // if (value != NULL)
                    //struct recup la valeur de $NAME
            }
            // else
                // ca affiche jsute \n normalement
        }
    }

}