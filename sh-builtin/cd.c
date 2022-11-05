/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabazyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:30:20 by sabazyan          #+#    #+#             */
/*   Updated: 2022/10/25 14:30:33 by sabazyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_header.h"

void print_cd(char *cmd)
{
    char        **matrix;
    char        cwd[256];
    const char  *path;

    matrix = ft_split(cmd, ' ');
    path = getcwd(cwd, 256);
    // if (matrix[0] && is_keyword(matrix[0]) == 0)
    //     printf("-minishell: %s: command not found\n", matrix[0]);
    if (matrix[0] && ft_strcmp(matrix[0], "cd") == 0 && matrix[1] && ft_strcmp(matrix[1], "..") == 0)
        printf("%s\n", ft_strrchr(path, '/'));
}
