/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:00:41 by root              #+#    #+#             */
/*   Updated: 2022/11/16 10:27:20 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_header.h"

void	heredoc(t_tok **token, t_cmds *cmds, t_table *table)
{
	t_vars *v;
	char *delim;
	char *term;
	char *tmpfile;
    
	tmpfile = NULL;
    v = malloc(sizeof(t_vars));
    if(!v)
        return ;
    v->log = (*token)->type;
	while((*token)->type != WORD && (*token)->type != EXP_FIELD)
		*token = (*token)->next;
    delim = heredoc_delimiter(token, &v);
	term = open_heredoc_prompt(delim, v->var, table);
    tmpfile = ft_strjoin(tmpfile, "/var/tmp/");
    tmpfile = ft_strjoin(tmpfile, "ayb");
    tmpfile = ft_strjoin(tmpfile, delim);
	if(term)
	{
		open__file__check__type(v->log, tmpfile, cmds);
		write(cmds->i_stream, term, ft_strlen(term));
	}
}

char    *heredoc_delimiter(t_tok **token, t_vars **v)
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
		if((*token)->type == SEP)
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
	while(1)
	{
		heredoc = readline("heredoc> ");
		if(ft_strncmp(heredoc, delim, ft_strlen(delim)) == 0 && \
			ft_strlen(heredoc) == ft_strlen(delim))
				break;
		if(heredoc)
			term = join_arguments(term, '\n', heredoc);
	}
	if(term)
	{
		
		if(!flag)
			term = find_replace(term, table->env);
        printf("%s\n", term);
		return (term);
	}
	else
		return (NULL);
}