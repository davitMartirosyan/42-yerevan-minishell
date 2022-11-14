/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 04:24:24 by dmartiro          #+#    #+#             */
/*   Updated: 2022/11/14 07:33:55 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_header.h"

int typeface(int c, int len)
{
	if(c == '<')
	{
		if(len == 1)
			return (REDIR_IN);
		else if(len == 2)
			return (HEREDOC);
		else
			return (UNDEFINED);
	} else if(c == '>')
	{
		if(len == 1)
			return (REDIR_OUT);
		else if(len == 2)
			return (APPEND);
		else
			return (UNDEFINED);
	}
	else
		return (UNDEFINED);
}

void	redirection(char *cmdline, int *pos, int io, t_tok **token)
{
	int _io;
	int i;
	int type;
	char *reddir;
	
	i = *pos;
	_io = 0;
	while(cmdline[++i] && cmdline[i] == io)
		_io++;
	reddir = word(cmdline, _io+1, *pos);
	type = typeface(io, _io+1);
	add(token, new_token(_io+1, reddir, type));
	free(reddir);
	*pos += _io;
}
