/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 03:00:39 by dmartiro          #+#    #+#             */
/*   Updated: 2022/10/24 21:46:12 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_header.h"
static int		wordlen(char *wordstart, int pos);
static char		*word(char *cmdline, int len, int s_pos);
static void		add_word(char *cmdline, int *pos, t_tok **token);

t_tok	*tokenization(char *cmdline)
{
	t_tok *tokens;
	t_tok *tmp;
	int i;

	i = -1;
	tokens = malloc(sizeof(t_tok));
	if(!tokens)
		return (NULL);
	tokens->tok = ".";
	tokens->next = NULL;
	tmp = tokens;
	while(cmdline[++i])
	{
		if(cmdline[i] && ft_iswordpart(cmdline[i]))
			add_word(cmdline, &i, &tokens);		
	}
	return (tmp);
}

static void add_word(char *cmdline, int *pos, t_tok **token)
{
	char *wordpart;
	int len;

	len = wordlen(cmdline, *pos);
	wordpart = word(cmdline, len, *pos);
	while((*token)->next != NULL)
		(*token) = (*token)->next;

	(*token)->next = new_token(len, wordpart, WORD);
	free(wordpart);
	*pos += len;
}


static int wordlen(char *wordstart, int s_pos)
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