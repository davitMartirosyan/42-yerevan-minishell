/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:27:49 by root              #+#    #+#             */
/*   Updated: 2022/11/12 20:30:55 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

static void select_filename(t_tok *token, t_cmds *cmds);
static void open__file__check__type(int type, char *filename, t_cmds *cmds);
static void check_type(int fd, int type, t_cmds *cmds);

t_cmds *parse(t_tok **token, t_table *table, char **envp)
{
	t_cmds *cmds;
	int _pipe;
	char *arguments;
	
	cmds = malloc(sizeof(t_cmds));
	if(!cmds)
		return (NULL);
	cmds->i_stream = 0;
	cmds->o_stream = 1;
	_pipe = pipes(token) + 1;
	arguments = NULL;
	while(*token != NULL && _pipe)
	{
		if(typeis_arg((*token)->type))
			arguments = join_arguments(arguments, 1, (*token)->tok);
		if(typeis_redirection((*token)->type))
		{
			select_filename(*token, cmds);
			*token = (*token)->next;
			continue;
		}
		// if((*token)->type == PIPE)
		// {
		// 	// close_command(arguments, cmds);
		// 	_pipe--;
		// }
		if((*token) == NULL)
			break;
		token = &(*token)->next;
	}
	write(cmds->o_stream, "barev", 5);
	return (cmds);
}

static void select_filename(t_tok *token, t_cmds *cmds)
{
	int type;
	
	type = token->type;
	while(token->type != WORD && token->type != EXP_FIELD)
		*token = *token->next;
	open__file__check__type(type, token->tok, cmds);
}

static void open__file__check__type(int type, char *filename, t_cmds *cmds)
{
	int fd;	

	if(type == REDIR_OUT)
		fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if(type == REDIR_IN)
		fd = open(filename, O_RDONLY);
	else if(type == APPEND)
		fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 0644);
	check_type(fd, type, cmds);
}

static void check_type(int fd, int type, t_cmds *cmds)
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

t_cmdline * parse_tree(t_table *table, char **envp)
{
	t_cmdline	*commands;
	t_tok		*tokens;
	
	commands = malloc(sizeof(t_cmdline));
	if(!commands)
		return (NULL);
	tokens = table->token;
	if(tokens != NULL)
		commands->cmds = parse(&tokens, table, envp);
	return (commands);
}