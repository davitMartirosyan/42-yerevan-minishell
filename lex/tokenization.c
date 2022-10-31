/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 03:00:39 by dmartiro          #+#    #+#             */
/*   Updated: 2022/10/31 06:37:33 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

t_tok *tokenization(char *cmdline)
{
	t_tok *tokens;
	int i;

	tokens = NULL;
	i = -1;
	while (cmdline[++i])
	{
		if (cmdline[i] && ft_iswordpart(cmdline[i]))
			add_word(cmdline, &i, &tokens);
		if (cmdline[i] && (cmdline[i] == '\"' || cmdline[i] == '\''))
			expansions(cmdline, &i, cmdline[i], &tokens);
		if (cmdline[i] && (cmdline[i] == '>' || cmdline[i] == '<'))
			redirection(cmdline, &i, cmdline[i], &tokens);
		if (cmdline[i] && cmdline[i] == '|')
			add_pipe(cmdline, &i, cmdline[i], &tokens);
	}
	// printf("%s\n", cmdline);
	while(tokens != NULL)
		{
			printf("%s : %d\n", tokens->tok, tokens->type);
			tokens = tokens->next;
		}
	return (tokens);
}

void expansions(char *cmdline, int *pos, int quote, t_tok **token)
{
	int i;
	int len;
	char *expansion;

	i = *pos;
	len = 0;
	while(cmdline[++i] && cmdline[i] != quote)
		++len;
	expansion = word(cmdline, len, *pos + 1);
	add(token, new_token(len, expansion, EXP_FIELD));
	*pos += len+1;
}