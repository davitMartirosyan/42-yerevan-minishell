/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_analizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:06:07 by root              #+#    #+#             */
/*   Updated: 2022/10/31 16:08:31 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell_header.h"

void lexical_analyzer(char *cmdline, t_table *table)
{	
	openquotes(cmdline);
	if(quote_syntax_analyzer(cmdline, table->q_c))
	{
		// cmdline = find_replace(cmdline, table->env);
		token_replacment(cmdline, 4, '$');
		table->token = tokenization(cmdline);
	}
	else
		printf("%s '%s'\n", QUOTE_SYNTAX_ERR, "\'");
	free(cmdline);
}

	