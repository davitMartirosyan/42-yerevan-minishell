/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 23:15:51 by codespace         #+#    #+#             */
/*   Updated: 2022/12/14 07:56:27 by dmartiro         ###   ########.fr       */
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

void    reset_update_table(t_table **table, t_cmdline *tree)
{
    free_tokens(&(*table)->token);
	free_cmdline(tree);
}

void free_cmdline(t_cmdline *tree)
{
	t_cmds *current;
	t_cmds *next;

	current = tree->cmds;
	while(current != NULL)
	{
		next = current->next;
		free(current->arguments);
		free(current->path);
		free_arg_pack(current->arg_pack);
		free(current);
		current = next;
	}
	free(tree);
}

void free_arg_pack(char **arg_pack)
{
	int i;

	i = -1;
	while(arg_pack[++i])
		free(arg_pack[i]);
	free(arg_pack);
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