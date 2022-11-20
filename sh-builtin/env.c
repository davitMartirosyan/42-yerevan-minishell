/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:32:26 by sabazyan          #+#    #+#             */
/*   Updated: 2022/11/20 16:10:29 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

void print_env(char *cmd, char *env[])
{
    char    **matrix;
    int     i;
    int     j;

    matrix = ft_split(cmd, ' ');
    i = 1;
    j = -1;
    if (matrix[0] && ft_strcmp(matrix[0], "env") == 0 && !matrix[1])
    {
        while (env[++j])
            printf("%s\n", env[j]);
    }
    else if (matrix[0] && ft_strcmp(matrix[0], "env") == 0 && matrix[1])
        printf("env: %s: No such file or directory\n", ft_strtrim(matrix[1], "\""));
}