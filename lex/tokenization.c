/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 03:00:39 by dmartiro          #+#    #+#             */
/*   Updated: 2022/10/31 16:09:22 by user             ###   ########.fr       */
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
		else if(cmdline[i] && ft_isspace(cmdline[i]))
			space(cmdline, &i, cmdline[i], &tokens);
		else if(cmdline[i] && (cmdline[i] == '\"' || cmdline[i] == '\''))
			expansion(cmdline, &i, cmdline[i], &tokens);
		else if (cmdline[i] && (cmdline[i] == '>' || cmdline[i] == '<'))
			redirection(cmdline, &i, cmdline[i], &tokens);
		else if (cmdline[i] && cmdline[i] == '|')
			add_pipe(cmdline, &i, cmdline[i], &tokens);
	}
	return (tokens);
}

void space(char *cmdline, int *pos, char sep, t_tok **token)
{
	int i;
	int len;
	char *separator;
	
	i = *pos;
	len = 1;
	while(cmdline[++i])
	{
		if(!ft_isspace(cmdline[i]))
			break;
		++len;
	}
	separator = word(cmdline, len, *pos);
	add(token, new_token(len, separator, SEP));
	*pos += len;
}