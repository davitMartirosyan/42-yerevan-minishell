/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 23:15:51 by codespace         #+#    #+#             */
/*   Updated: 2022/12/04 23:19:39 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"


void    print_tokens(t_tok **token)
{
	while((*token) != NULL)
	{
		printf("[%s] : %d\n", (*token)->tok, (*token)->type);
		token = &(*token)->next;
	}
}

void    reset_update_table(t_table **table, t_cmdline **tree)
{
    free_tokens(&(*table)->token);
}

void    free_tokens(t_tok **token)
{
    t_tok *curr;
    t_tok *next;
    
    curr = *token;
    while(curr != NULL)
    {
        next = curr->next;
        free(curr);
        curr = next;
    }
    *token = NULL;
}