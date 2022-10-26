/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 03:00:39 by dmartiro          #+#    #+#             */
/*   Updated: 2022/10/26 08:09:42 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

static void add_redirection(char *cmdline, int *pos, int io, t_tok **token);
static char *find_file_name(char *cmdline, int *pos);

t_tok *tokenization(char *cmdline)
{
	t_tok *tokens;
	int i;

	tokens = NULL;
	i = -1;
	while(cmdline[++i])
	{
		if(cmdline[i] && ft_iswordpart(cmdline[i]))
			add_word(cmdline, &i, &tokens);
		if(cmdline[i] && cmdline[i] == '>')
			add_redirection(cmdline, &i, '>', &tokens);
	}
	return (tokens);
}

static void add_redirection(char *cmdline, int *pos, int io, t_tok **token)
{
	int _iostream_count;
	int len;
	int i;
	char *filename;
	
	i = *pos;
	_iostream_count = 1;
	while(cmdline[++i] == io)
		_iostream_count++;
	while(!ft_iswordpart(cmdline[++i]));
	
	len = wordlen(cmdline, i);
	filename = word(cmdline, len, i);
	add(token, new_token(len, filename, REDIR_OUT));
	*pos += i;
	// printf("%s\n", cmdline+i);
}



static char *find_file_name(char *cmdline, int *pos)
{
	int len;
	int i = *pos;
	char *file;
	
	while(cmdline[i++])
	{
		if(ft_iswordpart(cmdline[i]))
		{
			len = wordlen(cmdline, i);
			file = word(cmdline, len, i);		
			break;
		}
	}
	*pos += i+len;
	return (file);
}