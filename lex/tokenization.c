/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 03:00:39 by dmartiro          #+#    #+#             */
/*   Updated: 2022/10/23 08:31:18 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_header.h"
static int wordlen(char *wordstart, int s_pos);
static char *word(char *cmdline, int len, int s_pos);
static void add_word(char *cmdline, int *pos, t_tok *token);

t_tok *tokenization(char *cmdline)
{
	t_tok *token;
	int i;
	
	i = -1;
	while(cmdline[++i])
	{
		if(ft_iswordpart(cmdline[i]))
			add_word(cmdline, &i, token);
		// if(cmdline[i] == '>')
		// 	redirection(cmdline, &i, token, '>');
		// if(cmdline[i] == '<')
		// 	redirection(cmdline, &i, token, '<');
		// if(cmdline[i] == '|')
		// 	pipe(cmdline, &i, token);
	}
	return (token);
}

static void add_word(char *cmdline, int *pos, t_tok *token)
{
	int len;
	char *wordpart;
	t_tok *node;
	
	len = wordlen(cmdline, *pos);
	wordpart = word(cmdline, len, *pos);
	
	node = new_token(len, wordpart, WORD);
	
	printf("%s : %d | type : %d\n", node->tok, node->len, node->type);
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