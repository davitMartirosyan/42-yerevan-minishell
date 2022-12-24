/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:00:41 by root              #+#    #+#             */
/*   Updated: 2022/12/18 15:06:43 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

void	heredoc(t_tok **token, t_cmds *cmds, t_table *table)
{
	t_vars *v;
	char *delim;
	char *term;
	char *tmpfile;
	
	delim = NULL;
	term = NULL;
	tmpfile = NULL;
    v = malloc(sizeof(t_vars));
    if(!v)
        return ;
    v->log = (*token)->type;
	while((*token)->type != WORD && (*token)->type != EXP_FIELD)
		*token = (*token)->next;
    delim = heredoc_delimiter(token, &v);
	term = open_heredoc_prompt(delim, v->var, table);
	tmpfile = new_file(table);
	open__file__check__type(v->log, tmpfile, cmds);
	if(term)
		write(cmds->i_stream, term, ft_strlen(term));
	close(cmds->i_stream);
	v->fd = open(tmpfile, O_RDONLY, 0644);
	free(tmpfile);
	cmds->i_stream = v->fd;
	free(v);
	free(term);
	free(delim);
}

char	*new_file(t_table *table)
{
	char *tmpfile;
	char *tmp;

	tmp = NULL;
	tmp = ft_itoa(table->get_pid);
	tmpfile = ft_strdup("/var/tmp/");
	tmpfile = ft_strjoin(tmpfile, ".minishell-");
	tmpfile = ft_strjoin(tmpfile, tmp);
	free(tmp);
	tmp = NULL;
	tmp = ft_itoa(table->hdocs);
	tmpfile = ft_strjoin(tmpfile, tmp);
	free(tmp);
	tmp = NULL;
	table->hdocs++;
	return ( tmpfile);
}

char	*heredoc_delimiter(t_tok **token, t_vars **v)
{
    char *delim;
    
    delim = NULL;
	while(*token != NULL)
	{
		if((*token)->type == WORD || (*token)->type == EXP_FIELD)
		{
			if((*token)->type == EXP_FIELD)
				(*v)->var = 1;
			delim = ft_strjoin(delim, (*token)->tok);
		}
		if((*token)->type == SEP || (*token)->type == HEREDOC)
			(*v)->let++;
		if((*v)->let == 1 || (*token)->next == NULL)
			break;
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
	heredoc = NULL;
	while(1)
	{
		heredoc = readline("> ");
		if(heredoc == NULL)
			break;
		if(heredoc && ft_strcmp(heredoc, delim) != 0)
			term = join_arguments(term, '\n', heredoc);
		if(ft_strcmp(heredoc, delim) == 0 && \
			ft_strlen(heredoc) == ft_strlen(delim))
		{
			term = ft_strjoin(term, "\n");
			break;
		}
		free(heredoc);
	}
	free(heredoc);
	if(term)
	{
		if(!flag)
			term = find_replace(term, table);
		return (term);
	}
	else
		return (NULL);
}