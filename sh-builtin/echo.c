/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabazyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:29:34 by sabazyan          #+#    #+#             */
/*   Updated: 2022/10/25 14:30:10 by sabazyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_header.h"

int is_keyword(char *str)
{
    char    **keywords;
    int     i;

    keywords = ft_split(RESERVED, ' ');
    i = -1;
    while (keywords[++i])
    {
        if (ft_strcmp(keywords[i], str) == 0)
            return (1);
    }
    return (0);
}

int is_token(char *str)
{
    char    **tokens;
    int     i;

    tokens = ft_split(TOKENS, ' ');
    i = -1;
    while (tokens[++i])
    {
        if (ft_strcmp(tokens[i], str) == 0)
            return (1);
    }
    return (0);
}

void print_echo(char *cmd)
{
    char    **matrix;
    int     i;

    matrix = ft_split(cmd, ' ');
    i = 1;
    if (matrix[0] && is_keyword(matrix[0]) == 0)
        printf("-minishell: %s: command not found\n", matrix[0]);
    else if (matrix[0] && is_keyword(matrix[0]) == 1)
    {
        if (ft_strcmp(matrix[0], "echo") == 0 && !matrix[1])
            printf("\n");
        else if (ft_strcmp(matrix[0], "echo") == 0 && matrix[1] && ft_strcmp(matrix[1], "-n") != 0)
        {
            while (matrix[i] && is_token(matrix[i]) == 0)
            {
                printf("%s", ft_strtrim(matrix[i], "\""));
                if (matrix[i + 1])
                    printf(" ");
                i++;
            }
            printf("\n");
        }
        else if (ft_strcmp(matrix[0], "echo") == 0 && matrix[1] && ft_strcmp(matrix[1], "-n") == 0)
        {
            i++;
            while (matrix[i] && is_token(matrix[i]) == 0)
            {
                printf("%s", ft_strtrim(matrix[i], "\""));
                if (matrix[i + 1])
                    printf(" ");
                i++;
            }
        }
    }
}
