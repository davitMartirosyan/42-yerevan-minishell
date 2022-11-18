/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:27:49 by root              #+#    #+#             */
/*   Updated: 2022/11/18 15:48:10 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_header.h"

t_cmds *parse(t_tok *token, t_table *table, char **envp)
{
	t_cmds *commands;
	
	int _pipe;
	char *arguments;
	
	commands = malloc(sizeof(t_cmds));
	if(!commands)
		return (NULL);
	commands->i_stream = 0;
	commands->o_stream = 1;
	commands->path = "mek";
	arguments = NULL;
	parse_to(token, table, &commands, &arguments);
	printf("%s\n", commands->next->arg_pack[0]);

	return (commands);
}

void parse_to(t_tok *token, t_table *table, t_cmds **cmds, char **arguments)
{
	int _pipe;
	
	_pipe = pipes(&token) + 1;
	while(token != NULL && _pipe)
	{
		if(typeis_arg(token->type))
			*arguments = join_arguments(*arguments, 1, token->tok);
		if(typeis_redirection(token->type))
		{
			select_filename(&token, *cmds);
			token = token->next;
			continue;
		}
		if(typeis_heredoc(token->type))
		{
			heredoc(&token, *cmds, table);
			continue;
		}
		if(token->type == PIPE)
		{
			cmds = &(*cmds)->next;
			(*cmds) = malloc(sizeof(t_cmds));
			token = token->next;
			continue;
		}
		if(*arguments)
		{
			(*cmds)->arg_pack = ft_split(*arguments, 1);
			*arguments = NULL;
		}
		token = token->next;
	}
}

void close_prev_command(char **arguments, t_cmds *cmds, int *_pipe)
{
	t_cmds *next_cmd;
	
	if(*arguments)
		cmds->arg_pack = ft_split(*arguments, 1);
	*_pipe--;
}

t_cmdline *parse_tree(t_table *table, char **envp)
{
	t_cmdline	*commands;
	t_tok		*tokens;
	
	tokens = table->token;
	if(tokens != NULL)
	{
		if(syntax_handling(tokens))
		{
			commands = malloc(sizeof(t_cmdline));
			if(!commands)
				return (NULL);
			commands->cmds = parse(tokens, table, envp);
		}
		else
		{
			printf("%s - %s\n", SHELLERR, table->err_handling);
			return (NULL);
		}
	}
	
	if(commands->cmds)
		return (commands);
	return (NULL);
}

//gcc -I includes */*.c minishell.c -lreadline -o minishell && ./minishell