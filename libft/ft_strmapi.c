/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:30:13 by dmartiro          #+#    #+#             */
/*   Updated: 2022/04/07 22:55:54 by dmartiro         ###   ########.fr       */
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
