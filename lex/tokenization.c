/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 03:00:39 by dmartiro          #+#    #+#             */
/*   Updated: 2022/10/23 05:11:40 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_header.h"
static int wordlen(char *wordstart, int s_pos);
static char *word(char *cmdline, int len, int s_pos);


t_tok *tokenization(char *cmdline)
{
	t_tok *token;
	int i;
	
	i = -1;
	while(cmdline[++i])
	{
		len = 0;
		if(ft_iswordpart(cmdline[i]))
			add_word(cmdline, &i, token);
		if(cmdline[i] == '>')
			redirection(cmdline, &i, token, '>');
		if(cmdline[i] == '<')
			redirection(cmdline, &i, token, '<');
		if(cmdline[i] == '|')
			pipe(cmdline, &i, token);
	}
	return (tok_tmp);
}

static void add_word(char *cmdline, int *pos, t_tok *token)
{
	int i;
	
	i = 0;
	token = 
	// while(cmdline[*pos] && ft_iswordpart(cmdline[*pos]))
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