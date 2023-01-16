/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:57:38 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/16 11:57:39 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
int g_var = 0;

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
	v->log = (*token)->type;
	while ((*token)->type != WORD && (*token)->type != EXP_FIELD)
		*token = (*token)->next;
	delim = heredoc_delimiter(token, &v);
	term = open_heredoc_prompt(delim, v->var, table);
	if (!term)
		return ;	
	tmpfile = new_file(table);
	open__file__check__type(v->log, tmpfile, cmds);
	if (term)
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
	return (tmpfile);
}

char	*heredoc_delimiter(t_tok **token, t_vars **v)
{
	char *delim;
	
	delim = NULL;
	while (*token != NULL)
	{
		if ((*token)->type == WORD || (*token)->type == EXP_FIELD)
		{
			if ((*token)->type == EXP_FIELD)
				(*v)->var = 1;
			delim = ft_strjoin(delim, (*token)->tok);
		}
		if ((*token)->type == SEP || (*token)->type == HEREDOC)
			(*v)->let++;
		if ((*v)->let == 1 || (*token)->next == NULL || \
			(*token)->type == PIPE)
			break;
		*token = (*token)->next;
	}
	if (delim)
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
	signal(SIGINT, heredoc_sig);
	while (1)
	{
		heredoc = readline("> ");
		if(g_var == 1)
		{
			ft_signal(0);
			break; 
		}
		if (heredoc == NULL)
		{
			ft_fprintf(STDERR_FILENO, \
			"-sadm: %s %d delimited by end-of-file (wanted `%s')\n", \
			HEREDOC_SYNTAX_WARNING, (uintmax_t)__LINE__, delim);
			term = ft_strjoin(term, "\n");
			break;
		}
		if (heredoc && ft_strcmp(heredoc, delim) != 0)
			term = join_arguments(term, '\n', heredoc);
		if (ft_strlen(heredoc) == ft_strlen(delim) && \
			ft_strcmp(heredoc, delim) == 0)
		{
			term = ft_strjoin(term, "\n");
			break;
		}
		free(heredoc);
	}
	free(heredoc);
	if (term && g_var == 0)
	{
		if (flag != 1)
			term = find_replace(term, table);
		return (term);
	}
	return (NULL);
}

void	heredoc_sig(int sig)
{
	(void)sig;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	g_var = 1;
}