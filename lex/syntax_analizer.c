/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 20:07:27 by root              #+#    #+#             */
/*   Updated: 2022/10/17 06:01:07 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_header.h"

int quote_syntax_analyze(char *cmdline, int *q_c)
{
	if(check_quotes(cmdline, q_c))
	{
		token_replacment(cmdline, '\a', '\'');
		token_replacment(cmdline, '\b', '\"');
		return (1);
	}
	else
	{
		token_replacment(cmdline, '\a', '\'');
		token_replacment(cmdline, '\b', '\"');
		return (0);
	}
}