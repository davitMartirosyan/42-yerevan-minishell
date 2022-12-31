/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:00:41 by root              #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/12/08 22:35:02 by dmartiro         ###   ########.fr       */
=======
/*   Updated: 2022/12/18 15:06:43 by dmartiro         ###   ########.fr       */
>>>>>>> master
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

void	heredoc(t_tok **token, t_cmds *cmds, t_table *table)
{
	t_vars *v;
	char *delim;
	char *term;
	char *tmpfile;
<<<<<<< HEAD
    int	fd;
	
    v = malloc(sizeof(t_vars));
    if(!v)
        return ;
=======
	
	delim = NULL;
	term = NULL;
	tmpfile = NULL;
    v = malloc(sizeof(t_vars));
>>>>>>> master
    v->log = (*token)->type;
	while((*token)->type != WORD && (*token)->type != EXP_FIELD)
		*token = (*token)->next;
    delim = heredoc_delimiter(token, &v);
	term = open_heredoc_prompt(delim, v->var, table);
<<<<<<< HEAD
	tmpfile = new_file(delim);
=======
	if(!term)
		return ;
	tmpfile = new_file(table);
>>>>>>> master
	open__file__check__type(v->log, tmpfile, cmds);
	if(term)
		write(cmds->i_stream, term, ft_strlen(term));
	close(cmds->i_stream);
<<<<<<< HEAD
	fd = open(tmpfile, O_RDONLY);
	cmds->i_stream = fd;
}

char	*new_file(char *delim)
{
	static int tail = 1234;
	char *tmpfile;
	
	tmpfile = "/var/tmp/";
	tmpfile = ft_strjoin(tmpfile, "ayb");
	tmpfile = ft_strjoin(tmpfile, delim);
	tmpfile = ft_strjoin(tmpfile, ft_itoa(tail));
	tail++;
=======
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
>>>>>>> master
	return (tmpfile);
}

char	*heredoc_delimiter(t_tok **token, t_vars **v)
{
    char *delim;
    
    delim = NULL;
<<<<<<< HEAD
    while((*token) != NULL)
=======
	while(*token != NULL)
>>>>>>> master
	{
		if((*token)->type == WORD || (*token)->type == EXP_FIELD)
		{
			if((*token)->type == EXP_FIELD)
				(*v)->var = 1;
			delim = ft_strjoin(delim, (*token)->tok);
		}
<<<<<<< HEAD
		if((*token)->type == SEP)
=======
		if((*token)->type == SEP || (*token)->type == HEREDOC)
>>>>>>> master
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
<<<<<<< HEAD
	
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
			term = find_replace(term, table->env);
=======

	term = NULL;
	heredoc = NULL;
	while(1)
	{
		heredoc = readline("> ");
		if(heredoc == NULL)
			return (NULL);
		if(heredoc && ft_strcmp(heredoc, delim) != 0)
			term = join_arguments(term, '\n', heredoc);
		if(ft_strlen(heredoc) == ft_strlen(delim) && \
			ft_strcmp(heredoc, delim) == 0)
		{
			term = ft_strjoin(term, "\n");
			break;
		}
		free(heredoc);
	}
	free(heredoc);
	if(term)
	{
		if(flag != 1)
			term = find_replace(term, table);
>>>>>>> master
		return (term);
	}
	else
		return (NULL);
}