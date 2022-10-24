/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_analizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:06:07 by root              #+#    #+#             */
/*   Updated: 2022/10/24 21:39:09 by root             ###   ########.fr       */
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
		table->token = tokenization(cmdline);
		while(table->token != NULL)
		{
			printf("%s\n", table->token->tok);
			table->token = table->token->next;
		}
	}
	else
	{
		printf("%s '%s'\n",QUOTE_SYNTAX_ERR, "\'");
		return ;
	}
	
	// printf("\n%s\n", cmdline);
}
	// printf("double quotes -> %d\n", (*table)->q_counts[0]);
	// printf("single quotes -> %d\n", (*table)->q_counts[1]);

	