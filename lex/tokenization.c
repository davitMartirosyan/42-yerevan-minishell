/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 03:00:39 by dmartiro          #+#    #+#             */
/*   Updated: 2022/11/02 01:34:33 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

t_tok *tokenization(char *cmdline)
{
	t_tok *tokens;
	int i;

	tokens = NULL;
	i = 0;
	while (cmdline[i])
	{
		if (cmdline[i] && ft_iswordpart(cmdline[i]) && ft_strlen(cmdline) > i)
			add_word(cmdline, &i, &tokens);
		if(cmdline[i] && ft_isspace(cmdline[i]))
			space(cmdline, &i, cmdline[i], &tokens);
		if(cmdline[i] && (cmdline[i] == '\"' || cmdline[i] == '\''))
			expansion(cmdline, &i, cmdline[i], &tokens);
		if (cmdline[i] && (cmdline[i] == '>' || cmdline[i] == '<'))
			redirection(cmdline, &i, cmdline[i], &tokens);
		if (cmdline[i] && cmdline[i] == '|')
			add_pipe(cmdline, &i, cmdline[i], &tokens);
		i++;
	}
	return (tokens);
}