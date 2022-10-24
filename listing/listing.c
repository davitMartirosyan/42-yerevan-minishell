/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 07:19:03 by root              #+#    #+#             */
/*   Updated: 2022/10/24 21:33:44 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_header.h"

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

t_tok   *last(t_tok *lst)
{
	if (lst == NULL)
		return (0);
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}



void	add(t_tok **lst, t_tok *new)
{
	t_tok	*list;

	list = *lst;
	if (!list)
	{
		*lst = new;
		return ;
	}
	last(list)->next = new;
}
