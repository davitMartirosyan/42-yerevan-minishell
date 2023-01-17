/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 02:56:33 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/17 02:56:34 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*memory;

	memory = malloc(sizeof(char) * (ft_strlen(s) + 1));
	i = 0;
	if (!s || !f || !memory)
		return (NULL);
	while (i < ft_strlen(s))
	{
		memory[i] = f(i, s[i]);
		i++;
	}
	memory[i] = '\0';
	return (memory);
}
