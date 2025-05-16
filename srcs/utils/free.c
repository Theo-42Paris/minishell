#include "../../include/minishell.h"

void	free_env(t_env **env)
{
	t_env	*tmp;

	if (!env)
		return;
	while (*env)
	{
		tmp = (*env)->next;
		free((*env)->env);
		free(*env);
		*env = tmp;
	}
	*env = NULL;
}

void free_token(t_token **token)
{
    t_token *tmp;
    while (*token)
    {
        tmp = (*token)->next;
        if ((*token)->data)
            free((*token)->data);
        free(*token);
        *token = tmp;
    }
}

void	free_redir(t_redir **redir)
{
	t_redir	*tmp;

	if (!redir || !*redir)
		return ;
	while (*redir)
	{
		tmp = (*redir)->next;
		free((*redir)->arg);
		free(*redir);
		*redir = tmp;
	}
	*redir = NULL;
}

void	free_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;
	int		i;

	if (!cmd || !*cmd)
		return ;
	while (*cmd)
	{
		tmp = (*cmd)->next;
		if ((*cmd)->args)
		{
			i = 0;
			while ((*cmd)->args[i])
			{
				free((*cmd)->args[i]);
				i++;
			}
			free((*cmd)->args);
		}
		//free((*cmd)->cmd);
		free_redir(&((*cmd)->redir));
		free(*cmd);
		*cmd = tmp;
	}
	*cmd = NULL;
}

void	free_all(t_data *data, char *line, char *good_line)
{
	free(line);
	free(good_line);
	free_token(&data->token);
	free_cmd(&data->cmd);
}
