/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_analise.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 21:14:09 by dmartiro          #+#    #+#             */
/*   Updated: 2022/10/06 04:02:15 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_header.h"


void lexical_analyze(char *cmdline, t_table **table)
{
	char **tokens;
	add_history(cmdline);
	tokens = ft_split(cmdline, ' ');
	int i = -1;
	while(tokens[++i])
		tokens[i] = ft_strtrim(tokens[i], " ");
	
}