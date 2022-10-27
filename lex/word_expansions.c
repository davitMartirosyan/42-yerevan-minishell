/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 20:07:27 by root              #+#    #+#             */
/*   Updated: 2022/10/27 14:31:29 by user             ###   ########.fr       */
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

void expansion(char *cmdline, int *pos, int quote, t_tok **token)
{
	int i;
	int len;
	char *expansion;

	i = *pos;
	len = 0;
	while(cmdline[++i] && cmdline[i] != quote)
		len++;
	expansion = word(cmdline, len, *pos+1);
	add(token, new_token(len, expansion, WORD));
	free(expansion);
	*pos += len+1;
}