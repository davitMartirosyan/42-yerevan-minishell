/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 03:00:39 by dmartiro          #+#    #+#             */
/*   Updated: 2022/12/13 12:35:51 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

t_tok	*tokenization(char *cmdline)
{
	t_tok *tokens;
	int i;

	tokens = NULL;
	i = 0;
	while (cmdline && cmdline[i])
	{
		if (cmdline[i] && ft_iswordpart(cmdline[i]) && \
			(int)ft_strlen(cmdline) > i)
			add_word(cmdline, &i, &tokens);
		if(cmdline[i] && ft_isspace(cmdline[i]))
			space(cmdline, &i, &tokens);
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

t_tok *new_token(int len, char *token, int type)
{
    t_tok *tok;

    tok = malloc(sizeof(t_tok));
    if(!tok)
        return (NULL);
    tok->len  = len;
    tok->tok  = ft_strdup(token);
    tok->type = type;
    tok->next = NULL;
    return (tok);
}

void	add(t_tok **lst, t_tok *new)
{
	while(*lst)
		lst = &(*lst)->next;
	*lst = new;	
}
