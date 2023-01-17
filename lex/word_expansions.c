/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <tumolabs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:57:28 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/17 02:38:43 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

int	wordlen(char *wordstart, int s_pos)
{
	int	i;

	i = 0;
	while (wordstart[s_pos] && ft_iswordpart(wordstart[s_pos]))
	{
		s_pos++;
		i++;
	}
	return (i);
}

char	*word(char *cmdline, int len, int s_pos)
{
	char	*word;
	int		i;

	i = 0;
	word = NULL;
	word = malloc(sizeof(char) * (len + 1));
	while (i < len)
	{
		word[i] = cmdline[s_pos];
		s_pos++;
		i++;
	}
	word[i] = '\0';
	return (word);
}

void	add_word(char *cmdline, int *pos, t_tok **token)
{
	int		len;
	char	*wordpart;

	(void)token;
	len = wordlen(cmdline, *pos);
	wordpart = NULL;
	wordpart = word(cmdline, len, *pos);
	add(token, new_token(len, wordpart, WORD));
	free(wordpart);
	*pos += len;
}

void	space(char *cmdline, int *pos, t_tok **token)
{
	int		i;
	int		len;
	char	*separator;

	i = *pos;
	len = 0;
	separator = NULL;
	while (cmdline[++i])
	{
		if (!ft_isspace(cmdline[i]))
			break ;
		++len;
	}
	separator = word(cmdline, len, *pos);
	add(token, new_token(len, separator, SEP));
	free(separator);
	*pos += len;
}

void	expansion(char *cmdline, int *pos, int quote, t_tok **token)
{
	int		i;
	int		len;
	char	*expo;

	i = *pos;
	len = 0;
	expo = NULL;
	while (cmdline[++i])
	{
		if (cmdline[i] == quote)
			break ;
		++len;
	}
	expo = word(cmdline, len, *pos + 1);
	add(token, new_token(len, expo, EXP_FIELD));
	free(expo);
	*pos += len + 1;
}
