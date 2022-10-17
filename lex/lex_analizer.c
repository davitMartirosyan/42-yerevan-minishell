/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_analizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:06:07 by root              #+#    #+#             */
/*   Updated: 2022/10/17 06:03:02 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell_header.h"

void lexical_analyze(char *cmdline, t_table **table)
{
	openquotes(cmdline);
	if(quote_syntax_analyze(cmdline, (*table)->q_c))
	{
		cmdline = find_replace(cmdline, (*table)->env);
		token_replacment(cmdline, 4, '$');
		printf("%s\n", cmdline);
	}
	else
		printf("%s %s '%s'\n", SHELL, QUOTE_SYNTAX_ERR, "\'");
}
	// printf("double quotes -> %d\n", (*table)->q_counts[0]);
	// printf("single quotes -> %d\n", (*table)->q_counts[1]);

	