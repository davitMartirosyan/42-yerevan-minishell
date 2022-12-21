/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:00:41 by root              #+#    #+#             */
/*   Updated: 2022/12/21 23:43:43 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

void	heredoc(t_tok **token, t_cmds *cmds, t_table *table)
{
	static int hd = 0;
	t_vars *v;
	char *delim;
	char *term;
	char *tmpfile;
    int	fd;
	
	(void)hd;
    v = malloc(sizeof(t_vars));
    if(!v)
        return ;
    v->log = (*token)->type;
	while((*token)->type != WORD && (*token)->type != EXP_FIELD)
		*token = (*token)->next;
    delim = heredoc_delimiter(token, &v);
	term = open_heredoc_prompt(delim, v->var, table);
	tmpfile = new_file(delim);
	open__file__check__type(v->log, tmpfile, cmds);
	if(term)
		write(cmds->i_stream, term, ft_strlen(term));
	close(cmds->i_stream);
	fd = open(tmpfile, O_RDONLY, 0644);
	cmds->i_stream = fd;
}

char	*new_file(char *delim)
{
	char *tmpfile;

	tmpfile = ft_strjoin("/var/tmp/", "ayb");
	tmpfile = ft_strjoin(tmpfile, delim);
	return (tmpfile);
}

char	*heredoc_delimiter(t_tok **token, t_vars **v)
{
    char *delim;
    
    delim = NULL;
    while((*token) != NULL)
	{
		if((*token)->type == WORD || (*token)->type == EXP_FIELD)
		{
			if((*token)->type == EXP_FIELD)
				(*v)->var = 1;
			delim = ft_strjoin(delim, (*token)->tok);
		}
		if((*token)->type == SEP || (*token)->type == HEREDOC)
			break;
		if((*token)->next == NULL)
		{
			*token = (*token)->next;
			break;
		}
		*token = (*token)->next;
	}
    if(delim)
        return (delim);
    else
        return (NULL);
}

char	*open_heredoc_prompt(char *delim, int flag, t_table *table)
{
	char *heredoc;
	char *term;
	
	term = NULL;
	while(1)
	{
		heredoc = readline("heredoc> ");
		if(heredoc && ft_strncmp(heredoc, delim, ft_strlen(delim)) != 0)
			term = join_arguments(term, '\n', heredoc);
		if(ft_strncmp(heredoc, delim, ft_strlen(delim)) == 0 && \
			ft_strlen(heredoc) == ft_strlen(delim))
				break;
	}
	if(term)
	{
		if(!flag)
			term = find_replace(term, table);
		return (term);
	}
	else
		return (NULL);
}