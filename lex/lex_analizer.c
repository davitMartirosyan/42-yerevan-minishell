/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_analizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:06:07 by root              #+#    #+#             */
/*   Updated: 2022/12/18 15:05:32 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

int lexical_analyzer(char *cmdline, t_table *table)
{
	openquotes(cmdline);
	if(syntax_handling(cmdline, table, NULL))
	{
		cmdline = find_replace(cmdline, table);
		token_replacment(cmdline, 4, '$');
		table->token = tokenization(cmdline);
		return (1);
	}
	return (0);
}