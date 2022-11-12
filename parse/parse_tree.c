/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:27:49 by root              #+#    #+#             */
/*   Updated: 2022/11/12 21:08:03 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

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
		if(typeis_heredoc((*token)->type))
			heredoc()
		if((*token) == NULL)
			break;
		token = &(*token)->next;
	}
	cmds->arg_pack = ft_split(arguments, 1);
	return (cmds);
}

t_cmdline * parse_tree(t_table *table, char **envp)
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
			commands->cmds = parse(&tokens, table, envp);
		}
		else
		{
			printf("%s - %s\n", SHELLERR, table->err_handling);
			return (NULL);
		}
	}
	return (commands);
}