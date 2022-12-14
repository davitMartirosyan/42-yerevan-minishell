/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 20:07:27 by root              #+#    #+#             */
/*   Updated: 2022/12/14 13:18:53 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

int wordlen(char *wordstart, int s_pos)
{
	int i;

	i = 0;
	while(wordstart[s_pos] && ft_iswordpart(wordstart[s_pos]))
	{
		s_pos++;
		i++;
	}
	return (i);
}

char *word(char *cmdline, int len, int s_pos)
{
	char *word;
	int i;

	i = 0;
	word = malloc(sizeof(char) * (len + 1));
	while(i < len)
	{
		word[i] = cmdline[s_pos];
		s_pos++;
		i++;
	}
	word[i] = '\0';
	return (word);
}

void add_word(char *cmdline, int *pos, t_tok **token)
{
	int len;
	char *wordpart;
	
	len = wordlen(cmdline, *pos);
	wordpart = word(cmdline, len, *pos);
	add(token, new_token(len, wordpart, WORD));
	free(wordpart);
	*pos += len;
}

void space(char *cmdline, int *pos, t_tok **token)
{
	int i;
	int len;
	char *separator;
	
	i = *pos;
	len = 0;
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

void expansion(char *cmdline, int *pos, int quote, t_tok **token)
{
	int i;
	int len;
	char *exp;
	
	i = *pos;
	len = 0;
	while(cmdline[++i])
	{
		if(cmdline[i] == quote)
			break;
		++len;
	}
	exp = word(cmdline, len, *pos+1);
	add(token, new_token(len, exp, EXP_FIELD));
	free(exp);
	*pos += len+1;
}

