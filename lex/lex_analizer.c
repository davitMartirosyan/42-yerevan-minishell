/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_analizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:06:07 by root              #+#    #+#             */
/*   Updated: 2022/11/14 07:33:55 by dmartiro         ###   ########.fr       */
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
	}
	else
		printf("%s '%s'\n", TOKEN_SYNTAX_ERR, "\'");
}