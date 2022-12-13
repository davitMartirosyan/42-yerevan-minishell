/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_analizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:06:07 by root              #+#    #+#             */
/*   Updated: 2022/12/13 15:49:33 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

int lexical_analyzer(char *cmdline, t_table *table)
{
	openquotes(cmdline);
	if(syntax_handling(cmdline, table, NULL))
	{
		cmdline = find_replace(cmdline, table->env);
		token_replacment(cmdline, 4, '$');
		table->token = tokenization(cmdline);
		return (1);
	}
	return (0);
}