/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_analizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:56:56 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/16 12:04:35 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

int	lexical_analyzer(char *newpoint, t_table *table)
{
	char *cmdline;
	int t_f;

	t_f = 1;
	cmdline = ft_strdup(newpoint);
	openquotes(cmdline);
	if (quote_syntax_analyzer(cmdline, table->q_c))
	{
		cmdline = find_replace(cmdline, table);
		token_replacment(cmdline, 4, '$');
		table->token = tokenization(cmdline);
	}
	else
		quote_error(&t_f, table);
	free(cmdline);
	if(t_f == 1)	
		return (t_f);
	return (t_f);
}

void	quote_error(int *t_f, t_table *table)
{
	char	*d_s;

	d_s = "\'";
	if (table->q_c[0] % 2 != 0)
		d_s = "\"";
	ft_fprintf(STDERR_FILENO, "minishell: %s `%s'\n", TOKEN_SYNTAX_ERR, d_s);
	table->status = 256;
	*t_f = 0;
}