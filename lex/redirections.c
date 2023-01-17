/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:57:09 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/17 02:30:24 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

int	typeface(int c, int len)
{
	if (c == '<')
	{
		if (len == 1)
			return (REDIR_IN);
		else if (len == 2)
			return (HEREDOC);
		else
			return (UNDEFINED);
	}
	else if (c == '>')
	{
		if (len == 1)
			return (REDIR_OUT);
		else if (len == 2)
			return (APPEND);
		else
			return (UNDEFINED);
	}
	else
		return (UNDEFINED);
}

void	redirection(char *cmdline, int *pos, int io, t_tok **token)
{
	int		_io;
	int		i;
	int		type;
	char	*reddir;

	i = *pos;
	_io = 0;
	reddir = NULL;
	while (cmdline[++i] && cmdline[i] == io)
		_io++;
	reddir = word(cmdline, _io + 1, *pos);
	type = typeface(io, _io + 1);
	add(token, new_token(_io + 1, reddir, type));
	free(reddir);
	*pos += _io;
}
