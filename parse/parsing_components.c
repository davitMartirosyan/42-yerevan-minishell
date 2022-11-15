/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_components.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:29:49 by root              #+#    #+#             */
/*   Updated: 2022/11/15 15:19:16 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_header.h"

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
	
	if(type == REDIR_OUT)
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if(type == REDIR_IN)
		fd = open(filename, O_RDONLY);
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