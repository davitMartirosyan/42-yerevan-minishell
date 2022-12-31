/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 10:14:09 by user              #+#    #+#             */
/*   Updated: 2022/11/20 16:10:29 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

void add_pipe(char *cmdline, int *pos, int _p_ch, t_tok **token)
{
	int i;
	int _p;
	int type;
	char *pipe;
	
	i = *pos;
	_p = 1;
	while(cmdline[++i] && cmdline[i] == _p_ch)
		++_p;
	pipe = word(cmdline, _p, *pos);
	if(_p > 1)
		type = UNDEFINED;
	else
		type = PIPE;
	add(token, new_token(_p, pipe, type));
	free(pipe);
	*pos += _p;
}