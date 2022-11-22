/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:19:57 by dmartiro          #+#    #+#             */
/*   Updated: 2022/11/02 21:37:07 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_table		*table;
	char		*cmdline;

	table = create_tab(envp);
	while (1)
	{
		cmdline = readline("Minishell-$ ");
		builtins(cmdline, table);
		add_history(cmdline);
	}
	//free(cmdline);
}