/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:57:01 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/16 11:57:02 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

void	add_pipe(char *cmdline, int *pos, int _p_ch, t_tok **token)
{
	int i;
	int _p;
	int type;
	char *pipe;
	
	i = *pos;
	_p = 1;
	pipe = NULL;
	while (cmdline[++i] && cmdline[i] == _p_ch)
		++_p;
	pipe = word(cmdline, _p, *pos);
	if (_p > 1)
		type = UNDEFINED;
	else
		type = PIPE;
	add(token, new_token(_p, pipe, type));
	free(pipe);
	*pos += _p-1;
}