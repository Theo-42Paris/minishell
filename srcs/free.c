#include "../include/minishell.h"

void	free_token(t_token **token)
{
	t_token	*tmp;

	if (!token)
		return ;
	while (*token)
	{
		tmp = (*token)->next;
		free((*token)->data);
		free(*token);
		*token = tmp;
	}
	*token = NULL;
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
		free((*cmd)->cmd);
		free_redir(&((*cmd)->redir));
		free(*cmd);
		*cmd = tmp;
	}
	*cmd = NULL;
}
