/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:27:49 by root              #+#    #+#             */
/*   Updated: 2022/11/26 21:01:52 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

t_cmds *parse(t_tok *token, t_table *table, char **envp)
{
	(void)envp;
	t_cmds *commands;
	
	commands = malloc(sizeof(t_cmds));
	if(!commands)
		return (NULL);
	std(&commands);
	parse_to(token, table, &commands);
	separate(&commands);
	return (commands);
}

void parse_to(t_tok *token, t_table *table, t_cmds **cmds)
{
	while(token != NULL)
	{
		if(typeis_arg(token->type))
		{
			(*cmds)->arguments = join_arguments((*cmds)->arguments, 1, \
			token->tok);
			token = token->next;
			continue;
		}
		if(typeis_redirection(token->type))
		{
			select_filename(&token, *cmds);
			token = token->next;
			continue;
		}
		if(!type_is_p_h(&token, &cmds, table))
			continue;
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
		commands = malloc(sizeof(t_cmdline));
		if(!commands)
			return (NULL);
		commands->cmds = parse(tokens, table, envp);
		if(commands->cmds)
			return (commands);
			// syntax_handling(&tokens, &commands);
	}
	return (NULL);
}

void separate(t_cmds **commands)
{
	t_cmds *tmp;
	int i;

	tmp = *commands;
	while((*commands) != NULL)
	{
		if((*commands)->arguments != NULL)
			(*commands)->arg_pack = ft_split((*commands)->arguments, 1);
		commands = &(*commands)->next;
	}
	
	while(tmp != NULL)
	{
		i = -1;
		if(tmp != NULL && tmp->arguments != NULL)
			while(tmp->arg_pack[++i])
				token_replacment(tmp->arg_pack[i], 3, ' ');
		tmp = tmp->next;
	}
}
// "echo $USER" | > file

//gcc -I includes */*.c minishell.c -lreadline -o minishell && ./minishell