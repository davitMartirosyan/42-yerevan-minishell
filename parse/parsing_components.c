/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_components.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:29:49 by root              #+#    #+#             */
/*   Updated: 2022/12/17 14:31:56 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

void select_filename(t_tok **token, t_cmds *cmds)
{
	int type;
	
	type = (*token)->type;
	while((*token)->type != WORD && (*token)->type != EXP_FIELD)
		*token = (*token)->next;
	open__file__check__type(type, (*token)->tok, cmds);
}

void open__file__check__type(int type, char *filename, t_cmds *cmds)
{
	int fd;	

	fd = 0;
	if(type == REDIR_OUT)
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if(type == REDIR_IN)
	{
		fd = open(filename, O_RDONLY);
		cmds->err = filename;
	}
	else if(type == APPEND)
		fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if(type == HEREDOC)
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	check_type(fd, type, cmds);
}

void check_type(int fd, int type, t_cmds *cmds)
{
	if(type == REDIR_IN || type == HEREDOC)
	{
		if(cmds->i_stream != 0)
			close(cmds->i_stream);
		cmds->i_stream = fd;
	}
	else if(type == REDIR_OUT || type == APPEND)
	{
		if(cmds->o_stream != 1)
			close(cmds->o_stream);
		cmds->o_stream = fd;
	}
}

int type_is_p_h(t_tok **token, t_cmds ***cmds, t_table *table)
{
	if(typeis_heredoc((*token)->type))
	{
		heredoc(token, *(*cmds), table);
		return 0;
	}
	if((*token)->type == PIPE)
	{
		*cmds = &(*(*cmds))->next;
		*(*cmds) = malloc(sizeof(t_cmds));
		std(*cmds);	
		*token = (*token)->next;
		return 0;
	}
	return 1;
}

void    std(t_cmds **cmds)
{
	(*cmds)->arg_pack = NULL;
	(*cmds)->arguments = NULL;
	(*cmds)->i_stream = STDIN;
	(*cmds)->o_stream = STDOUT;
	(*cmds)->e_stream = STDERR;
}

