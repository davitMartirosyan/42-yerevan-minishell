/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_analizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <tumolabs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:56:56 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/18 22:20:37 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

int	lexical_analyzer(char *newpoint, t_table *table)
{
	char	*cmdline;
	int		t_f;

	t_f = 1;
	cmdline = ft_strdup(newpoint);
	openquotes(cmdline);
	if (quote_syntax_analyzer(cmdline, table->q_c))
	{
		cmdline = find_replace(cmdline, table);
		token_replacment(cmdline, 4, '$');
		table->token = tokenization(cmdline);
		replace_tokens(table->token);
	}
	else
		quote_error(&t_f, table);
	free(cmdline);
	if (t_f == 1)
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

int	dollar_expansions(char *cmdline, t_vars *v)
{
	if (cmdline[v->log] && cmdline[v->log] == '$' && \
		cmdline[v->log + 1] != '?' && \
		cmdline[v->log + 1] != '$' && cmdline[v->log + 1] != '\0')
		return (1);
	return (0);
}

void	_key_value_pair(char **cmdline, char **key, char **val, t_table *table)
{
	*key = keyof(*cmdline, table->v.log + 1);
	*val = valueof(*key, table->env);
	*cmdline = replace(*cmdline, *key, *val, &table->v.log);
}

int	__meta_chars(char *cmdline_ch)
{
	if (*cmdline_ch && *cmdline_ch == '\'')
		return (0);
	if (*cmdline_ch && *cmdline_ch == '\"')
		*cmdline_ch = 8;
	if (*cmdline_ch && *cmdline_ch == '$')
		*cmdline_ch = 4;
	return (1);
}
