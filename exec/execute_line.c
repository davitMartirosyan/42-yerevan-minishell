/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 03:17:29 by dmartiro          #+#    #+#             */
/*   Updated: 2022/10/06 04:01:12 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_header.h"

int execute(char *cmd, t_table **table, char **envp)
{
    int stdindup =  dup(STDIN);
    int stdoutdup =  dup(STDOUT);
    printf("%d : %d\n", stdindup, stdoutdup);

    close(stdindup);
    close(stdoutdup);
    return (0);
}