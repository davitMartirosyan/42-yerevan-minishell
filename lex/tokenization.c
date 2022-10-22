/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 03:00:39 by dmartiro          #+#    #+#             */
/*   Updated: 2022/10/22 08:01:44 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_header.h"
static int wordlen(char *wordstart, int s_pos);
static char *word(char *cmdline, int len, int s_pos);


t_tok *tokenization(char *cmdline)
{
	t_tok *token;
	t_tok *tok_tmp;
	int i;
	int len;
	char *wordpart;
	
	i = -1;
	token = malloc(sizeof(t_tok));
	if(!token)
		return (NULL);
	tok_tmp = token;
	while(cmdline[++i])
	{
		len = 0;
		if(ft_iswordpart(cmdline[i]))
		{
			len = wordlen(cmdline, i);
			wordpart = word(cmdline, len, i);
			token->len = len;
			token->tok = wordpart;
			token->type = WORD;
			token->next = malloc(sizeof(t_tok));
			token = token->next;
			i += len;
			free(wordpart);
			//mi qani hatic segfaulta qcum
		}
	}
	return (tok_tmp);
}

static int wordlen(char *wordstart, int s_pos)
{
	int i;

	i = 0;
	while(wordstart[s_pos]  && ft_iswordpart(wordstart[s_pos]))
	{
		s_pos++;
		i++;
	}
	return (i);
}
static char *word(char *cmdline, int len, int s_pos)
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