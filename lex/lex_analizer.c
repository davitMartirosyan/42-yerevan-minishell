/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_analizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:06:07 by root              #+#    #+#             */
/*   Updated: 2022/10/23 03:36:25 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell_header.h"

void lexical_analyzer(char *cmdline, t_table *table)
{
	openquotes(cmdline);
	if(quote_syntax_analyzer(cmdline, table->q_c))
	{
		cmdline = find_replace(cmdline, table->env);
		token_replacment(cmdline, 4, '$');
	}
	else
	{
		printf("%s '%s'\n",QUOTE_SYNTAX_ERR, "\'");
		return ;
	}
	table->token = tokenization(cmdline);
	while(table->token->next != NULL)
	{
		printf("%s\n", table->token->tok);
		table->token = table->token->next;
	}
	printf("\n\n%s\n", cmdline);
	return ;
}
	// printf("double quotes -> %d\n", (*table)->q_counts[0]);
	// printf("single quotes -> %d\n", (*table)->q_counts[1]);

	