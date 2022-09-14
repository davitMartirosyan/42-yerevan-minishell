/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_analise.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 21:14:09 by dmartiro          #+#    #+#             */
/*   Updated: 2022/09/14 01:18:44 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../libft/libft.h"

int main(int ac, char *av[], char **envp)
{
	const char *CAP_LETTERS;
	const char *SML_LETTERS;
	CAP_LETTERS = "A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z";
	SML_LETTERS = "a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z";
	char **lex = ft_split(CAP_LETTERS, '|');

	int i = -1;
	while(envp[++i])
		printf("%s\n", envp[i]);
}
