/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 20:07:27 by root              #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/12/01 23:35:51 by dmartiro         ###   ########.fr       */
=======
/*   Updated: 2022/12/14 13:18:53 by user             ###   ########.fr       */
>>>>>>> master
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
	word = NULL;
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
	
	(void)token;
	len = wordlen(cmdline, *pos);
	wordpart = NULL;
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
	separator = NULL;
	while(cmdline[++i])
	{
		if(!ft_isspace(cmdline[i]))
			break;
		++len;
	}
	separator = word(cmdline, len, *pos);
	add(token, new_token(len, separator, SEP));
	free(separator);
	*pos += len;
}

void expansion(char *cmdline, int *pos, int quote, t_tok **token)
{
	int i;
	int len;
	char *expo;
	
	i = *pos;
	len = 0;
	expo = NULL;
	while(cmdline[++i])
	{
		if(cmdline[i] == quote)
			break;
		++len;
	}
	expo = word(cmdline, len, *pos+1);
	add(token, new_token(len, expo, EXP_FIELD));
	free(expo);
	*pos += len+1;
}

