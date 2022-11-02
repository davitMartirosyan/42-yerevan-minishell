/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabazyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:30:41 by sabazyan          #+#    #+#             */
/*   Updated: 2022/10/25 14:30:52 by sabazyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_header.h"

void print_pwd(char *cmd)
{
    char    **matrix;
    char    cwd[256];

    matrix = ft_split(cmd, ' ');
    // if (matrix[0] && is_keyword(matrix[0]) == 0)
    //     printf("-minishell: %s: command not found\n", matrix[0]);
    if (matrix[0] && ft_strcmp(matrix[0], "pwd") == 0)
        printf("%s\n", getcwd(cwd, 256));
}
