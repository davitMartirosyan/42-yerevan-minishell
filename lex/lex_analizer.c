/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_analizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:06:07 by root              #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/12/13 15:49:33 by user             ###   ########.fr       */
=======
/*   Updated: 2022/12/18 15:05:32 by dmartiro         ###   ########.fr       */
>>>>>>> master
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

<<<<<<< HEAD
int lexical_analyzer(char *cmdline, t_table *table)
{
=======
int lexical_analyzer(char *newpoint, t_table *table)
{
	char *cmdline;

	cmdline = NULL;
	cmdline = ft_strdup(newpoint);
>>>>>>> master
	openquotes(cmdline);
	if(syntax_handling(cmdline, table, NULL))
	{
		cmdline = find_replace(cmdline, table);
		token_replacment(cmdline, 4, '$');
		table->token = tokenization(cmdline);
<<<<<<< HEAD
		return (1);
	}
=======
		free(cmdline);
		return (1);
	}
	free(cmdline);
>>>>>>> master
	return (0);
}