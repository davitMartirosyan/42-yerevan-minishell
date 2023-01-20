/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:57:01 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/17 02:11:22 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

void	add_pipe(char *cmdline, int *pos, int _p_ch, t_tok **token)
{
	int		i;
	int		_p;
	int		type;
	char	*pipe;

	i = *pos;
	_p = 1;
	pipe = NULL;
	while (cmdline[++i] && cmdline[i] == _p_ch)
		++_p;
	pipe = word(cmdline, _p, *pos);
	if (_p > 1)
		type = UNDEFINED;
	else
		type = PIPE;
	add(token, new_token(_p, pipe, type));
	free(pipe);
	*pos += _p - 1;
}

void	replace_tokens(t_tok *token)
{
	t_tok	*toks;

	toks = token;
	while (toks != NULL)
	{
		token_replacment(toks->tok, 7, '\'');
		token_replacment(toks->tok, 8, '\"');
		toks = toks->next;
	}
}

void	find_quotes(char *cmdline, int quote)
{
	char	q_s;

	if (quote == '\'')
		q_s = '\"';
	else
		q_s = '\'';
	if (*cmdline == q_s && q_s == '\'')
			*cmdline = 7;
	if (*cmdline == q_s && q_s == '\"')
		*cmdline = 8;
}
