/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 07:19:03 by root              #+#    #+#             */
/*   Updated: 2022/10/23 08:30:15 by root             ###   ########.fr       */
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
    tok->tok  = token;
    tok->type = type;
    tok->next = NULL;
    return (tok);
}