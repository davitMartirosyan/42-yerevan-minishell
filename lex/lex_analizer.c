/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_analizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:06:07 by root              #+#    #+#             */
/*   Updated: 2022/10/22 07:48:43 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell_header.h"

char *lexical_analyzer(char *cmdline, t_table **table)
{
	t_tok *token;
	t_tok *tmp;
	openquotes(cmdline);
	if(quote_syntax_analyzer(cmdline, (*table)->q_c))
	{
		cmdline = find_replace(cmdline, (*table)->env);
		token_replacment(cmdline, 4, '$');
	}
	else
	{
		printf("%s '%s'\n",QUOTE_SYNTAX_ERR, "\'");
		return (NULL);
	}

	token = tokenization(cmdline);
	tmp = token;
	while(tmp->next != NULL)
	{
		printf("{%s}-{%d}-{%d}\n",\
			tmp->tok,
			tmp->len,
			tmp->type
		);
		tmp = tmp->next;
	}
	printf("\n\n%s\n", cmdline);
	return (NULL);
}
	// printf("double quotes -> %d\n", (*table)->q_counts[0]);
	// printf("single quotes -> %d\n", (*table)->q_counts[1]);

	