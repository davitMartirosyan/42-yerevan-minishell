/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:27:49 by root              #+#    #+#             */
/*   Updated: 2022/11/22 20:36:54 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

static void print_arguments(t_cmds **commands);

t_cmds *parse(t_tok *token, t_table *table, char **envp)
{
	t_cmds *commands;
	
	commands = malloc(sizeof(t_cmds));
	if(!commands)
		return (NULL);
	std(&commands);
	parse_to(token, table, &commands);
	// separate(&commands);
	// reduce(&commands);
	return (commands);
}

static void print_arguments(t_cmds **commands)
{
	while(*commands != NULL)
	{
		printf("%s\n", (*commands)->arguments);
		commands = &(*commands)->next;
	}
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
		if(syntax_handling(tokens))
		{
			commands = malloc(sizeof(t_cmdline));
			if(!commands)
				return (NULL);
			commands->cmds = parse(tokens, table, envp);
			if(commands->cmds)
				return (commands);
		}
		else
			return (NULL);
	}
	return (NULL);
}

void separate(t_cmds **commands)
{
	while((*commands) != NULL && (*commands)->arguments != NULL)
	{
		(*commands)->arg_pack = ft_split((*commands)->arguments, 1);
		commands = &((*commands)->next);
	}
}

void reduce(t_cmds **commands)
{
	int i;

	while((*commands) != NULL && (*commands)->arguments != NULL)
	{
		i = -1;
		while((*commands)->arg_pack[++i] && (*commands)->arg_pack[i] != NULL)
			token_replacment((*commands)->arg_pack[i], 3, ' ');
		commands = &(*commands)->next;
	}
}

//gcc -I includes */*.c minishell.c -lreadline -o minishell && ./minishell