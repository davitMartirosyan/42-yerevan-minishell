/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 03:00:39 by dmartiro          #+#    #+#             */
/*   Updated: 2022/10/23 21:12:37 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_header.h"
static int wordlen(char *wordstart, int pos);
static char *word(char *cmdline, int len, int s_pos);
static void add_word(char *cmdline, int *pos, t_tok *token);
static void insert_after(t_tok **tokens, t_tok *node);

t_tok *tokenization(char *cmdline)
{
	t_tok *tokens;
	int i;
	
	i = -1;
	while(cmdline[++i])
	{
		if (cmdline[i] && ft_iswordpart(cmdline[i]))
			add_word(cmdline, &i, tokens);
		// if(cmdline[i] == '>')
		// 	redirection(cmdline, &i, tokens, '>');
		// if(cmdline[i] == '<')
		// 	redirection(cmdline, &i, tokens, '<');
		// if(cmdline[i] == '|')
		// 	pipe(cmdline, &i, tokens);
	}
	return (tokens);
}

static void add_word(char *cmdline, int *pos, t_tok *token)
{
	int len;
	char *wordpart;
	t_tok *node;
	
	len = wordlen(cmdline, *pos);
	wordpart = word(cmdline+*pos, len, *pos);
	
	printf("%s\n", wordpart);
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
		printf("%c\n", cmdline[s_pos]);
		word[i] = cmdline[s_pos];
		s_pos++;
		i++;
	}
	word[i] = '\0';
	return (word);
}