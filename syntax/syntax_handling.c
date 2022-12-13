/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:53:26 by root              #+#    #+#             */
/*   Updated: 2022/12/13 15:52:13 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

static int token_syntax_analyzer(t_table *table, t_cmdline *commands);

int syntax_handling(char *cmdline, t_table *table, t_cmdline *commands)
{
    static int syn = 0;
    
    if(syn == 0)
    {
        if(quote_syntax_analyzer(cmdline, table->q_c))
        {
            syn++;
            return (1);
        }
        printf("%s%s '%s'\n", SHELLERR, TOKEN_SYNTAX_ERR, "\'");
        return (0);   
    }
    else
    {
        if(token_syntax_analyzer(table, commands))
        {
            syn = 0;
            return (1);
        }
        return (0);
    }
    return (1);
}

static int token_syntax_analyzer(t_table *table, t_cmdline *commands)
{
    t_tok *toks;
    t_cmds *cmd;

    toks = table->token;
    cmd = commands->cmds;
    
    return (1);
}