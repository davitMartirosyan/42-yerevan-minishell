/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:27:49 by root              #+#    #+#             */
/*   Updated: 2022/11/09 05:44:30 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
static void select_filename(t_tok *token, t_cmds *cmds);

t_cmds *parse(t_tok **token, t_table *table, char **envp)
{
	t_cmds *cmds;
	int pipe_count;
	char	*arguments;

	cmds = malloc(sizeof(t_cmds));
	if(!cmds)
		return (NULL);
	pipe_count = pipes(token) + 1;
	arguments = NULL;
	while(*token != NULL)
	{
		if(typeis_arg((*token)->type))
			arguments = join_arguments(arguments, 1, (*token)->tok);
		if(typeis_redirection((*token)->type))
			select_filename(*token, cmds);
		if((*token)->next == NULL)
			break;
		token = &(*token)->next;
	}
	printf("%s\n", arguments);
	return (NULL);
}

static void select_filename(t_tok *token, t_cmds *cmds)
{
	while(token->type != WORD && token->type != EXP_FIELD)
		*token = *token->next;
	printf("%s\n", token->tok);
}

t_cmdline  *parse_tree(t_table *table, char **envp)
{
	t_cmdline	*commands;
	t_tok		*tokens;
	t_cmds		*cmds;
	
	tokens = table->token;
	if(tokens != NULL)
	{
		cmds = parse(&tokens, table, envp);
	}	
	return (NULL);
}















// sdfdfjgskdjksdj 'fsjdhf " ' sdkfjsldf " hssdkhasd ' "

// sdfdfjgskdjksdj 'fsjdhf 8 ' sdkfjsldf " hssdkhasd 7 "

// sdfdfjgskdjksdj 'fsjdhf " ' sdkfjsldf " hssdkhasd ' "