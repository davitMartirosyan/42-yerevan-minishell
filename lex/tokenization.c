/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 03:00:39 by dmartiro          #+#    #+#             */
/*   Updated: 2022/10/26 18:10:11 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

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
			redirection(cmdline, &i, cmdline[i], &tokens);
		if(cmdline[i] && cmdline[i] == '<')
			redirection(cmdline, &i, cmdline[i], &tokens);
		if(cmdline[i] && cmdline[i] == '|')
			pipe(cmdline, &i, &tokens);
	}
	return (tokens);
}

static void pipe(char *cmdline, int *pos, t_tok **token)
{
	
}