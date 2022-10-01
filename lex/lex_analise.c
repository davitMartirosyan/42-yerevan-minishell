/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_analise.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 21:14:09 by dmartiro          #+#    #+#             */
/*   Updated: 2022/09/29 16:31:38 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_header.h"


void lexical_analyze(char *cmdline, t_env **env, t_table **table)
{
	// int pos;
	// if(contains("<<", cmdline, &pos))
	// 	printf("HEREDOC\n");
	// if(contains(">>", cmdline, &pos))
	// 	printf("APPEND MODE\n");
	// if(contains(">", cmdline, &pos))
	// 	printf("OUTPUT\n");
	// if(contains("<", cmdline, &pos))
	// 	printf("INPUT\n");
	// if(contains("|", cmdline, &pos))
	// 	printf("PIPE\n");

	regexp(cmdline, "/A-Za-z*/");
}

int contains(char *tok, char *cmdline, int *pos)
{
	int i;
	int c;
	int j;
	int len;
	int flag;
	int count;

	i = -1;
	len = ft_strlen(tok);
	count = 0;
	while(cmdline[++i])
	{
		
		c = 0;
		j = i;
		if(cmdline[j] == tok[c])
		{
			flag = 0;	
			while(tok[c])
			{
				if(cmdline[j] == tok[c])
				{
					++count;
					flag++;
					j++;
				}
				c++;
			}
			if(cmdline[j] == tok[c - 1])
			{
				++count;
				i = j;
				continue;
			}
			if(count != len && cmdline[j] != tok[c - 1])
			{
				count = 0;
				i = j;
				continue;
			}
			if(flag == len && count == len)
			{
				*pos = j;
				count = 0;
				return(1);
			}
			i = j;
		}
		count = 0;
	}
	return (0);
}




// while(tok[c])
// {
// 	if(cmdline[j] == tok[c])
// 	{
// 		++count;
// 		flag++;
// 		j++;
// 	}
// 	c++;
// }
// int counter_of("<<", cmdline)
// {

// }








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
