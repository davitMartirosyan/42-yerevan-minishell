/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:53:26 by root              #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/12/14 08:06:04 by dmartiro         ###   ########.fr       */
=======
/*   Updated: 2022/12/17 11:03:55 by dmartiro         ###   ########.fr       */
>>>>>>> master
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

static int token_syntax_analyzer(t_table *table, t_cmdline *commands);

int syntax_handling(char *cmdline, t_table *table, t_cmdline *commands)
{
    static int syn = 0;
    
<<<<<<< HEAD
    if(syn == 0 && cmdline)
    {
=======
    if(syn == 0)
    {
        if(!cmdline[0])
            return (0);
>>>>>>> master
        if(!quote_syntax_analyzer(cmdline, table->q_c))
        {
			printf("%s%s '%s'\n", SHELLERR, TOKEN_SYNTAX_ERR, "\'");
            return (0);
        }
        syn++;
<<<<<<< HEAD
        return (1);   
=======
        return (1);
>>>>>>> master
    }
    else
    {
        if(!token_syntax_analyzer(table, commands))
        {
<<<<<<< HEAD
			printf("Token error\n");
=======
>>>>>>> master
			syn--;
            return (0);
        }
		syn--;
        return (1);
    }
    return (0);
}

static int token_syntax_analyzer(t_table *table, t_cmdline *commands)
{
    t_tok *toks;
    t_cmds *cmd;

<<<<<<< HEAD
    toks = table->token;
    cmd = commands->cmds;
	if(cmd != NULL)
		return (1);
	return (0);
}
=======
    toks = NULL;
    cmd = NULL;
	toks = table->token;
    cmd = commands->cmds;
    if(toks != NULL && commands != NULL)
    {
        //while(toks != NULL)
        //{
        //    if(toks->type == UNDEFINED)
        //    {
        //        printf("%s%s '%s'\n", SHELLERR, TOKEN_SYNTAX_ERR, toks->tok);
        //        return (0);
        //    }
        //    else if(typeis_redirection(toks->type))
        //    {
        //        if(!find_delim(&toks))
        //            printf("%s%s '%s'\n", SHELLERR, TOKEN_SYNTAX_ERR, toks->tok);
        //        else
        //            continue;
        //    }
        //    toks = toks->next;
        //}
        return (1);
    }
    return (0);
}

//valgrind -leak-check=full
>>>>>>> master
