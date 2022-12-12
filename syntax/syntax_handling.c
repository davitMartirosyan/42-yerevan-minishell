/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:53:26 by root              #+#    #+#             */
/*   Updated: 2022/12/12 15:31:12 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

int syntax_handling(char *cmdline, t_table *table)
{
    if(!quote_syntax_analyzer(cmdline, table->q_c))
    {
        printf("%s%s '%s'\n",SHELLERR, TOKEN_SYNTAX_ERR, "\'");
        return (0);
    }
    return (1);
}