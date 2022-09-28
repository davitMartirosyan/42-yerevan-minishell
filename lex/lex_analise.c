/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_analise.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 21:14:09 by dmartiro          #+#    #+#             */
/*   Updated: 2022/09/28 22:27:01 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_header.h"



void lexical_analyze(char *cmdline, t_env **env, t_table **table)
{
	if(contains("<<", cmdline))
	{
		printf("ok\n");
	}
}


int contains(char *tok, char *cmdline)
{
	// tok -> |
	// cmdline -> abc | x=
	int i;
	int c;
	int j;
	int len;
	int flag;

	i = -1;
	len = ft_strlen(tok);
	while(cmdline[++i])
	{
		c = -1;
		j = i;
		if(cmdline[j] == tok[++c])
		{
			flag = 1;
			while(tok[++c])
				if(cmdline[++j] == tok[c])
					flag++;
			if(cmdline[++j] == tok[c - 1])
				return (0);
			else if(flag == len)
				return (1);
			flag = 0;
		}
	}
	return (0);
}

// int main(int ac, char *av[], char **envp)
// {
// 	const char *CAP_LETTERS;
// 	const char *SML_LETTERS;
// 	CAP_LETTERS = "A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z";
// 	SML_LETTERS = "a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z";
// 	char **lex = ft_split(CAP_LETTERS, '|');
// 	int i = -1;
// 	while(envp[++i])
// 		printf("%s\n", envp[i]);
// }
