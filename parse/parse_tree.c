/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:27:49 by root              #+#    #+#             */
/*   Updated: 2022/11/14 08:11:00 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_header.h"

static void heredoc(t_tok **token, t_cmds *cmds);
static void open_heredoc_prompt(char *delim, int flag, t_cmds *cmds);

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
	_pipe = pipes(&token) + 1;
	arguments = NULL;
	
	while(token != NULL)
	{
		if(typeis_arg(token->type))
			arguments = join_arguments(arguments, 1, token->tok);
		if(typeis_redirection(token->type))
		{
			select_filename(&token, cmds);
			token = token->next;
			continue;
		}
		if(typeis_heredoc(token->type))
		{
			heredoc(&token, cmds);
			continue;
		}
		token = token->next;
	}
	// printf("[%s]\n", arguments);
	if(arguments)
		cmds->arg_pack = ft_split(arguments, 1);
	return (cmds);
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

static void heredoc(t_tok **token, t_cmds *cmds)
{
	int flag;
	char *delim;
	int dob;
	t_tok *tmp;
	
	delim = NULL;
	flag = 0;
	dob = 0;
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
		if(dob == 2)
			break;
		*token = (*token)->next;
	}
	// printf("{%s}\n", delim);
	open_heredoc_prompt(delim, flag, cmds);
}

static void open_heredoc_prompt(char *delim, int flag, t_cmds *cmds)
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
	printf("%s\n", term);
}

//gcc -I includes */*.c minishell.c -lreadline -o minishell && ./minishell