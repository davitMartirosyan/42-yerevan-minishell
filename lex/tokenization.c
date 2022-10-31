/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 03:00:39 by dmartiro          #+#    #+#             */
/*   Updated: 2022/10/31 11:45:05 by user             ###   ########.fr       */
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
		if(cmdline[i] && (cmdline[i] == '\"' || cmdline[i] == '\''))
			expansion(cmdline, &i, cmdline[i], &tokens);
		if (cmdline[i] && (cmdline[i] == '>' || cmdline[i] == '<'))
			redirection(cmdline, &i, cmdline[i], &tokens);
		if (cmdline[i] && cmdline[i] == '|')
			add_pipe(cmdline, &i, cmdline[i], &tokens);
	}
	return (tokens);
}

void expansion(char *cmdline, int *pos, int quote, t_tok **token)
{
	int flag;
	int i;
	char *exp_field;
	int len;
	
	i = *pos;
	flag = 1;
	len = 1;
	while(cmdline[i++])
	{
		if(cmdline[i] && cmdline[i] == quote)
		{
			flag = 0;
			continue;
		}
		else if(flag == 0 && !ft_iswordpart(cmdline[i]))
			break;
		len++;
	}
	exp_field = word(cmdline, len, *pos);
	add(token, new_token(len, exp_field, EXP_FIELD));
	free(exp_field);
	*pos += len;
}