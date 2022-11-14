/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:27:49 by root              #+#    #+#             */
/*   Updated: 2022/11/14 15:11:50 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_header.h"

t_cmds *parse(t_tok *token, t_table *table, char **envp)
{
	t_cmds *cmds;
	int _pipe;
	char *arguments;
	
	cmds = malloc(sizeof(t_cmds));
	if(!cmds)
		return (NULL);
	cmds->i_stream = 0;
	cmds->o_stream = 1;
	arguments = NULL;
	parse_to(token, table, cmds, &arguments);
	printf("%s\n", arguments);
	if(arguments)
		cmds->arg_pack = ft_split(arguments, 1);
	return (cmds);
}

void parse_to(t_tok *token, t_table *table, t_cmds *cmds, char **arguments)
{
	int _pipe;
	
	_pipe = pipes(&token) + 1;
	while(token != NULL)
	{
		if(typeis_arg(token->type))
			*arguments = join_arguments(*arguments, 1, token->tok);
		if(typeis_redirection(token->type))
		{
			select_filename(&token, cmds);
			token = token->next;
			continue;
		}
		if(typeis_heredoc(token->type))
		{
			heredoc(&token, cmds, table);
			continue;
		}
		token = token->next;
	}
}

t_cmdline *parse_tree(t_table *table, char **envp)
{
	t_cmdline	*commands;
	t_tok		*tokens;
	
	tokens = table->token;
	if(tokens != NULL)
	{
		if(!syntax_handling(tokens))
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
	return (commands);
}

void heredoc(t_tok **token, t_cmds *cmds, t_table *table)
{
	int flag;
	char *delim;
	int dob;
	
	delim = NULL;
	flag = 0;
	dob = 0;
	while((*token)->type != WORD && (*token)->type != EXP_FIELD)
		*token = (*token)->next;
	while((*token) != NULL)
	{
		if((*token)->type == WORD || (*token)->type == EXP_FIELD)
		{
			if((*token)->type == EXP_FIELD)
				flag = 1;
			delim = ft_strjoin(delim, (*token)->tok);
		}
		if((*token)->type == SEP)
			dob++;
		if(dob == 1 || (*token)->next == NULL)
			break;
		*token = (*token)->next;
	}
	open_heredoc_prompt(delim, flag, cmds, table);
}

void open_heredoc_prompt(char *delim, int flag, t_cmds *cmds, t_table *table)
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
		term = join_arguments(term, '\n', heredoc);
	}
	if(term)
	{
		if(!flag)
			term = find_replace(term, table->env);
		printf("%s\n", term);
	}
}

//gcc -I includes */*.c minishell.c -lreadline -o minishell && ./minishell