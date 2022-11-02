/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 01:32:43 by dmartiro          #+#    #+#             */
/*   Updated: 2022/11/02 18:09:46 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

static int check_syntax(t_tok *node, int count);

void parse_tree(t_table *table, char **envp)
{
	t_tok *from;
    t_tok *to;
    char *parseto;
    int i;

    from = table->token;
    i = 0;
    parseto = NULL;
    while(from != NULL)
    {
        if(check_syntax() == 1)
        from = from->next;
        i++;
    }
}

static int check_syntax(t_tok *node, int count)
{
    if((node->type == WORD \
        || node->type == EXP_FIELD \
        || node->type == SEP))
        return (2);
    else if(node->
    )
}
