/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 07:19:03 by root              #+#    #+#             */
/*   Updated: 2022/11/20 16:10:29 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

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
