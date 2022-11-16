/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:27:49 by root              #+#    #+#             */
/*   Updated: 2022/11/16 10:25:54 by user             ###   ########.fr       */
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
		// if(token->type == PIPE)
		// {
		// 	//Remove words from *arguments
		// 	//Next node in cmds struct
		// 	//check if _pipe is 0 or not
		// 	//token pointer move after pipe symbol token
		// 	//continue;
		// }
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
	return (commands);
}

//gcc -I includes */*.c minishell.c -lreadline -o minishell && ./minishell